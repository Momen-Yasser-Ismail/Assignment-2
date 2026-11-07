#include "ProgramLoader.h"

#include "Memory.h"
#include "Exceptions.h"
#include "InstructionDecoder.h"

#include <cctype>
#include <fstream>
#include <string>
#include <vector>

std::string ProgramLoader::trim(const std::string& text) {
    const std::size_t first = text.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) {
        return {};
    }
    const std::size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}// return the string after deleting the spaces from the beginning and end of the string.

bool ProgramLoader::parseInstruction(const std::string& originalLine,
                                     std::uint16_t& instruction,
                                     int lineNumber) {
    std::string line = originalLine;

    const std::size_t comment = line.find(';');
    if (comment != std::string::npos) {
        line.erase(comment);
    }

    line = trim(line);
    if (line.empty()) {
        return false;
    }// delete comments after ; and trim the line then if the line is empty return false.

    if (line.size() != 4) {
        throw ProgramLoadException(
            "Line " + std::to_string(lineNumber) +
            ": an instruction must contain exactly four hexadecimal digits.");
    }// ensure that the instruction is exactly 4 hexadecimal digits, otherwise throw an exception.

    std::uint16_t value = 0;
    for (char ch : line) {
        const unsigned char c = static_cast<unsigned char>(ch);
        if (!std::isxdigit(c)) {
            throw ProgramLoadException(
                "Line " + std::to_string(lineNumber) +
                ": invalid hexadecimal character.");
        }// ensure that the instruction contains only valid hexadecimal characters, otherwise throw an exception.

        const unsigned int digit =
            std::isdigit(c) ? static_cast<unsigned int>(ch - '0')
                            : static_cast<unsigned int>(
                                  std::tolower(c) - 'a' + 10);
        value = static_cast<std::uint16_t>((value << 4) | digit);
    }// convert the hexadecimal string to a 16-bit unsigned integer.

    const std::uint8_t highByte = static_cast<std::uint8_t>(value >> 8);
    const std::uint8_t lowByte = static_cast<std::uint8_t>(value & 0xFF);

    // Assumed shared interface of the InstructionDecoder owned by the CPU team.
    if (!InstructionDecoder::isValid(highByte, lowByte)) {
        throw InvalidInstructionException(value, lineNumber);
    }

    instruction = value;
    return true;
}

void ProgramLoader::validateStartAddress(std::uint8_t startAddress) { // ensure that start address is even and less than 0xFF, otherwise throw an exception.
    if ((startAddress % 2) != 0) {
        throw ProgramLoadException("Start address must be even.");
    }

    // 0xFF is reserved as the screen output port.
    if (startAddress >= 0xFF) {
        throw ProgramLoadException("Start address must be less than 0xFF.");
    }
}

bool ProgramLoader::load(const std::string& filename,
                         std::uint8_t startAddress,
                         Memory& memory) const { // load the program from the file into memory starting at startAddress, validate the program and throw exceptions if there are any issues.
    validateStartAddress(startAddress);

    std::ifstream file(filename);
    if (!file.is_open()) {
        throw ProgramLoadException("Cannot open program file: " + filename);
    }

    // Stage all bytes first: invalid input must not partially modify Memory.
    std::vector<std::uint8_t> programBytes;
    std::string line;
    int lineNumber = 0;

    while (std::getline(file, line)) { // read the file line by line, increment the line number, parse the instruction and if valid.
        ++lineNumber;

        std::uint16_t instruction = 0;
        if (!parseInstruction(line, instruction, lineNumber)) {
            continue;
        }

        programBytes.push_back(static_cast<std::uint8_t>(instruction >> 8));
        programBytes.push_back(static_cast<std::uint8_t>(instruction & 0xFF));
    }

    if (file.bad()) {
        throw ProgramLoadException("Error while reading program file.");
    }

    if (programBytes.empty()) {
        throw ProgramLoadException("Program file contains no instructions.");
    }

    // Writable program addresses are startAddress through 0xFE.
    const std::size_t available =
        static_cast<std::size_t>(0xFF - startAddress);

    if (programBytes.size() > available) {
        throw ProgramLoadException(
            "Program does not fit in memory before screen port 0xFF.");
    }

    for (std::size_t i = 0; i < programBytes.size(); ++i) {
        const auto address = static_cast<std::uint8_t>(
            static_cast<std::size_t>(startAddress) + i);
        memory.write(address, programBytes[i]);
    } // write the program bytes to memory starting at startAddress. 

    return true;
}
