#include <cstdint>

#ifndef VALUE_H
#define VALUE_H

class Value {
private: 
    uint8_t size;
    uint64_t value;
    uint64_t high_impedance;
    uint64_t unknown;

public:
    Value(uint8_t size, uint64_t value, uint64_t high_impedance, uint64_t unknown) : size(size), value(value), high_impedance(high_impedance), unknown(unknown) { }

    uint8_t get_size();
    uint64_t get_value();
    uint64_t get_high_impedance();
    uint64_t get_unknown();
};

#endif