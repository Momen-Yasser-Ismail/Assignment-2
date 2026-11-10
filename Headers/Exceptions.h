#pragma once

#include <cstdint>
#include <stdexcept>
#include <string>
#include "Hex.h"

class ProgramLoadException : public std::runtime_error {
public:
    explicit ProgramLoadException(const std::string& message)
        : std::runtime_error(message) {}
};

class InvalidInstructionException : public std::runtime_error {
public:
    explicit InvalidInstructionException(std::uint16_t instruction, int lineNumber = -1)
        : std::runtime_error(makeMessage(instruction, lineNumber)) {}

private:
    static std::string makeMessage(std::uint16_t instruction, int lineNumber) {
        std::string message = "Invalid instruction 0x" + toHex(instruction, 4);
        if (lineNumber >= 0) {
            message += " at line " + std::to_string(lineNumber);
        }
        return message;
    }
};
