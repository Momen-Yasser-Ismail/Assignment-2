# Vole Machine Simulator

A modular, C++17 implementation of the **Vole Machine** architecture (a simple, simulated computer system often used for educational computer architecture studies). 

This project simulates the CPU, registers, memory, arithmetic logic unit (ALU), and memory-mapped console output, featuring an interactive command-line interface to load, run, and step through machine code instructions.

---

## 🛠️ Project Structure

```text
├── .cpps/                  # C++ implementation files (.cpp)
├── Headers/                # Header files (.h)
├── Part 1 (...)/           # Architectural documentation, design materials, and test programs
├── README.md               # Project documentation
└── vole.exe                # Compiled executable
```

---

## 🚀 Features

* **Complete Vole Machine Simulation**:
  * 256-byte addressable RAM grid (`0x00` to `0xFF`).
  * 16 General-Purpose Registers (`R0` through `RF`).
  * Dedicated CPU registers: Program Counter (`PC`), Instruction Register (`IR`), and Halted status.
* **Memory-Mapped Screen Output**: Writes to memory address `0xFF` stream directly to the simulated console output buffer.
* **Automatic Screen Clearing**: Screen buffer and memory-mapped display state cleanly reset upon loading new programs.
* **Flexible Execution Modes**:
  * **Continuous Execution**: Run full programs until `HALT` (`0xC000`).
  * **Single-Step Execution**: Debug machine code step-by-step while inspecting register and memory updates.
* **Real-time Visualization**: High-level renderer displaying CPU status, register files, and a 16x16 hexadecimal memory dump.

---

## 💻 Build & Run Instructions

### Prerequisites
* A C++ compiler supporting **C++17** (e.g., `g++`, `clang++`, or MSVC).

### Building the Project
From the repository root directory, execute the following command in your terminal:

```bash
g++ -std=c++17 .cpps/*.cpp -IHeaders -o vole.exe
```

### Running the Simulator
Run the compiled binary:

```bash
./vole.exe
```

---

## 🎮 How to Use

When launching `./vole.exe`, an interactive menu presents the following options:

1. **Load Program**: Loads hexadecimal Vole machine code instructions from a `.txt` file into memory at a specified starting address.
2. **Run Program**: Continuously executes instructions from the current `PC` address until a `HALT` instruction (`C000`) is encountered.
3. **Run One Step**: Advances execution by a single instruction step (useful for debugging).
4. **Display Memory**: Displays the 256-byte RAM array in a 16x16 grid format.
5. **Display Registers**: Prints the current hexadecimal values stored across all 16 registers (`R0`–`RF`).
6. **Display CPU**: Displays current `PC`, `IR`, and execution status.
7. **Display Screen Output**: Shows characters/hex values streamed to memory address `0xFF`.
8. **Display All**: Formats and prints CPU state, registers, memory, and screen buffer simultaneously.
9. **Reset Machine**: Wipes memory, clears registers, resets the program counter to zero, and flushes the screen output.

> 💡 **Tip**: When running multiple programs sequentially at different load addresses, use option `9 (Reset Machine)` or ensure the `PC` is explicitly set to the new program's start address to prevent lingering register state or crashes.

---

## 🏗️ Architecture Overview

The system is designed following object-oriented design principles (Facade & Component patterns):

* `Machine`: The facade manager coordinating hardware components (`CPU`, `Memory`, `Screen`, `ProgramLoader`).
* `CPU`: Handles the fetch-decode-execute cycle and instruction pointers.
* `ALU`: Computes integer arithmetic, floating-point addition, bitwise operations (`AND`, `OR`, `XOR`), and rotations.
* `Memory`: Manages 256 memory cells and intercepts writes to `0xFF` for screen output streaming.
* `ConsoleUI` & `ConsoleRenderer`: Handles terminal interactions and state visual rendering.

---

## 📄 Example Vole Program (Swap Registers)

```text
2105    ; Load R1 with 0x05
2206    ; Load R2 with 0x06
2300    ; Clear R3 (temp register)
4013    ; Move R1 into R3
4021    ; Move R2 into R1
4032    ; Move R3 into R2
2300    ; Reset temp register R3
C000    ; HALT execution
```

---

