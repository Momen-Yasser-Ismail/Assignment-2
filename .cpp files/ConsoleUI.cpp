#include "ConsoleUI.h"

#include <exception>
#include <iostream>
#include <limits>
#include <string>

ConsoleUI::ConsoleUI(Machine& machine)
    : machine(machine) {}

void ConsoleUI::showMenu() const {
    std::cout << "\n========== VOLE MACHINE ==========\n"
              << "1. Load Program\n"
              << "2. Run Program\n"
              << "3. Run One Step\n"
              << "4. Display Memory\n"
              << "5. Display Registers\n"
              << "6. Display CPU (PC / IR)\n"
              << "7. Display Screen Output\n"
              << "8. Display All\n"
              << "9. Reset Machine\n"
              << "0. Exit\n"
              << "Choice: ";
}

void ConsoleUI::handleLoadProgram() {
    std::string filename;
    unsigned int address = 0;

    std::cout << "Enter program filename: ";
    std::getline(std::cin, filename);

    std::cout << "Enter start address in hexadecimal (00-FF): ";
    if (!(std::cin >> std::hex >> address)) {
        std::cout << "Invalid hexadecimal address.\n";
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return;
    }
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    if (address > 0xFF) {
        std::cout << "Address must be in range 00-FF.\n";
        return;
    }

    try {
        if (machine.loadProgram(filename, static_cast<std::uint8_t>(address))) {
            std::cout << "Program loaded successfully.\n";
        } else {
            std::cout << "Program was not loaded.\n";
        }
    } catch (const std::exception& error) {
        std::cout << "Load error: " << error.what() << '\n';
    }
}

void ConsoleUI::handleRun() {
    try {
        machine.run();
        std::cout << "Program execution finished.\n";
    } catch (const std::exception& error) {
        std::cout << "Execution error: " << error.what() << '\n';
    }
    displayAll();
}

void ConsoleUI::handleStep() {
    if (machine.isHalted()) {
        std::cout << "CPU is halted. Reset or load a program first.\n";
        return;
    }

    try {
        const bool executed = machine.runStep();
        if (!executed) {
            std::cout << "No instruction was executed (halted or fetch failed).\n";
        }
    } catch (const std::exception& error) {
        std::cout << "Step error: " << error.what() << '\n';
    }
    displayAll();
}

void ConsoleUI::displayMemory() const {
    renderer.displayMemory(machine);
}

void ConsoleUI::displayRegisters() const {
    renderer.displayRegisters(machine);
}

void ConsoleUI::displayCPU() const {
    renderer.displayCPU(machine);
}

void ConsoleUI::displayScreen() const {
    renderer.displayScreen(machine);
}

void ConsoleUI::displayAll() const {
    displayCPU();
    displayRegisters();
    displayMemory();
    displayScreen();
}

void ConsoleUI::start() {
    bool active = true;

    while (active) {
        showMenu();

        int choice = -1;
        if (!(std::cin >> choice)) {
            std::cout << "Please enter a valid menu option.\n";
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            continue;
        }
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        switch (choice) {
            case 1: handleLoadProgram(); break;
            case 2: handleRun(); break;
            case 3: handleStep(); break;
            case 4: displayMemory(); break;
            case 5: displayRegisters(); break;
            case 6: displayCPU(); break;
            case 7: displayScreen(); break;
            case 8: displayAll(); break;
            case 9:
                machine.resetAll();
                std::cout << "Machine reset successfully.\n";
                break;
            case 0:
                active = false;
                break;
            default:
                std::cout << "Invalid option. Try again.\n";
                break;
        }
    }
}
