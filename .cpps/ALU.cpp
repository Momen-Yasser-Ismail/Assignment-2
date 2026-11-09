#include "../Headers/ALU.h"

#include <cmath>

std::uint8_t ALU::addFloatingpoint(std::uint8_t val1, std::uint8_t val2) {
    if (val1 == 0) return val2;
    if (val2 == 0) return val1;

    // Extract components for val1
    int s1 = (val1 >> 7) & 1;
    int e1 = ((val1 >> 4) & 7) - 4; // excess-4 bias
    int m1 = val1 & 0x0F;

    // Extract components for val2
    int s2 = (val2 >> 7) & 1;
    int e2 = ((val2 >> 4) & 7) - 4;
    int m2 = val2 & 0x0F;

    // Convert to signed actual values
    double v1 = (s1 ? -1.0 : 1.0) * (m1 / 16.0) * std::pow(2.0, e1);
    double v2 = (s2 ? -1.0 : 1.0) * (m2 / 16.0) * std::pow(2.0, e2);
    double sum = v1 + v2;

    if (sum == 0.0) return 0x00;

    // Encode result back into 8-bit Vole float format
    int resSign = (sum < 0.0) ? 1 : 0;
    sum = std::abs(sum);

    int resExp = 0;
    while (sum >= 1.0) {
        sum /= 2.0;
        resExp++;
    }
    while (sum < 0.5 && resExp > -4) {
        sum *= 2.0;
        resExp--;
    }

    int biasedExp = resExp + 4;
    if (biasedExp > 7) biasedExp = 7; // Overflow cap
    if (biasedExp < 0) biasedExp = 0; // Underflow cap

    int resMantissa = static_cast<int>(std::round(sum * 16.0));
    if (resMantissa > 15) resMantissa = 15;

    return static_cast<std::uint8_t>((resSign << 7) | (biasedExp << 4) | resMantissa);
}