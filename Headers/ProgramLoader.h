#ifndef ProgramLoader_H
#define ProgramLoader_H

#include <cstdint>
#include <string>

class Memory; // forward declaration of memory class will be used later.


class ProgramLoader { // The loader validates the complete file before writing any byte in memory "all or nothing".
public:
    bool load(const std::string& filename,
              std::uint8_t startAddress,
              Memory& memory) const;

private: 
    static std::string trim(const std::string& text); // delete the spaces
    static bool parseInstruction(const std::string& line,
                                 std::uint16_t& instruction,
                                 int lineNumber); // parse:"analyze" the instruction and return true if it is valid, false otherwise.
    static void validateStartAddress(std::uint8_t startAddress); // Ensure that the starting address is permitted and not reserved.
}; 

#endif
