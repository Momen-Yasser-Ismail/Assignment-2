#include <iostream>
#include <vector>
#include <string>
#include <cstdint>
using namespace std;

class Memory
{
private:
    uint8_t cells[256];
    string screenoutput;

public:
    Memory();

    uint8_t read(uint8_t address);
    void write(uint8_t address, uint8_t value);

    const uint8_t *getCells() const;
    string getScreenOutput() const;
    void clear();
};
