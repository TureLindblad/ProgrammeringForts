#include "Component.h"
#include <iostream>
#include <iomanip>
#include <vector>

static void CreateCircuit1(std::vector<std::shared_ptr<Component>>& circuitBoard);
static void CreateCircuit2(std::vector<std::shared_ptr<Component>>& circuitBoard);
static void CreateCircuit3(std::vector<std::shared_ptr<Component>>& circuitBoard);
static void Simulate(std::vector<std::shared_ptr<Component>>& circuitBoard, int iterations, int printLines, double timeStep);

int main()
{
    std::vector<std::shared_ptr<Component>> circuitBoard;
    
    //CreateCircuit1(circuitBoard);
    //CreateCircuit2(circuitBoard);
    CreateCircuit3(circuitBoard);
    
    Simulate(circuitBoard, 200000, 10, 0.1);
}

static void CreateCircuit1(std::vector<std::shared_ptr<Component>>& circuitBoard) { 
    std::shared_ptr<Connection> p = std::make_shared<Connection>("p", 0.0);
    std::shared_ptr<Connection> n = std::make_shared<Connection>("n", 0.0);
    std::shared_ptr<Connection> r124 = std::make_shared<Connection>("r124", 0.0);
    std::shared_ptr<Connection> r23 = std::make_shared<Connection>("r23", 0.0);

    circuitBoard.push_back(std::make_shared<Battery>("Bat", 24.0, p, n));
    circuitBoard.push_back(std::make_shared<Resistor>("R1", 6.0, p, r124));
    circuitBoard.push_back(std::make_shared<Resistor>("R2", 4.0, r124, r23));
    circuitBoard.push_back(std::make_shared<Resistor>("R3", 8.0, r23, n));
    circuitBoard.push_back(std::make_shared<Resistor>("R4", 12.0, r124, n));
}

static void CreateCircuit2(std::vector<std::shared_ptr<Component>>& circuitBoard) {
    std::shared_ptr<Connection> p = std::make_shared<Connection>("p", 0.0);
    std::shared_ptr<Connection> n = std::make_shared<Connection>("n", 0.0);
    std::shared_ptr<Connection> l = std::make_shared<Connection>("l", 0.0);
    std::shared_ptr<Connection> r = std::make_shared<Connection>("r", 0.0);

    circuitBoard.push_back(std::make_shared<Battery>("Bat", 24.0, p, n));
    circuitBoard.push_back(std::make_shared<Resistor>("R1", 150.0, p, l));
    circuitBoard.push_back(std::make_shared<Resistor>("R2", 50.0, p, r));
    circuitBoard.push_back(std::make_shared<Resistor>("R3", 100.0, r, l));
    circuitBoard.push_back(std::make_shared<Resistor>("R4", 300.0, l, n));
    circuitBoard.push_back(std::make_shared<Resistor>("R5", 250.0, r, n));
}

static void CreateCircuit3(std::vector<std::shared_ptr<Component>>& circuitBoard) {
    std::shared_ptr<Connection> p = std::make_shared<Connection>("p", 0.0);
    std::shared_ptr<Connection> n = std::make_shared<Connection>("n", 0.0);
    std::shared_ptr<Connection> l = std::make_shared<Connection>("l", 0.0);
    std::shared_ptr<Connection> r = std::make_shared<Connection>("r", 0.0);

    circuitBoard.push_back(std::make_shared<Battery>("Bat", 24.0, p, n));
    circuitBoard.push_back(std::make_shared<Resistor>("R1", 150.0, p, l));
    circuitBoard.push_back(std::make_shared<Resistor>("R2", 50.0, p, r));
    circuitBoard.push_back(std::make_shared<Capacitor>("C3", 1.0, r, l));
    circuitBoard.push_back(std::make_shared<Resistor>("R4", 300.0, l, n));
    circuitBoard.push_back(std::make_shared<Capacitor>("C5", 0.75, r, n));
}

static void Simulate(std::vector<std::shared_ptr<Component>>& circuitBoard, int iterations, int printLines, double timeStep) {
    int counter = 0;

    for (std::shared_ptr<Component> comp : circuitBoard) {
        std::cout << comp->GetName() << "     ";
    }

    std::cout << "\n";

    for (int i = 0; i < iterations; i++) {
        counter++;
        for (std::shared_ptr<Component> comp : circuitBoard) {
            comp->MoveCharge();
            if (counter == iterations / printLines) {
                double componentVoltage = comp->GetTerminalA()->voltage - comp->GetTerminalB()->voltage;
                std::cout << std::setprecision(2) << std::fixed << componentVoltage << "   ";
            }
        }
        if (counter == iterations / printLines) {
            std::cout << "\n";
            counter = 0;
        }
    }
}