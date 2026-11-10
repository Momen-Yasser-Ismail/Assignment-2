#pragma once

#include <cstdint>

class ALU
{
    public:
        static std::uint8_t addinteger(std::uint8_t a, std::uint8_t b);
        static std::uint8_t addFloatingpoint(std::uint8_t a, std::uint8_t b);
        static std::uint8_t And(std::uint8_t a, std::uint8_t b);
        static std::uint8_t Or(std::uint8_t a, std::uint8_t b);
        static std::uint8_t Xor(std::uint8_t a, std::uint8_t b);
        static std::uint8_t rotateRight(std::uint8_t value, std::uint8_t steps);
};
