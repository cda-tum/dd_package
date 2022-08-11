#ifndef DDPACKAGE_PHASEUTILITIES_HPP
#define DDPACKAGE_PHASEUTILITIES_HPP

#include "Definitions.hpp"

namespace dd {

    inline phase_t multiplyPhases(phase_t a, phase_t b) {
        //  short x = (short) a;
        //  short y = (short) b;
        //  short xy = ((x & 0x1) ^ (y & 0x1)) | ((x & 0x2) ^ (y & 0x2) ^ ((x & y & 0x1) << 1));
        //  return (phase_t) xy;
        return (phase_t)(((int)a + (int)b) & 0x3);
    }

    inline void multiplyPhaseObjectBy(phase_t& a, phase_t b) {
        a = (phase_t)(((int)a + (int)b) & 0x3);
    }

    inline phase_t getPhaseInverse(phase_t a) {
        //      int A = (int) a;
        //      A = (A & 0x1) | ( ((A&1) << 1) ^ (A&2) );
        //      return (phase_t) A;
        return (phase_t)((4 - (int)a) & 0x3);
    }

    inline phase_t getPhaseaMinusB(phase_t a, phase_t b) {
        phase_t minb = getPhaseInverse(b);
        return (phase_t)((a + minb) & 0x3);
    }

    inline std::string phaseToString(phase_t a) {
        switch (a) {
            case phase_t::phase_one:
                return "+1";
            case phase_t::phase_i:
                return "i";
            case phase_t::phase_minus_one:
                return "-1";
            case phase_t::phase_minus_i:
                return "-i";
            case phase_t::no_phase:;
        }
        return "(no phase)";
    }

} // namespace dd

#endif
