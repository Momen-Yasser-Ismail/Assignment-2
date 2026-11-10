#pragma once

#include "Machine.h"
#include "ConsoleRenderer.h"
#include <string>

class ConsoleUI {
public:
    explicit ConsoleUI(Machine& machine);
    void start();

private:
    Machine& machine;
    ConsoleRenderer renderer;

    void showMenu() const;
    void handleLoadProgram();
    void handleRun();
    void handleStep();
    void displayMemory() const;
    void displayRegisters() const;
    void displayCPU() const;
    void displayScreen() const;
    void displayAll() const;
};
