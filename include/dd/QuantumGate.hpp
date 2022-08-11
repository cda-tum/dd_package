#ifndef QuantumGate_H
#define QuantumGate_H


#include "ComplexValue.hpp"
#include "Definitions.hpp"
#include "Control.hpp"

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

}


#endif
