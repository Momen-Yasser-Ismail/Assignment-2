#pragma once
#ifndef HEX_H
#define HEX_H

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

inline std::string toHex(std::uint32_t value, int width = 2) {
    std::stringstream stream;
    stream << std::uppercase << std::hex
           << std::setfill('0') << std::setw(width) << value;
    return stream.str();
}

#endif