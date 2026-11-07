#include"RegisterFile.h"

RegisterFile::RegisterFile()
{
    clear();
}

uint8_t RegisterFile::getRegister(uint8_t index) const
{
    if (index > 15)
    {
        cout << "Error: Register index out of range, must be betwwen 0 and 15." << endl;
        return 0;
    }
    return registers [index];
}

void RegisterFile::setRegister(uint8_t index, uint8_t value)
{
    if (index > 15)
    {
        cout << "Error: Register index out of range, must be betwwen 0 and 15."
        return;
    }

    registers[index] = value
}

void RegisterFile::clear()
{for (int i = 0; i < 16; i++)
    {
        registers[i] = 0;
    }
}
