#include "../Headers/ProgramLoader.h"
#include "../Headers/Memory.h"
#include "../Headers/CPU.h"
#include "../Headers/Exceptions.h"
#include "../Headers/Hex.h"

#include <fstream>
#include <sstream>
#include <algorithm>
#include <cctype>
#include <vector>

bool ProgramLoader::load(const std::string& filename, std::uint8_t startAddress, Memory& memory) const {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ProgramLoadException("Program is not correct: Cannot open file " + filename);
    }

    std::string line;
    int lineNumber = 0;
    
    struct InstructionEntry {
        std::uint8_t high;
        std::uint8_t low;
    };
    std::vector<InstructionEntry> parsedInstructions;

    while (std::getline(file, line)) {
        lineNumber++;

        // Strip comments starting with ';' or '#'
        size_t commentPos = line.find_first_of(";#");
        if (commentPos != std::string::npos) {
            line = line.substr(0, commentPos);
        }

        // Trim leading and trailing whitespace (including carriage returns \r)
        line.erase(line.begin(), std::find_if(line.begin(), line.end(), [](unsigned char ch) {
            return !std::isspace(ch);
        }));
        line.erase(std::find_if(line.rbegin(), line.rend(), [](unsigned char ch) {
            return !std::isspace(ch);
        }).base(), line.end());

        // Skip blank lines safely
        if (line.empty()) {
            continue;
        }

        std::stringstream ss(line);
        std::string token;
        while (ss >> token) {
            if (token.length() != 4) {
                throw ProgramLoadException("Program is not correct: Invalid instruction length at line " + std::to_string(lineNumber) + " (Expected 4 hex digits).");
            }

            for (char c : token) {
                if (!isxdigit(static_cast<unsigned char>(c))) {
                    throw ProgramLoadException("Program is not correct: Non-hexadecimal character found at line " + std::to_string(lineNumber) + ".");
                }
            }

            std::uint16_t instruction = 0;
            std::stringstream converter(token);
            if (!(converter >> std::hex >> instruction)) {
                throw ProgramLoadException("Program is not correct: Failed to parse instruction at line " + std::to_string(lineNumber) + ".");
            }

            std::uint8_t opcode = (instruction >> 12) & 0xF;
            if (opcode < 1 || opcode > 0xC) {
                throw ProgramLoadException("Program is not correct: Invalid opcode '0x" + toHex(opcode, 1) + "' at line " + std::to_string(lineNumber) + ".");
            }

            if (startAddress + (parsedInstructions.size() * 2) + 1 > 0xFF) {
                throw ProgramLoadException("Program is not correct: Exceeds maximum memory capacity (0xFF).");
            }

            std::uint8_t highByte = static_cast<std::uint8_t>((instruction >> 8) & 0xFF);
            std::uint8_t lowByte = static_cast<std::uint8_t>(instruction & 0xFF);

            parsedInstructions.push_back({highByte, lowByte});
        }
    }

    if (parsedInstructions.empty()) {
        throw ProgramLoadException("Program is not correct: File contains no valid instructions.");
    }

    // Write to memory only after full validation passes successfully
    std::uint16_t writeAddress = startAddress;
    for (const auto& entry : parsedInstructions) {
        memory.write(writeAddress, entry.high);
        memory.write(writeAddress + 1, entry.low);
        writeAddress += 2;
    }

    return true;
}