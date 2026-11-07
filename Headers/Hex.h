#ifndef Hex_H
#define Hex_H

#include <cstdint>
#include <iomanip>
#include <sstream>
#include <string>

inline std::string toHex(std::uint32_t value, int width = 2) { // function with default width = 2
    std::stringstream stream; // temporary string stream to format the output
    stream << std::uppercase << std::hex
           << std::setfill('0') << std::setw(width) << value;
           // set the stream to uppercase "capital letters in hexa(A-F)",
           // convert from decimal to hexadecimal,
           // fill with '0',
           // set width,
           // use all the setting to format the value on the stream.

    return stream.str(); // return converted value as string
}

#endif
