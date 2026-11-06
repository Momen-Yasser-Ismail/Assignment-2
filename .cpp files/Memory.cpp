#include "Memory.h"

Memory::Memory()
{
    clear();
}

uint8_t Memory::read(uint8_t address)
{
    return cells[address];
}

void Memory::write(uint8_t address, uint8_t value)
{
    cells[address] = value;

    if (address == 0xFF)
    {
        screenoutput += static_cast<char>(value);
    }
}

const uint8_t *Memory::getCells() const
{
    return cells;
}

string Memory::getScreenOutput() const
{
    return screenoutput;
}

void Memory::clear()
{
    for (int i = 0; i < 256; i++)
    {
        cells[i] = 0;
    }

    screenoutput = "";
}