#pragma once

#include <cstdint>
#include <iostream>

class RegisterFile 
{
private:
    std::uint8_t registers[16];

public:
    RegisterFile();

    std::uint8_t getRegister(std::uint8_t index) const;
    void setRegister(std::uint8_t index, std::uint8_t value);
    const std::uint8_t* getRegisters() const;
    void clear();
};