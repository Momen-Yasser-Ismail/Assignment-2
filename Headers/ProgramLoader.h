#pragma once

#include <cstdint>
#include <string>

class Memory;

class ProgramLoader {
public:
    bool load(const std::string& filename,
              std::uint8_t startAddress,
              Memory& memory) const;
}; 