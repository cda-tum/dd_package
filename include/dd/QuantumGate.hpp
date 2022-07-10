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

	bool isControlledGate() const {
		return controls.size() != 0;
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

};

}


#endif
