#pragma once
#include "Memory.h"


class CPU{
    private:
        uint8_t pc;
        uint16_t ir;
        uint8_t registers[16];
        bool halted;
        Memory& memory;
    public:
        CPU(Memory&memory);
        bool fetch();
        void execute();
        bool isValid(uint16_t ir);
        uint8_t getPC();
        void setPC(uint8_t address);
        uint16_t getIR();
        void step();
        uint8_t getRegister(uint8_t index);
        void setRegister(uint8_t index , uint8_t value);
        bool isHalted();


};
