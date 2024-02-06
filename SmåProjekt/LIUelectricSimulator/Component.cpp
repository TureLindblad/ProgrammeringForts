#include "Component.h"

Component::Component(std::string name, double componentValue, std::shared_ptr<Connection> terminalA, std::shared_ptr<Connection> terminalB) {
	name_ = name;
	componentValue_ = componentValue;
	terminalA_ = terminalA;
	terminalB_ = terminalB;
}

std::string Component::GetName() const
{
	return name_;
}

double Component::GetComponentValue() const {
	return componentValue_;
}

std::shared_ptr<Connection> Component::GetTerminalA() const {
	return terminalA_;
}

std::shared_ptr<Connection> Component::GetTerminalB() const {
	return terminalB_;
}

void Component::SetTerminalA(double voltage) {
	terminalA_->voltage = voltage;
}

void Component::SetTerminalB(double voltage) {
	terminalB_->voltage = voltage;
}

void Battery::MoveCharge() {
	this->SetTerminalA(this->GetComponentValue());
	this->SetTerminalB(0.0);
}

void Resistor::MoveCharge() {
	double chargeA = this->GetTerminalA()->voltage;
	double chargeB = this->GetTerminalB()->voltage;
	double resistance = this->GetComponentValue();

	double current = ((std::max(chargeA, chargeB) - std::min(chargeA, chargeB)) / resistance) * 0.1;

	if (chargeA < chargeB) {
		SetTerminalA(this->GetTerminalA()->voltage + current);
		SetTerminalB(this->GetTerminalB()->voltage - current);
	}
	else {
		SetTerminalB(this->GetTerminalB()->voltage + current);
		SetTerminalA(this->GetTerminalA()->voltage - current);
	}
}

void Capacitor::MoveCharge() {
	double chargeA = this->GetTerminalA()->voltage;
	double chargeB = this->GetTerminalB()->voltage;
	double fahrad = this->GetComponentValue();

	double toBeStored = (std::max(chargeA, chargeB) - std::min(chargeA, chargeB) - this->storedCharge) * fahrad * 0.1;

	this->storedCharge += toBeStored;

	if (chargeA < chargeB) {
		SetTerminalA(this->GetTerminalA()->voltage + toBeStored);
		SetTerminalB(this->GetTerminalB()->voltage - toBeStored);
	}
	else {
		SetTerminalB(this->GetTerminalB()->voltage + toBeStored);
		SetTerminalA(this->GetTerminalA()->voltage - toBeStored);
	}
}