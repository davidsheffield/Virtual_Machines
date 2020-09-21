#include "vm8008.h"

using namespace std;

VM8008::VM8008() {
    pc_stack[0] = 0;
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


uint16_t VM8008::get_HL() const {
    return (((static_cast<uint16_t>(reg_H) << 8) + static_cast<uint16_t>(reg_L))
            & 0x3fff);
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
    pc_stack[0] = val;
    return;
}


uint16_t VM8008::get_pc() const {
    return pc_stack[0];
}


void VM8008::push_pc_stack(uint16_t val) {
    for (int i=7; i>0; ++i) {
        pc_stack[i] = pc_stack[i - 1];
    }
    pc_stack[0] = val;
}


void VM8008::pop_pc_stack() {
    for (int i=0; i<7; ++i) {
        pc_stack[i] = pc_stack[i + 1];
    }
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
        uint8_t op = memory[pc_stack[0]];
        // cout << "Get memory " << pc << ": " << int(op) << endl;
        ++pc_stack[0];
        // if ((op == 0x00) || (op == 0x01)) {
        //     // cout << "Halt" << endl;
        //     halt = true;
        // } else if ((op & 0b11111000) == 0b11000000) {
        //     // cout << "Load A with " << int(op & 0b00000111) << endl;
        //     set_A(op & 0b00000111);
        // } else if ((op & 0b11111000) == 0b10000000) {
        //     // cout << "Add " << int(op & 0b00000111) << endl;
        //     reg_A += op & 0b00000111;
        // }
        switch (op) {
        case 0x00: // HLT
            halt = true;
            break;
        case 0x01: // HLT
            halt = true;
            break;
        case 0x02: // RLC
            reg_A = (reg_A << 1) | (reg_A >> 7);
            flag_carry = false;
            break;
        case 0x03: // RFC
            if (!flag_carry) {
                pop_pc_stack();
            }
            break;
        case 0x04: // ADI
            reg_A += memory[pc_stack[0]];
            ++pc_stack[0];
            flag_parity = !(reg_A & 0x1);
            flag_zero = reg_A == 0;
            flag_sign = reg_A & 0x80;
            break;
        case 0x05: // RST 0
            push_pc_stack(0);
            break;
        case 0x06: // LAI
            reg_A = memory[pc_stack[0]];
            ++pc_stack[0];
            break;
        case 0x07: // RET
            pop_pc_stack();
            break;
        case 0x08: // INB
            ++reg_B;
            flag_parity = !(reg_B & 0x1);
            flag_zero = reg_B == 0;
            flag_sign = reg_B & 0x80;
            break;
        case 0x09: // DCB
            --reg_B;
            flag_parity = !(reg_B & 0x1);
            flag_zero = reg_B == 0;
            flag_sign = reg_B & 0x80;
            break;
        case 0x0a: // RRC
            reg_A = (reg_A >> 1) | (reg_A << 7);
            flag_carry = false;
            break;
        case 0x0b: // RFZ
            if (!flag_zero) {
                pop_pc_stack();
            }
            break;
        case 0x0c: // ACI
            reg_A += memory[pc_stack[0]] + static_cast<uint8_t>(flag_carry);
            ++pc_stack[0];
            flag_parity = !(reg_A & 0x1);
            flag_zero = reg_A == 0;
            flag_sign = reg_A & 0x80;
            break;
        case 0x0d: // RST 1
            push_pc_stack(0x8);
            break;
        case 0x0e: // LBI
            reg_B = memory[pc_stack[0]];
            ++pc_stack[0];
            break;
        case 0x0f: // RET
            pop_pc_stack();
            break;
        case 0x2e: // LHI
            reg_H = memory[pc_stack[0]];
            ++pc_stack[0];
            break;
        case 0x36: // LLI
            reg_L = memory[pc_stack[0]];
            ++pc_stack[0];
            break;
        case 0xc7: // LAM
            reg_A = memory[get_HL()];
            break;
        }
    }
}


int main() {
    // VM8008 vm1;
    // vm1.set_memory(0, 0b11000001);
    // vm1.set_memory(1, 0b10000010);
    // vm1.set_memory(2, 0b00000000);
    // vm1.run();
    // cout << int(vm1.get_A()) << endl;

    // VM8008 vm2;
    // vm2.set_memory(0, 0b11000010);
    // vm2.set_memory(1, 0b10000010);
    // vm2.set_memory(2, 0b00000000);
    // vm2.run();
    // cout << int(vm2.get_A()) << endl;

    VM8008 vm;
    vm.set_memory(0, 0x36);   // LLI 100
    vm.set_memory(1, 100);
    vm.set_memory(2, 0x2e);   // LHI 1
    vm.set_memory(3, 1);
    vm.set_memory(4, 0xc7);   // LAM
    vm.set_memory(5, 0x0c);   // ACI
    vm.set_memory(6, 255);
    vm.set_memory(7, 0x00);   // HLT
    vm.set_memory(356, 4);
    vm.run();

    uint8_t val = vm.get_A();
    cout << int(val) << " " << std::bitset<8>(val).to_string() << endl;
    cout << "C" << int(vm.get_carry())
         << " P" << int(vm.get_parity())
         << " Z" << int(vm.get_zero())
         << " S" << int(vm.get_sign())
         << endl;

    return 0;
}
