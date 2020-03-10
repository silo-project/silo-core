#include <cstdint>

#ifndef VALUE_H
#define VALUE_H

class Value {
private: 
    uint8_t size;
    uint64_t value;
    uint64_t unknown;
    uint64_t error;

public:
    Value(uint8_t size, uint64_t value, uint64_t unknown, uint64_t error) : size(size), value(value), unknown(unknown), error(error) { }

    uint8_t getSize();
    uint64_t getValue();
    uint64_t getUnknown();
    uint64_t getError();
};

#endif