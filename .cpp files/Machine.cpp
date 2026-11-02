#include "Machine.h"

// Initilaizing the constructor:
Machine::Machine() 
    : screen_(), memory_(screen_), cpu_(memory_), loader_(), programStart_(0) {}

// Program Loading:
void Machine::loadProgram(const std::string& filename, std::uint8_t startAddress) {
    programStart_ = loader_.load(filename, startAddress, memory_);
    screen_.clear();
    cpu_.restart(startAddress);
}

// Execution Controls ( 2 Options ):

// Option A: Compile all at once
void Machine::run() {
    cpu_.run();
}

// Option B: Compile Step by step or line by line
bool Machine::runStep() {
    cpu_.step();
    return !cpu_.isHalted();
}

// Manual overrides and resets:
void Machine::overwriteRegister(std::uint8_t index, std::uint8_t value) {
    cpu_.writeRegister(index, value);
}

void Machine::overwriteMemory(std::uint8_t address, std::uint8_t value) {
    memory_.write(address, value);
}

void Machine::setPCToStart() {
    cpu_.restart(programStart_);
}

// The safe inspectors ( So the UI can peak at the hardware without messing with anything directrly ):
std::uint8_t Machine::getPC() const {
    return cpu_.getPC();
}

std::uint16_t Machine::getIR() const {
    return cpu_.getIR();
}

std::uint8_t Machine::getRegister(std::uint8_t index) const {
    return cpu_.readRegister(index);
}

const std::uint8_t* Machine::getRegisters() const {
    return nullptr; 
}

std::uint8_t Machine::getMemoryCell(std::uint8_t address) const {
    return memory_.read(address);
}

const std::uint8_t* Machine::getMemoryCells() const {
    return memory_.getCells(); 
}

std::string Machine::getScreenOutput() const {
    return screen_.getContent();
}

bool Machine::isHalted() const {
    return cpu_.isHalted();
}