/*
 * This file is part of the JKQ DD Package which is released under the MIT license.
 * See file README.md or go to http://iic.jku.at/eda/research/quantum_dd/ for more information.
 */

#ifndef DDpackage_H
#define DDpackage_H

#include "ComputeTable.hpp"
#include "DDcomplex.hpp"
#include "Definitions.hpp"
#include "OperationTable.hpp"
#include "ToffoliTable.hpp"
#include "UniqueTable.hpp"

#include <algorithm>
#include <array>
#include <bitset>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <map>
#include <queue>
#include <random>
#include <set>
#include <sstream>
#include <string>
#include <tuple>
#include <unordered_set>
#include <vector>

using CN = dd::ComplexNumbers;

namespace dd {

    enum class BasisStates {
        zero,
        one,
        plus,
        minus,
        right,
        left
    };

    class Package {
        ///
        /// Complex number handling
        ///
    public:
        ComplexNumbers cn{};
        // change the tolerance used to decide the equivalence of numbers
        static void setComplexNumberTolerance(const fp tol) { CN::setTolerance(tol); }

        ///
        /// Construction, destruction, information and reset
        ///
    public:
        static constexpr auto maxPossibleQubits = std::numeric_limits<Qubit>::max() + 1;
        static constexpr auto defaultQubits     = 128;
        explicit Package(std::size_t nq = defaultQubits):
            cn(ComplexNumbers()), nqubits(nq) {
            resize(nq);
        };
        ~Package()                      = default;
        Package(const Package& package) = delete;
        Package& operator=(const Package& package) = delete;

        // resize the package instance
        void resize(std::size_t nq) {
            if (nq > maxPossibleQubits) {
                throw std::invalid_argument("Requested too many qubits from package. Qubit datatype only allows up to " +
                                            std::to_string(maxPossibleQubits) + " qubits, while " +
                                            std::to_string(nq) + " were requested. Please recompile the package with a wider Qubit type!");
            }
            nqubits = nq;
            vUniqueTable.resize(nqubits);
            mUniqueTable.resize(nqubits);
            IdTable.resize(nqubits);
        }

        // print information on package and its members
        static void printInformation();

        // print unique and compute table statistics
        void statistics();

        // reset package state
        void reset() {
            vUniqueTable.clear();
            mUniqueTable.clear();
            clearComputeTables();
        }

        // getter for qubits
        [[nodiscard]] auto qubits() const { return nqubits; }

    private:
        std::size_t nqubits;

        ///
        /// Vector nodes, edges and quantum states
        ///
    public:
        struct vNode;
        struct vEdge {
            vNode*  p;
            Complex w;

            constexpr bool operator==(const vEdge& other) const {
                return p == other.p && CN::equals(w, other.w);
            }
            constexpr bool operator!=(const vEdge& other) const {
                return !operator==(other);
            }
        };
        struct vNode {
            vNode*                   next = nullptr; // link for unique table and available space chain
            std::array<vEdge, RADIX> e{};            // edges out of this node
            std::size_t              ref{};          // reference count
            Qubit                    v{};            // variable index (nonterminal) value (-1 for terminal)
        };
        struct vCachedEdge {
            vNode*       p{};
            ComplexValue w{};

            vCachedEdge() = default;
            vCachedEdge(vNode* p, const ComplexValue& w):
                p(p), w(w) {}
            vCachedEdge(vNode* p, const Complex& c):
                p(p) {
                w.r = CN::val(c.r);
                w.i = CN::val(c.i);
            }
            bool operator==(const vCachedEdge& other) const {
                return p == other.p && CN::equals(w, other.w);
            }
            bool operator!=(const vCachedEdge& other) const {
                return !operator==(other);
            }
        };

        static vEdge makeVectorTerminal(const Complex& w) { return {vTerminalNode, w}; }
        // make a vector DD node and return an edge pointing to it. The node is not recreated if it already exists.
        vEdge makeVectorNode(Qubit var, const std::array<vEdge, RADIX>& edge, bool cached = false);
        vEdge normalize(const vEdge& e, bool cached);

        static constexpr bool isTerminal(const vNode* p) { return p == vTerminalNode; }
        static constexpr bool isTerminal(const vEdge& e) { return isTerminal(e.p); }
        static constexpr bool isZeroDD(const vEdge& e) { return e == vZero; }
        static constexpr bool isOneDD(const vEdge& e) { return e == vOne; }

        // generate |0...0> with n qubits
        vEdge makeZeroState(QubitCount n);
        // generate computational basis state |i> with n qubits
        vEdge makeBasisState(QubitCount n, const std::vector<bool>& state);
        // generate general basis state with n qubits
        vEdge makeBasisState(QubitCount n, const std::vector<BasisStates>& state);

    private:
        static vNode vTerminal;
        // pointer to vector terminal node
        constexpr static vNode* vTerminalNode{&vTerminal};
        // edges pointing to vector zero and one DD constants
        constexpr static vEdge vOne{vTerminalNode, ComplexNumbers::ONE};
        constexpr static vEdge vZero{vTerminalNode, ComplexNumbers::ZERO};

        ///
        /// Matrix nodes, edges and quantum gates
        ///
    public:
        struct mNode;
        struct mEdge {
            mNode*  p;
            Complex w;

            constexpr bool operator==(const mEdge& other) const {
                return p == other.p && CN::equals(w, other.w);
            }
            constexpr bool operator!=(const mEdge& other) const {
                return !operator==(other);
            }
        };

        struct mNode {
            mNode*                   next = nullptr; // link for unique table and available space chain
            std::array<mEdge, NEDGE> e{};            // edges out of this node
            std::size_t              ref{};          // reference count
            Qubit                    v{};            // variable index (nonterminal) value (-1 for terminal)
            bool                     symm  = false;  // node is symmetric
            bool                     ident = false;  // node resembles identity
        };
        struct mCachedEdge {
            mNode*       p{};
            ComplexValue w{};

            mCachedEdge() = default;
            mCachedEdge(mNode* p, const ComplexValue& w):
                p(p), w(w) {}
            mCachedEdge(mNode* p, const Complex& c):
                p(p) {
                w.r = CN::val(c.r);
                w.i = CN::val(c.i);
            }
            bool operator==(const mCachedEdge& other) const {
                return p == other.p && CN::equals(w, other.w);
            }
            bool operator!=(const mCachedEdge& other) const {
                return !operator==(other);
            }
        };

        static mEdge makeMatrixTerminal(const Complex& w) { return {mTerminalNode, w}; }
        // make a matrix DD node and return an edge pointing to it. The node is not recreated if it already exists.
        mEdge makeMatrixNode(Qubit var, const std::array<mEdge, NEDGE>& edge, bool cached = false);
        mEdge normalize(const mEdge& e, bool cached);

        static constexpr bool isTerminal(const mNode* p) { return p == mTerminalNode; }
        static constexpr bool isTerminal(const mEdge& e) { return isTerminal(e.p); }
        static constexpr bool isZeroDD(const mEdge& e) { return e == mZero; }
        static constexpr bool isOneDD(const mEdge& e) { return e == mOne; }

        // build matrix representation for a single gate on an n-qubit circuit
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, Qubit target) {
            return makeGateDD(mat, n, std::set<Control>{}, target);
        }
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, const Control& control, Qubit target) {
            return makeGateDD(mat, n, std::set{control}, target);
        }
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, Qubit control, Qubit target) {
            return makeGateDD(mat, n, std::set<Control>{{control}}, target);
        }
        mEdge makeGateDD(const std::array<ComplexValue, NEDGE>& mat, QubitCount n, const std::set<Control>& controls, Qubit target);

    private:
        static mNode mTerminal;
        // pointer to matrix terminal node
        constexpr static mNode* mTerminalNode{&mTerminal};
        // edges pointing to matrix zero and one DD constants
        constexpr static mEdge mOne{mTerminalNode, ComplexNumbers::ONE};
        constexpr static mEdge mZero{mTerminalNode, ComplexNumbers::ZERO};

        // check whether node represents a symmetric matrix or the identity
        void checkSpecialMatrices(mNode* p);

        ///
        /// Unique tables, Reference counting and garbage collection
        ///
    public:
        static constexpr std::size_t NBUCKET         = 32768;       // number of hash table buckets; must be a power of 2
        static constexpr std::size_t HASHMASK        = NBUCKET - 1; // must be nbuckets-1
        static constexpr std::size_t ALLOCATION_SIZE = 2000;        // may be increased for larger benchmarks to minimize the number of allocations
        static constexpr std::size_t GCLIMIT         = 250000;      // initial garbage collection limit
        static constexpr std::size_t GCINCREMENT     = 0;           // garbage collection limit increment

        // hash functions
        static std::size_t hash(const vNode* p);
        static std::size_t hash(const mNode* p);

        // unique tables
        UniqueTable<vNode, vEdge, hash, NBUCKET, ALLOCATION_SIZE> vUniqueTable{nqubits, GCLIMIT, GCINCREMENT};

        void incRef(const vEdge& e) { vUniqueTable.incRef(e); }
        void decRef(const vEdge& e) { vUniqueTable.decRef(e); }

        UniqueTable<mNode, mEdge, hash, NBUCKET, ALLOCATION_SIZE> mUniqueTable{nqubits, GCLIMIT, GCINCREMENT};

        void incRef(const mEdge& e) { mUniqueTable.incRef(e); }
        void decRef(const mEdge& e) { mUniqueTable.decRef(e); }

        void garbageCollect(bool force = false);

    private:
        ///
        /// Compute table definitions
        ///
    public:
        static constexpr std::size_t CTSLOTS = 16384;       // no. of computed table slots
        static constexpr std::size_t CTMASK  = CTSLOTS - 1; // must be CTSLOTS-1

        // hash functions
        template<class A, class B>
        static std::size_t computeHash(const A& a, const B& b) {
            const auto node_pointer = (reinterpret_cast<std::uintptr_t>(a.p) +
                                       reinterpret_cast<std::uintptr_t>(b.p)) >>
                                      3U;
            const auto weights = reinterpret_cast<std::uintptr_t>(a.w.i) +
                                 reinterpret_cast<std::uintptr_t>(a.w.r) +
                                 reinterpret_cast<std::uintptr_t>(b.w.i) +
                                 reinterpret_cast<std::uintptr_t>(b.w.r);
            return (node_pointer + weights) & CTMASK;
        }

        template<class A, class B>
        static std::size_t computeCachedHash(const A& a, const B& b) {
            const auto node_pointer = (reinterpret_cast<std::uintptr_t>(a.p) +
                                       reinterpret_cast<std::uintptr_t>(b.p)) >>
                                      3U;
            const auto weights = static_cast<std::size_t>(a.w.r * 1000 +
                                                          a.w.i * 2000 +
                                                          b.w.r * 3000 +
                                                          b.w.i * 4000);
            return (node_pointer + weights) & CTMASK;
        }

        void clearComputeTables();

        ///
        /// Addition
        ///
    public:
        ComputeTable<vCachedEdge, vCachedEdge, vCachedEdge, computeCachedHash<vCachedEdge, vCachedEdge>, CTSLOTS> vectorAdd{};
        ComputeTable<mCachedEdge, mCachedEdge, mCachedEdge, computeCachedHash<mCachedEdge, mCachedEdge>, CTSLOTS> matrixAdd{};
        template<class Edge>
        Edge add(const Edge& x, const Edge& y) {
            [[maybe_unused]] const auto before = cn.cacheCount;

            auto result = add2(x, y);

            if (result.w != CN::ZERO) {
                cn.releaseCached(result.w);
                result.w = cn.lookup(result.w);
            }

            [[maybe_unused]] const auto after = cn.cacheCount;
            assert(after == before);

            return result;
        }

    private:
        vEdge add2(const vEdge& x, const vEdge& y);
        mEdge add2(const mEdge& x, const mEdge& y);

        ///
        /// Matrix (conjugate) transpose
        ///
    public:
        ComputeTable<mEdge, mEdge, mEdge, computeHash<mEdge, mEdge>, CTSLOTS> matrixTranspose{};
        ComputeTable<mEdge, mEdge, mEdge, computeHash<mEdge, mEdge>, CTSLOTS> conjugateMatrixTranspose{};

        mEdge transpose(const mEdge& a);
        mEdge conjugateTranspose(const mEdge& a);

        ///
        /// Multiplication
        ///
    public:
        ComputeTable<mEdge, vEdge, vCachedEdge, computeHash<mEdge, vEdge>, CTSLOTS> matrixVectorMultiplication{};
        ComputeTable<mEdge, mEdge, mCachedEdge, computeHash<mEdge, mEdge>, CTSLOTS> matrixMultiplication{};
        template<class LeftOperand, class RightOperand>
        RightOperand multiply(const LeftOperand& x, const RightOperand& y) {
            [[maybe_unused]] const auto before = cn.cacheCount;

            Qubit var = -1;
            if (!isTerminal(x)) {
                var = x.p->v;
            }
            if (!isTerminal(y) && (y.p->v) > var) {
                var = y.p->v;
            }

            auto e = multiply2(x, y, var);

            if (e.w != CN::ZERO && e.w != CN::ONE) {
                cn.releaseCached(e.w);
                e.w = cn.lookup(e.w);
            }

            [[maybe_unused]] const auto after = cn.cacheCount;
            assert(before == after);

            return e;
        }

    private:
        vEdge multiply2(const mEdge& x, const vEdge& y, Qubit var);
        mEdge multiply2(const mEdge& x, const mEdge& y, Qubit var);

        ///
        /// Inner product and fidelity
        ///
    public:
        ComputeTable<vEdge, vEdge, vCachedEdge, computeHash<vEdge, vEdge>, CTSLOTS> vectorInnerProduct{};

        ComplexValue innerProduct(const vEdge& x, const vEdge& y);
        fp           fidelity(const vEdge& x, const vEdge& y);

    private:
        ComplexValue innerProduct(const vEdge& x, const vEdge& y, Qubit var);

        ///
        /// Kronecker/tensor product
        ///
    public:
        ComputeTable<vEdge, vEdge, vCachedEdge, computeHash<vEdge, vEdge>, CTSLOTS> vectorKronecker{};
        ComputeTable<mEdge, mEdge, mCachedEdge, computeHash<mEdge, mEdge>, CTSLOTS> matrixKronecker{};
        template<class Edge>
        Edge kronecker(const Edge& x, const Edge& y) {
            auto e = kronecker2(x, y);

            if (e.w != CN::ZERO && e.w != CN::ONE) {
                cn.releaseCached(e.w);
                e.w = cn.lookup(e.w);
            }

            return e;
        }

        // extent the DD pointed to by `e` with `h` identities on top and `l` identities at the bottom
        mEdge extend(const mEdge& e, Qubit h = 0, Qubit l = 0);

    private:
        vEdge kronecker2(const vEdge& x, const vEdge& y);
        mEdge kronecker2(const mEdge& x, const mEdge& y);

        ///
        /// (Partial) trace
        ///
    public:
        mEdge        partialTrace(const mEdge& a, const std::vector<bool>& eliminate);
        ComplexValue trace(const mEdge& a);

    private:
        /// TODO: introduce a compute table for the trace?
        mEdge trace(const mEdge& a, const std::vector<bool>& eliminate, std::size_t alreadyEliminated = 0);

        ///
        /// Toffoli gates
        ///
    public:
        static constexpr std::size_t TTSLOTS = 2048;
        ToffoliTable<mEdge, TTSLOTS> toffoliTable{};

        ///
        /// Identity matrices
        ///
    public:
        // create n-qubit identity DD. makeIdent(n) === makeIdent(0, n-1)
        mEdge makeIdent(QubitCount n) { return makeIdent(0, static_cast<Qubit>(n - 1)); }
        mEdge makeIdent(Qubit leastSignificantQubit, Qubit mostSignificantQubit);

        // identity table access and reset
        [[nodiscard]] const auto& getIdentityTable() const { return IdTable; }

        void clearIdentityTable() {
            for (auto& entry: IdTable) entry.p = nullptr;
        }

    private:
        std::vector<mEdge> IdTable{};

        ///
        /// Operations (related to noise)
        ///
    public:
        static constexpr std::size_t          OperationSLOTS = 16384;
        OperationTable<mEdge, OperationSLOTS> operations{};

    private:
        ///
        /// Decision diagram size
        ///
    public:
        template<class Edge>
        unsigned int size(const Edge& e) {
            static constexpr unsigned int            NODECOUNT_BUCKETS = 200000;
            static std::unordered_set<decltype(e.p)> visited{NODECOUNT_BUCKETS}; // 2e6
            visited.max_load_factor(10);
            visited.clear();
            return nodeCount(e, visited);
        }

    private:
        template<class Edge>
        unsigned int nodeCount(const Edge& e, std::unordered_set<decltype(e.p)>& v) const {
            v.insert(e.p);
            unsigned int sum = 1;
            if (!isTerminal(e)) {
                for (const auto& edge: e.p->e) {
                    if (edge.p != nullptr && !v.count(edge.p)) {
                        sum += nodeCount(edge, v);
                    }
                }
            }
            return sum;
        }

        ///
        /// Ancillary and garbage reduction
        ///
    public:
        mEdge reduceAncillae(mEdge& e, const std::vector<bool>& ancillary, bool regular = true);

        // Garbage reduction works for reversible circuits --- to be thoroughly tested for quantum circuits
        vEdge reduceGarbage(vEdge& e, const std::vector<bool>& garbage);
        mEdge reduceGarbage(mEdge& e, const std::vector<bool>& garbage, bool regular = true);

    private:
        mEdge reduceAncillaeRecursion(mEdge& e, const std::vector<bool>& ancillary, Qubit lowerbound, bool regular = true);

        vEdge reduceGarbageRecursion(vEdge& e, const std::vector<bool>& garbage, Qubit lowerbound);
        mEdge reduceGarbageRecursion(mEdge& e, const std::vector<bool>& garbage, Qubit lowerbound, bool regular = true);

        ///
        /// Vector and matrix extraction from DDs
        ///
    public:
        /// Get a single element of the vector or matrix represented by the dd with root edge e
        /// \tparam Edge type of edge to use (vector or matrix)
        /// \param e edge to traverse
        /// \param elements string {0, 1, 2, 3}^n describing which outgoing edge should be followed
        ///        (for vectors entries are limitted to 0 and 1)
        ///        If string is longer than required, the additional characters are ignored.
        /// \return the complex amplitude of the specified element
        template<class Edge>
        ComplexValue getValueByPath(const Edge& e, const std::string& elements) {
            if (isTerminal(e)) {
                return {CN::val(e.w.r), CN::val(e.w.i)};
            }

            auto c = cn.getTempCachedComplex(1, 0);
            auto r = e;
            do {
                CN::mul(c, c, r.w);
                std::size_t tmp = elements.at(r.p->v) - '0';
                assert(tmp <= r.p->e.size());
                r = r.p->e.at(tmp);
            } while (!isTerminal(r));
            CN::mul(c, c, r.w);

            return {CN::val(c.r), CN::val(c.i)};
        }
        ComplexValue getValueByPath(const vEdge& e, size_t i);
        ComplexValue getValueByPath(const vEdge& e, const Complex& amp, size_t i);
        ComplexValue getValueByPath(const mEdge& e, size_t i, size_t j);
        ComplexValue getValueByPath(const mEdge& e, const Complex& amp, size_t i, size_t j);

        CVec getVector(const vEdge& e);
        void getVector(const vEdge& e, const Complex& amp, size_t i, CVec& vec);
        void printVector(const vEdge& e);

        CMat getMatrix(const mEdge& e);
        void getMatrix(const mEdge& e, const Complex& amp, size_t i, size_t j, CMat& mat);

        ///
        /// Debugging
        ///
    public:
        template<class Node>
        void debugnode(const Node* p) const {
            if (isTerminal(p)) {
                std::clog << "terminal\n";
                return;
            }
            std::clog << "Debug node: " << debugnode_line(p) << "\n";
            for (const auto& edge: p->e) {
                std::clog << "  " << std::hexfloat
                          << std::setw(22) << CN::val(edge.w.r) << " "
                          << std::setw(22) << CN::val(edge.w.i) << std::defaultfloat
                          << "i --> " << debugnode_line(edge.p) << "\n";
            }
            std::clog << std::flush;
        }

        template<class Node>
        std::string debugnode_line(const Node* p) const {
            if (isTerminal(p)) {
                return "terminal";
            }
            std::stringstream sst;
            sst << "0x" << std::hex << reinterpret_cast<std::uintptr_t>(p) << std::dec
                << "[v=" << static_cast<std::int_fast64_t>(p->v)
                << " ref=" << p->ref
                << " hash=" << hash(p)
                << "]";
            return sst.str();
        }

        template<class Edge>
        bool isLocallyConsistent(const Edge& e) {
            assert(CN::ONE.r->val == 1 && CN::ONE.i->val == 0);
            assert(CN::ZERO.r->val == 0 && CN::ZERO.i->val == 0);

            const bool result = isLocallyConsistent2(e);

            if (!result) {
                export2Dot(e, "locally_inconsistent.dot", true);
            }

            return result;
        }

        template<class Edge>
        bool isGloballyConsistent(const Edge& e) {
            std::map<ComplexTableEntry*, std::size_t> weight_counter{};
            std::map<decltype(e.p), std::size_t>      node_counter{};
            fillConsistencyCounter(e, weight_counter, node_counter);
            checkConsistencyCounter(e, weight_counter, node_counter);
            return true;
        }

    private:
        template<class Edge>
        bool isLocallyConsistent2(const Edge& e) {
            const auto ptr_r = CN::getAlignedPointer(e.w.r);
            const auto ptr_i = CN::getAlignedPointer(e.w.i);

            if ((ptr_r->ref == 0 || ptr_i->ref == 0) && e.w != CN::ONE && e.w != CN::ZERO) {
                std::clog << "\nLOCAL INCONSISTENCY FOUND\nOffending Number: " << e.w << " (" << ptr_r->ref << ", " << ptr_i->ref << ")\n\n";
                debugnode(e.p);
                return false;
            }

            if (isTerminal(e)) {
                return true;
            }

            if (!isTerminal(e) && e.p->ref == 0) {
                std::clog << "\nLOCAL INCONSISTENCY FOUND: RC==0\n";
                debugnode(e.p);
                return false;
            }

            for (const auto& child: e.p->e) {
                if (child.p->v + 1 != e.p->v && !isTerminal(child)) {
                    std::clog << "\nLOCAL INCONSISTENCY FOUND: Wrong V\n";
                    debugnode(e.p);
                    return false;
                }
                if (!isTerminal(child) && child.p->ref == 0) {
                    std::clog << "\nLOCAL INCONSISTENCY FOUND: RC==0\n";
                    debugnode(e.p);
                    return false;
                }
                if (!isLocallyConsistent2(child)) {
                    return false;
                }
            }
            return true;
        }

        template<class Edge>
        void fillConsistencyCounter(const Edge& edge, std::map<ComplexTableEntry*, std::size_t>& weight_map, std::map<decltype(edge.p), std::size_t>& node_map) {
            weight_map[CN::getAlignedPointer(edge.w.r)]++;
            weight_map[CN::getAlignedPointer(edge.w.i)]++;

            if (isTerminal(edge)) {
                return;
            }
            node_map[edge.p]++;
            for (auto& child: edge.p->e) {
                if (node_map[child.p] == 0) {
                    fillConsistencyCounter(child, weight_map, node_map);
                } else {
                    node_map[child.p]++;
                    weight_map[CN::getAlignedPointer(child.w.r)]++;
                    weight_map[CN::getAlignedPointer(child.w.i)]++;
                }
            }
        }

        template<class Edge>
        void checkConsistencyCounter(const Edge& edge, const std::map<ComplexTableEntry*, std::size_t>& weight_map, const std::map<decltype(edge.p), std::size_t>& node_map) {
            auto* r_ptr = CN::getAlignedPointer(edge.w.r);
            auto* i_ptr = CN::getAlignedPointer(edge.w.i);

            if (weight_map.at(r_ptr) > r_ptr->ref && r_ptr != CN::ONE.r && r_ptr != CN::ZERO.i) {
                std::clog << "\nOffending weight: " << edge.w << "\n";
                std::clog << "Bits: " << std::hexfloat << CN::val(edge.w.r) << " " << CN::val(edge.w.i) << std::defaultfloat << "\n";
                debugnode(edge.p);
                throw std::runtime_error("Ref-Count mismatch for " + std::to_string(r_ptr->val) + "(r): " + std::to_string(weight_map.at(r_ptr)) + " occurences in DD but Ref-Count is only " + std::to_string(r_ptr->ref));
            }

            if (weight_map.at(i_ptr) > i_ptr->ref && i_ptr != CN::ZERO.i && i_ptr != CN::ONE.r) {
                std::clog << edge.w << "\n";
                debugnode(edge.p);
                throw std::runtime_error("Ref-Count mismatch for " + std::to_string(i_ptr->val) + "(i): " + std::to_string(weight_map.at(i_ptr)) + " occurences in DD but Ref-Count is only " + std::to_string(i_ptr->ref));
            }

            if (isTerminal(edge)) {
                return;
            }

            if (node_map.at(edge.p) != edge.p->ref) {
                debugnode(edge.p);
                throw std::runtime_error("Ref-Count mismatch for node: " + std::to_string(node_map.at(edge.p)) + " occurences in DD but Ref-Count is " + std::to_string(edge.p->ref));
            }
            for (auto child: edge.p->e) {
                if (!isTerminal(child) && child.p->v != edge.p->v - 1) {
                    std::clog << "child.p->v == " << child.p->v << "\n";
                    std::clog << " edge.p->v == " << edge.p->v << "\n";
                    debugnode(child.p);
                    debugnode(edge.p);
                    throw std::runtime_error("Variable level ordering seems wrong");
                }
                checkConsistencyCounter(child, weight_map, node_map);
            }
        }
    };

} // namespace dd
#endif
