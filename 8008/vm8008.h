#ifndef VM8008_h
#define VM8008_h

#include <cstdint>
#include <iostream>

class VM8008
{
public:
    VM8008();
    ~VM8008();

    // Registers
    void set_A(uint8_t);
    void set_B(uint8_t);
    void set_C(uint8_t);
    void set_D(uint8_t);
    void set_E(uint8_t);
    void set_H(uint8_t);
    void set_L(uint8_t);
    uint8_t get_A() const;
    uint8_t get_B() const;
    uint8_t get_C() const;
    uint8_t get_D() const;
    uint8_t get_E() const;
    uint8_t get_H() const;
    uint8_t get_L() const;

    // Flags
    void set_carry(bool);
    void set_parity(bool);
    void set_zero(bool);
    void set_sign(bool);
    bool get_carry() const;
    bool get_parity() const;
    bool get_zero() const;
    bool get_sign() const;

    // Program counter
    void set_pc(uint16_t);
    uint16_t get_pc() const;

    // Memory
    void set_memory(uint16_t, uint8_t);
    uint8_t get_memory(uint16_t) const;

    void run();

private:
    // Registers
    uint8_t reg_A;
    uint8_t reg_B;
    uint8_t reg_C;
    uint8_t reg_D;
    uint8_t reg_E;
    uint8_t reg_H;
    uint8_t reg_L;

    // Flags
    bool flag_carry;
    bool flag_parity;
    bool flag_zero;
    bool flag_sign;

    // Program counter
    uint8_t pc;

    // Memory
    uint8_t memory[16384];
};

#endif
