/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#include "Definitions.hpp"
#include "LimTable.hpp"
#include "LimCache.hpp"

#include <cassert>
#include <cstddef>
#include <vector>

#ifndef DDPACKAGE_LIMFUNCTIONALITY_HPP
#define DDPACKAGE_LIMFUNCTIONALITY_HPP


namespace dd {

    struct LimFunctionality {
        LimTable<> limTable{};
        LimCache<> limCache{};

        LimFunctionality()  = default;
        ~LimFunctionality() = default;

        void clear() {
            limTable.clear();
            limCache.clear();
        }

        [[nodiscard]] std::size_t cacheCount() const {
            return limCache.getCount();
        }
    };

} // namespace dd

#endif //DDPACKAGE_LIMFUNCTIONALITY_HPP