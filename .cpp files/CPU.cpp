#include "CPU1.h"
#include <iostream>

using namespace std;
CPU :: CPU(Memory& mem) : memory (mem){
    ir = 0 ; 
    pc = 0 ; 
    halted = false;
    for (int i = 0 ; i < 16 ; i++){
        registers[i] = 0 ;
    }
}
bool CPU :: fetch(){
    int first = memory.read(pc);
    int second = memory.read(pc+1);
    ir = (first << 8) | second;
    pc+=2;
    return true;

}
bool CPU::isValid(uint16_t ir){
    uint8_t firstnum = (ir >> 12) &0xF ;
    return (firstnum >= 1 && firstnum <= 0xC);
}
uint8_t CPU :: getPC (){
    return pc ; 
}

void CPU :: setPC(uint8_t address){
    pc = address ;
}
uint16_t CPU :: getIR(){
    return ir ; 
}

uint8_t CPU :: getRegister(uint8_t index){
    if (index < 16) return registers[index];
    return 0 ;
}
void CPU :: setRegister(uint8_t index , uint8_t value){
    if (index < 16) registers[index] = value;
}
bool CPU::isHalted(){return halted;}

void CPU::execute(){
    int first_number = (ir >> 12)& 0xF ;
    uint8_t second_number = (ir >> 8)&0xF;
    int third_number = (ir >> 4)&0xF;
    int forth_number = (ir) &0xF;
    uint8_t memory_address = (third_number << 4 ) | forth_number;
    if (first_number < 1 || first_number > 0xC) return ;
    if (first_number == 1) {
        registers[second_number] = memory.read(memory_address);
    }
    else if (first_number == 2 ){
        registers[second_number] = (memory_address);
    }
    else if (first_number == 3 ){
        memory.write(memory_address,registers[second_number]);
    }
    else if (first_number == 4){
        registers [forth_number] = registers[third_number];
    }
    else if (first_number == 5){
        registers[second_number] = registers[third_number] + registers[forth_number];
    }
    else if (first_number == 6){

    }
    else if (first_number == 7){
        registers[second_number] = registers[third_number] | registers[forth_number];
    }
    else if (first_number == 8 ){
        registers[second_number] = registers[third_number] & registers[forth_number];
    }
    else if (first_number == 9){
        registers[second_number] = registers[third_number] ^ registers[forth_number];
    }
    else if (first_number == 0xA){
        int steps = forth_number%8;
        int leftnum = (registers[second_number] >> steps);
        int rightnum = (registers[second_number] << (8-steps));
        registers[second_number] = (leftnum | rightnum) &   0xFF;
    }
    else if (first_number == 0xB){
        if (registers [0] == registers[second_number]){
            pc = memory_address;
        }
    }
    else if (first_number == 0xC){
        halted = true ;
    }
}

void CPU::step(){
    if (halted) return;
    fetch();
    execute();
}

