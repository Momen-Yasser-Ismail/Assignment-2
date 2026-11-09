#include "../Headers/ConsoleRenderer.h"
#include "../Headers/Machine.h"
#include "../Headers/Hex.h"

#include <cstdint>
#include <iostream>

void ConsoleRenderer::displayMemory(const Machine& machine) const {
    const std::uint8_t* cells = machine.getMemoryCells();

    std::cout << "\n========== MEMORY ==========\n";
    if (cells == nullptr) {
        std::cout << "Memory data is unavailable.\n";
        return;
    }

    for (int row = 0; row < 16; ++row) {
        std::cout << toHex(static_cast<std::uint32_t>(row * 16), 2) << " | ";
        for (int col = 0; col < 16; ++col) {
            const int address = row * 16 + col;
            std::cout << toHex(cells[address], 2) << ' ';
        }
        std::cout << '\n';
    }
}

void ConsoleRenderer::displayRegisters(const Machine& machine) const {
    std::cout << "\n========== REGISTERS ==========\n";
    for (std::uint8_t i = 0; i < 16; ++i) {
        std::cout << 'R' << toHex(i, 1) << ": "
                  << toHex(machine.getRegister(i), 2) << "   ";
        if ((i + 1) % 4 == 0) {
            std::cout << '\n';
        }
    }
}

void ConsoleRenderer::displayCPU(const Machine& machine) const {
    std::cout << "\n========== CPU ==========\n"
              << "PC: 0x" << toHex(machine.getPC(), 2) << '\n'
              << "IR: 0x" << toHex(machine.getIR(), 4) << '\n'
              << "Halted: " << (machine.isHalted() ? "Yes" : "No") << '\n';
}

void ConsoleRenderer::displayScreen(const Machine& machine) const {
    std::cout << "\n========== SCREEN OUTPUT ==========\n";
    const std::string output = machine.getScreenOutput();
    std::cout << (output.empty() ? "(empty)" : output) << '\n';
}
