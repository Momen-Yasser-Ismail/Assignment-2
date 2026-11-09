#pragma once
#ifndef MACHINE_H
#define MACHINE_H

#include <string>
#include <cstdint>
#include "Screen.h"
#include "Memory.h"
#include "CPU.h"
#include "ProgramLoader.h"

class Machine {
private:
    Screen screen_;
    Memory memory_;
    CPU cpu_;
    ProgramLoader loader_;
    std::uint8_t programStart_;
    bool programLoaded_;

public:
    Machine();

    bool loadProgram(const std::string& filename, std::uint8_t startAddress);
    void run();
    bool runStep();
    void resetAll();

    void setProgramLoaded(bool loaded) { programLoaded_ = loaded; }
    bool isProgramLoaded() const { return programLoaded_; }

    void overwriteRegister(std::uint8_t index, std::uint8_t value);
    void overwriteMemory(std::uint8_t address, std::uint8_t value);
    void setPCToStart();

    std::uint8_t getPC() const;
    std::uint16_t getIR() const;
    std::uint8_t getRegister(std::uint8_t index) const;
    const std::uint8_t* getRegisters() const;
    std::uint8_t getMemoryCell(std::uint8_t address) const;
    const std::uint8_t* getMemoryCells() const;
    std::string getScreenOutput() const;
    bool isHalted() const;
};

#endif