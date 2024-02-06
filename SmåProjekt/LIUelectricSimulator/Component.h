#include <string>
#include <memory>
#pragma once
struct Connection {
	std::string name;
	double voltage;

	Connection(const std::string& name, const double& voltage)
		: name(name), voltage(voltage) {}
};

class Component
{
private:
	std::string name_;
	double componentValue_;
	
	std::shared_ptr<Connection> terminalA_;
	std::shared_ptr<Connection> terminalB_;
public:
	Component(std::string name, double componentValue, std::shared_ptr<Connection> terminalA, std::shared_ptr<Connection> terminalB);
	std::string GetName() const;
	double GetComponentValue() const;
	std::shared_ptr<Connection> GetTerminalA() const;
	std::shared_ptr<Connection> GetTerminalB() const;
	void SetTerminalA(double voltage);
	void SetTerminalB(double voltage);
	virtual void MoveCharge() = 0;
};

class Battery : public Component {
public:
	Battery(std::string name, double componentValue, std::shared_ptr<Connection> terminalA, std::shared_ptr<Connection> terminalB)
		: Component(name, componentValue, terminalA, terminalB) {
	}
	void MoveCharge() override;
};

class Resistor : public Component {
public:
	Resistor(std::string name, double componentValue, std::shared_ptr<Connection> terminalA, std::shared_ptr<Connection> terminalB)
		: Component(name, componentValue, terminalA, terminalB) {
	}
	void MoveCharge() override;
};

class Capacitor : public Component {
private:
	double storedCharge;
public:
	Capacitor(std::string name, double componentValue, std::shared_ptr<Connection> terminalA, std::shared_ptr<Connection> terminalB)
		: Component(name, componentValue, terminalA, terminalB) {
		storedCharge = 0.0;
	}
	void MoveCharge() override;
};

