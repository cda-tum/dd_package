#ifndef QuantumGate_H
#define QuantumGate_H


#include "ComplexValue.hpp"
#include "Definitions.hpp"
#include "Control.hpp"
#include "GateMatrixDefinitions.hpp"

#include <array>
#include <vector>

namespace dd {

class QuantumGate {
public:
	std::array<ComplexValue, NEDGE> mat;
	QubitCount n;
	Qubit target;
	std::set<Control, CompareControl>  controls;

	QuantumGate(std::array<ComplexValue, NEDGE> _mat, QubitCount _n, Qubit _target)
		: mat(_mat), n(_n), target(_target) {
		//
	}

	QuantumGate(std::array<ComplexValue, NEDGE> _mat, QubitCount _n, Control _control, Qubit _target)
		: mat(_mat), n(_n), target(_target), controls(std::set<Control, CompareControl>{_control})
	{
		//
	}

	QuantumGate(std::array<ComplexValue, NEDGE> _mat, QubitCount _n, Control _control1, Control _control2, Qubit _target)
		: mat(_mat), n(_n), target(_target), controls(std::set<Control, CompareControl>{_control1, _control2})
	{
		//
	}

	QuantumGate(std::array<ComplexValue, NEDGE> _mat, QubitCount _n, Control _control1, Control _control2, Control _control3, Qubit _target)
		: mat(_mat), n(_n), target(_target), controls(std::set<Control, CompareControl>{_control1, _control2, _control3})
	{
		//
	}

	bool isControlledGate() const {
		return controls.size() != 0;
	}

	char checkPauliGate() const {
		// we're not checking for identity
		if (mat == dd::Xmat && !isControlledGate()) return 'X';
		if (mat == dd::Zmat && !isControlledGate()) return 'Z';
		if (mat == dd::Ymat && !isControlledGate()) return 'Y';
		return 0;
	}

	char checkControlledPauliGate() const {
		// check if controlled pauli where all controls are above the target
		// for now, only consider cases with single control qubit
		if (isControlledGate() && controls.size() <= 1) {
			for (auto it = controls.begin(); it != controls.end(); it++) {
				if ((int) (*it).qubit < (int) target ) return 0;
			}
			if (mat == dd::Xmat) return 'X';
			if (mat == dd::Zmat) return 'Z';
			if (mat == dd::Ymat) return 'Y';
		}
		return 0;
	}

    pauli_op isDownwardSingleControlledPauliGate() const {
        // check if controlled pauli where all controls are above the target
        // for now, only consider cases with single control qubit
        if (isControlledGate() && controls.size() <= 1) {
            for (auto it = controls.begin(); it != controls.end(); it++) {
                if ((int) (*it).qubit < (int) target ) return (pauli_op)0;
            }
            if (mat == dd::Xmat) return pauli_x;
            if (mat == dd::Zmat) return pauli_y;
            if (mat == dd::Ymat) return pauli_z;
        }
        return (pauli_op)0;
    }

    bool isUncontrolledHadamardGate() const {
        return (controls.size() == 0 && mat == dd::Hmat);
    }

	bool isCliffordGate() const {
		if (mat == dd::Hmat && !isControlledGate()) return true;
		if (mat == dd::Smat && !isControlledGate()) return true;
		if (mat == dd::Xmat && controls.size() <= 1) return true;
		if (mat == dd::Ymat && controls.size() <= 1) return true;
		if (mat == dd::Zmat && controls.size() <= 1) return true;
		return false;
	}
};


class QuantumCircuit {
public:
	QubitCount n;
	std::vector<QuantumGate> gates;

	QuantumCircuit(QubitCount _n)
		: n(_n) {
		//
	}

	void addGate(std::array<ComplexValue, NEDGE> mat, Qubit target) {
		gates.push_back(QuantumGate(mat, n, target));
		n = std::max(n, (QubitCount) target);
	}

	void addGate(std::array<ComplexValue, NEDGE> mat, Control control, Qubit target) {
		gates.push_back(QuantumGate(mat, n, control, target));
		n = std::max(n, (QubitCount) target);
		n = std::max(n, (QubitCount) control.qubit);
	}

	void addGate(std::array<ComplexValue, NEDGE> mat, Control control1, Control control2, Qubit target) {
		gates.push_back(QuantumGate(mat, n, control1, control2, target));
		n = std::max(n, (QubitCount) target);
	}

	void addGate(std::array<ComplexValue, NEDGE> mat, Control control1, Control control2, Control control3, Qubit target) {
		gates.push_back(QuantumGate(mat, n, control1, control2, control3, target));
		n = std::max(n, (QubitCount) target);
	}


};

enum CliffordGateType_t {
    cliffNoGate   = 'N',   // indicates that a gate is not a Clifford gate, i.e., "no gate"
    cliffidentity = 'I',
    cliffpauli_x  = 'X',
    cliffpauli_y  = 'Y',
    cliffpauli_z  = 'Z',
    cliffPhase    = 'P',
    cliffPhaseInv = 'Q',
    cliffHadamard = 'H',
    cliffProject0 = '0',
    cliffProject1 = '1'
};

class CliffordGate {
public:
    CliffordGateType_t gateType;
    Control control;
    Qubit target;

    CliffordGate(CliffordGateType_t _gateType, Control _control, Qubit _target)
        : gateType(_gateType), control(_control), target(_target) {
        //
    }

    CliffordGate inverse() const {
        if (gateType == cliffPhase) return CliffordGate(cliffPhaseInv, control, target);
        if (gateType == cliffPhaseInv) return CliffordGate(cliffPhase, control, target);
        return *this;
    }

    GateMatrix getGateMatrix() const {
        switch(gateType) {
            case cliffpauli_x:  return Xmat;
            case cliffpauli_y:  return Ymat;
            case cliffpauli_z:  return Zmat;
            case cliffHadamard: return Hmat;
            default:
                return Imat;
        }
    }

    bool isPauliGate() const {
        return control.qubit == (Qubit)-1 && (gateType == cliffpauli_x || gateType == cliffpauli_y || gateType == cliffpauli_z);
    }

    bool isNone() const {
        return gateType == cliffNoGate;
    }

    //static CliffordGate cliffordGateNone(CliffordGateType_t::cliffNoGate, Control{(Qubit)-1, Control::Type::pos}, -1);
    static CliffordGate cliffordGateNone() {
        return CliffordGate(cliffNoGate, Control{-1, Control::Type::pos}, -1);
    }
};

//CliffordGate CliffordGate::cliffordGateNone = CliffordGate(cliffNoGate, Control{-1, Control::Type::pos}, -1);

inline std::ostream& operator<<(std::ostream& out, const CliffordGate& gate) {
    out << (char)gate.gateType << "[" << (int)gate.target;
    if (gate.control.qubit != -1) {
        out << " | " << ( (bool)gate.control.type ? "+" : "-") << (int)gate.control.qubit << "]";
    } else {
        out << "]";
    }
    return out;
}

}


#endif
