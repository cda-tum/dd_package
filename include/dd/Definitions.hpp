/*
 * This file is part of the MQT DD Package which is released under the MIT license.
 * See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_DATATYPES_HPP
#define DDpackage_DATATYPES_HPP

// Set to 'false' to activate debugging
#ifndef NDEBUG
#define NDEBUG true
#endif

// Set to 'true' to activate profiling. This enables
//   - call counts of various functions
//   - clock() timing of these functions
#define ENABLE_PROFILING false
#include "Profiling.hpp"

#include <complex>
#include <cstdint>
#include <type_traits>
#include <unordered_map>
#include <utility>
#include <vector>

namespace dd {
    // Set number of qubits for limdd state vector
    static const std::size_t NUM_QUBITS = 126;

    // integer type used for indexing qubits
    // needs to be a signed type to encode -1 as the index for the terminal
    // std::int_fast8_t can at least address 128 qubits as [0, ..., 127]
    using Qubit = std::int_fast8_t;
    static_assert(std::is_signed_v<Qubit>, "Type Qubit must be signed.");

    // integer type used for specifying numbers of qubits
    using QubitCount = std::make_unsigned<Qubit>::type;

    // integer type used for reference counting
    // 32bit suffice for a max ref count of around 4 billion
    using RefCount = std::uint_fast32_t;
    static_assert(std::is_unsigned_v<RefCount>, "RefCount should be unsigned.");

    // floating point type to use
    using fp = double;
    static_assert(std::is_floating_point_v<fp>, "fp should be a floating point type (float, *double*, long double)");

    // logic radix
    static constexpr std::uint_fast8_t RADIX = 2;
    // max no. of edges = RADIX^2
    static constexpr std::uint_fast8_t NEDGE = RADIX * RADIX;

    enum class BasisStates {
        zero,
        one,
        plus,
        minus,
        right,
        left
    };

    static constexpr fp SQRT2_2 = 0.707106781186547524400844362104849039284835937688474036588L;
    static constexpr fp PI      = 3.141592653589793238462643383279502884197169399375105820974L;
    static constexpr fp PI_2    = 1.570796326794896619231321691639751442098584699687552910487L;
    static constexpr fp PI_4    = 0.785398163397448309615660845819875721049292349843776455243L;

    using CVec = std::vector<std::complex<fp>>;
    using CMat = std::vector<CVec>;

    // use hash maps for representing sparse vectors of probabilities
    using ProbabilityVector = std::unordered_map<std::size_t, fp>;

    static constexpr std::uint_least64_t SERIALIZATION_VERSION = 1;

    // 64bit mixing hash (from MurmurHash3, https://github.com/aappleby/smhasher/blob/master/src/MurmurHash3.cpp)
    constexpr std::size_t murmur64(std::size_t k) {
        k ^= k >> 33;
        k *= 0xff51afd7ed558ccdULL;
        k ^= k >> 33;
        k *= 0xc4ceb9fe1a85ec53ULL;
        k ^= k >> 33;
        return k;
    }

    // combine two 64bit hashes into one 64bit hash (boost::hash_combine, https://www.boost.org/LICENSE_1_0.txt)
    constexpr std::size_t combineHash(std::size_t lhs, std::size_t rhs) {
        lhs ^= rhs + 0x9e3779b97f4a7c15ULL + (lhs << 6) + (lhs >> 2);
        return lhs;
    }

    // alternative hash combinator (from Google's city hash, https://github.com/google/cityhash/blob/master/COPYING)
    //    constexpr std::size_t combineHash(std::size_t lhs, std::size_t rhs) {
    //        const std::size_t kMul = 0x9ddfea08eb382d69ULL;
    //        std::size_t a = (lhs ^ rhs) * kMul;
    //        a ^= (a >> 47);
    //        std::size_t b = (rhs ^ a) * kMul;
    //        b ^= (b >> 47);
    //        b *= kMul;
    //        return b;
    //    }

    // calculates the Units in Last Place (ULP) distance of two floating point numbers
    [[maybe_unused]] static std::size_t ulpDistance(fp a, fp b) {
        if (a == b)
            return 0;

        std::size_t ulps   = 1;
        fp          nextFP = std::nextafter(a, b);
        while (nextFP != b) {
            ulps++;
            nextFP = std::nextafter(nextFP, b);
        }
        return ulps;
    }

    enum pauli_op {
        pauli_id = 'I',
        pauli_x  = 'X',
        pauli_y  = 'Y',
        pauli_z  = 'Z',
        pauli_none = 0
    };

    enum phase_t {
        phase_one       = 0,
        phase_i         = 1,
        phase_minus_one = 2,
        phase_minus_i   = 3,
		no_phase        = 4
    };

    enum LIMDD_group {
    	QMDD_group,
    	Z_group,
    	Pauli_group
    };

    enum CachingStrategy {
        QMDDCachingStrategy = 0,
        cliffordSpecialCaching = 1,
        localityAwareCachingDirtyTrick = 2,
        localityAwareCachingClean = 4,
        lazyMemoizationGroupIntersect = 8,
        localityAndCliffordCaching = cliffordSpecialCaching | localityAwareCachingDirtyTrick,
        smartStabilizerGeneration = 16,
        localityAwarePropagateReducedLim = 32,
        skipIdentityGateMultiplication   = 64
    };

    // Set to 'true' to enable (potentially buggy) bit tricks in the LimEntry<>::multiplyBy() routine
#define fastLazyMultiplication true

    inline bool usingSpecialCliffordCaching(CachingStrategy strategy) {
        return (strategy & cliffordSpecialCaching) != 0;
    }

    inline bool usingLazyMemoizationGroupIntersect(CachingStrategy strategy) {
        return (strategy & lazyMemoizationGroupIntersect) != 0;
    }

    inline bool usingSmartStabilizerGeneration(CachingStrategy strategy) {
        return (strategy & smartStabilizerGeneration) != 0;
    }

    inline bool usingLocalityAwareCachingDirtyTrick(CachingStrategy strategy) {
        return (strategy & localityAwareCachingDirtyTrick) != 0;
    }

    inline bool usingLocalityAwarePropagateReducedLim(CachingStrategy strategy) {
        return (strategy & localityAwarePropagateReducedLim) != 0;
    }

    inline bool usingSkipIdentityGate(CachingStrategy strategy) {
        return (strategy & skipIdentityGateMultiplication) != 0;
    }


} // namespace dd

#endif //DDpackage_DATATYPES_HPP
