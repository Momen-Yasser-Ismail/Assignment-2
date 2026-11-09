#pragma once
#ifndef CONSOLE_RENDERER_H
#define CONSOLE_RENDERER_H

class Machine;

class ConsoleRenderer {
public:
    void displayMemory(const Machine& machine) const;
    void displayRegisters(const Machine& machine) const;
    void displayCPU(const Machine& machine) const;
    void displayScreen(const Machine& machine) const;
};

#endif