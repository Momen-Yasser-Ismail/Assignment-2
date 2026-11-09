#pragma once
#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <string>
#include <cstdint>

class Memory
{
private:
    std::uint8_t cells[256];
    std::string screenoutput;

public:
    Memory();

    std::uint8_t read(std::uint8_t address);
    void write(std::uint8_t address, std::uint8_t value);

    const std::uint8_t *getCells() const;
    std::string getScreenOutput() const;
    void clear();
};

#endif