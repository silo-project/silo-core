#include <cstdint>

#ifndef VALUE_H
#define VALUE_H

class Value {
private: 
    uint8_t size;
    uint64_t value;
    uint64_t highImpedance;
    uint64_t unknown;

public:
    Value(uint8_t size, uint64_t value, uint64_t highImpedance, uint64_t unknown) : size(size), value(value), highImpedance(highImpedance), unknown(unknown) { }

    uint8_t getSize();
    uint64_t getValue();
    uint64_t getHighImpedance();
    uint64_t getUnknown();
};

#endif