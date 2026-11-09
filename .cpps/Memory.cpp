#include "../Headers/Memory.h"
#include "../Headers/Hex.h"

Memory::Memory()
{
    clear();
}

std::uint8_t Memory::read(std::uint8_t address)
{
    return cells[address];
}

void Memory::write(std::uint8_t address, std::uint8_t value)
{
    cells[address] = value;

    if (address == 0xFF)
    {
        screenoutput += toHex(value, 2);
    }
}

const std::uint8_t *Memory::getCells() const
{
    return cells;
}

std::string Memory::getScreenOutput() const
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