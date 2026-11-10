#pragma once

#include <cstdint>
#include "Memory.h"

class CPU {
private:
    std::uint8_t pc;
    std::uint16_t ir;
    std::uint8_t registers[16];
    bool halted;
    Memory& memory;

public:
    CPU(Memory& memory);
    bool fetch();
    void execute();
    bool isValid(std::uint16_t ir);
    
    std::uint8_t getPC() const;
    std::uint16_t getIR() const;
    std::uint8_t getRegister(std::uint8_t index) const;
    const std::uint8_t* getRegisters() const;
    bool isHalted() const;

    void setPC(std::uint8_t address);
    void setHalted(bool h); // Resets the halt state for consecutive program runs
    void step();
    void setRegister(std::uint8_t index, std::uint8_t value);
};