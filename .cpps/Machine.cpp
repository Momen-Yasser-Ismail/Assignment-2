#include "../Headers/Machine.h"

Machine::Machine() 
    : screen_(), memory_(), cpu_(memory_), loader_(), programStart_(0), programLoaded_(false) {}

bool Machine::loadProgram(const std::string& filename, std::uint8_t startAddress) {
    cpu_.setHalted(false);
    
    // Clear memory (which resets screenoutput to "") and screen buffers[cite: 32]
    memory_.clear();
    screen_.clear();
    
    loader_.load(filename, startAddress, memory_);
    
    cpu_.setPC(startAddress);
    programStart_ = startAddress;
    programLoaded_ = true; 
    return true; 
}

void Machine::run() {
    cpu_.setHalted(false);
    
    while (!cpu_.isHalted()) {
        cpu_.step();
    }
}

bool Machine::runStep() {
    if (cpu_.isHalted()) return false;
    cpu_.step();
    return !cpu_.isHalted();
}

void Machine::resetAll() {
    memory_.clear();
    screen_.clear();
    cpu_.setPC(0);
    cpu_.setHalted(false);
    for (int i = 0; i < 16; ++i) {
        cpu_.setRegister(static_cast<std::uint8_t>(i), 0);
    }
    programStart_ = 0;
    programLoaded_ = false; 
}

void Machine::overwriteRegister(std::uint8_t index, std::uint8_t value) {
    cpu_.setRegister(index, value);
}

void Machine::overwriteMemory(std::uint8_t address, std::uint8_t value) {
    memory_.write(address, value);
}

void Machine::setPCToStart() {
    cpu_.setPC(programStart_);
}

std::uint8_t Machine::getPC() const {
    return cpu_.getPC();
}

std::uint16_t Machine::getIR() const {
    return cpu_.getIR();
}

std::uint8_t Machine::getRegister(std::uint8_t index) const {
    return cpu_.getRegister(index);
}

const std::uint8_t* Machine::getRegisters() const {
    return cpu_.getRegisters(); 
}

std::uint8_t Machine::getMemoryCell(std::uint8_t address) const {
    return const_cast<Memory&>(memory_).read(address);
}

const std::uint8_t* Machine::getMemoryCells() const {
    return memory_.getCells(); 
}

std::string Machine::getScreenOutput() const {
    return memory_.getScreenOutput();
}

bool Machine::isHalted() const {
    return cpu_.isHalted();
}