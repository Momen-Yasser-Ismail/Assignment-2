#ifndef ConsoleRenderer_H
#define ConsoleRenderer_H

class Machine; // forward declaration of Machine class will be used later.

// Rendering only: this class reads Machine's public getters and never changes state.
class ConsoleRenderer {
public:
    void displayMemory(const Machine& machine) const;
    void displayRegisters(const Machine& machine) const;
    void displayCPU(const Machine& machine) const;
    void displayScreen(const Machine& machine) const;
};

#endif
