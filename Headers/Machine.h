#pragma once // Header guard to prevent multiple inclusions

#include <string> 
#include <cstdint> // Pulls fixed-width integers to ensure hardware accuracy

#include "CPU.h"
#include "Memory.h"
#include "Screen.h"
#include "ProgramLoader.h"

class Machine {
private:
    Screen screen_;
    Memory memory_;
    CPU cpu_;
    ProgramLoader loader_;
    std::uint8_t programStart_;

public:
    Machine();

    // Starting the machine and mangement commands
    void loadProgram(const std::string& filename, std::uint8_t startAddress);
    void run();
    bool runStep();
    
    // Manual overrides and state setting
    void overwriteRegister(std::uint8_t index, std::uint8_t value);
    void overwriteMemory(std::uint8_t address, std::uint8_t value);
    void setPCToStart();

    // Read-only inspection methods (Facade pattern for UI)
    std::uint8_t getPC() const;
    std::uint16_t getIR() const;
    std::uint8_t getRegister(std::uint8_t index) const;
    const std::uint8_t* getRegisters() const; // Read-only pointer to registers if needed
    std::uint8_t getMemoryCell(std::uint8_t address) const;
    const std::uint8_t* getMemoryCells() const;
    std::string getScreenOutput() const;
    bool isHalted() const;
};