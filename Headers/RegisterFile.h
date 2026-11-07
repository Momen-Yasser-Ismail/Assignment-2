#include <iostream>
using namespace std;
#include <cstdint>

class RegisterFile 
{
    private:
        uint8_t registers[16];

    public:
        RegisterFile();

        uint8_t getRegister(uint8_t index) const;
        void setRegister(uint8_t index, uint8_t value);
        void clear();
};