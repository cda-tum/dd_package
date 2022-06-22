/*
* This file is part of the MQT DD Package which is released under the MIT license.
* See file README.md or go to https://www.cda.cit.tum.de/research/quantum_dd/ for more information.
*/

#ifndef DDSIM_NOISEFUNCTIONALITY_HPP
#define DDSIM_NOISEFUNCTIONALITY_HPP

#include "Package.hpp"


namespace dd {
    // noise operations available for deterministic noise aware quantum circuit simulation
    enum noiseOperations : std::uint8_t {
        amplitudeDamping,
        phaseFlip,
        depolarization
    };


}



#endif //DDSIM_NOISEFUNCTIONALITY_HPP
