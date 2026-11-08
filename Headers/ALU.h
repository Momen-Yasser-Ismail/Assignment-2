#include<cstdint>

class ALU
{
    public:
        static uint8_t addinteger(uint8_t a, uint8_t b);

        static uint8_t addFloatingpoint(uint8_t a, uint8t_t b);

        static uint8_t And(uint8_t a, uint8_t b);

        static uint8_t Or(uint8_t a, uint8_t b);

        static uint8_t Xor(uint8_t a, uint8_t b);
        
        static uint8_t rotateRight(uint8_t value, uint8_t steps);
};
