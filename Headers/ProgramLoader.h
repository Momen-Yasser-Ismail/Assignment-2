#pragma once
#ifndef PROGRAM_LOADER_H
#define PROGRAM_LOADER_H

#include <cstdint>
#include <string>

class Memory;

class ProgramLoader {
public:
    bool load(const std::string& filename,
              std::uint8_t startAddress,
              Memory& memory) const;
}; 

#endif