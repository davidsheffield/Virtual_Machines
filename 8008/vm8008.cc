#include "vm8008.h"

using namespace std;

VM8008::VM8008() {
    pc = 0;
}

VM8008::~VM8008(){}


void VM8008::set_A(uint8_t val) {
    reg_A = val;
    return;
}


void VM8008::set_B(uint8_t val) {
    reg_B = val;
    return;
}


void VM8008::set_C(uint8_t val) {
    reg_C = val;
    return;
}


void VM8008::set_D(uint8_t val) {
    reg_D = val;
    return;
}


void VM8008::set_E(uint8_t val) {
    reg_E = val;
    return;
}


void VM8008::set_H(uint8_t val) {
    reg_H = val;
    return;
}


void VM8008::set_L(uint8_t val) {
    reg_L = val;
    return;
}


uint8_t VM8008::get_A() const {
    return reg_A;
}


uint8_t VM8008::get_B() const {
    return reg_B;
}


uint8_t VM8008::get_C() const {
    return reg_C;
}


uint8_t VM8008::get_D() const {
    return reg_D;
}


uint8_t VM8008::get_E() const {
    return reg_E;
}


uint8_t VM8008::get_H() const {
    return reg_H;
}


uint8_t VM8008::get_L() const {
    return reg_L;
}


void VM8008::set_carry(bool val) {
    flag_carry = val;
    return;
}


void VM8008::set_parity(bool val) {
    flag_parity = val;
    return;
}


void VM8008::set_zero(bool val) {
    flag_zero = val;
    return;
}


void VM8008::set_sign(bool val) {
    flag_sign = val;
    return;
}


bool VM8008::get_carry() const {
    return flag_carry;
}


bool VM8008::get_parity() const {
    return flag_parity;
}


bool VM8008::get_zero() const {
    return flag_zero;
}


bool VM8008::get_sign() const {
    return flag_sign;
}


void VM8008::set_pc(uint16_t val) {
    pc = val;
    return;
}


uint16_t VM8008::get_pc() const {
    return pc;
}


void VM8008::set_memory(uint16_t loc, uint8_t val) {
    memory[loc] = val;
    return;
}


uint8_t VM8008::get_memory(uint16_t loc) const {
    return memory[loc];
}


void VM8008::run() {
    bool halt = false;
    while (!halt) {
        uint8_t op = memory[pc];
        // cout << "Get memory " << pc << ": " << int(op) << endl;
        ++pc;
        if ((op == 0) || ((op & 0b1111110) == 0)) {
            // cout << "Halt" << endl;
            halt = true;
        } else if ((op & 0b11111000) == 0b11000000) {
            // cout << "Load A with " << int(op & 0b00000111) << endl;
            set_A(op & 0b00000111);
        } else if ((op & 0b11111000) == 0b10000000) {
            // cout << "Add " << int(op & 0b00000111) << endl;
            reg_A += op & 0b00000111;
        }
    }
}


int main() {
    VM8008 vm1;
    vm1.set_memory(0, 0b11000001);
    vm1.set_memory(1, 0b10000010);
    vm1.set_memory(2, 0b00000000);
    vm1.run();
    cout << int(vm1.get_A()) << endl;

    VM8008 vm2;
    vm2.set_memory(0, 0b11000010);
    vm2.set_memory(1, 0b10000010);
    vm2.set_memory(2, 0b00000000);
    vm2.run();
    cout << int(vm2.get_A()) << endl;

    return 0;
}
