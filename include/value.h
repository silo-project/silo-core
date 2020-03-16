#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

class Value {
private:
    uint8_t width;
    uint64_t value;
    uint64_t state;

public:
    Value(uint8_t width, uint64_t value, uint64_t state) {
        this->width = width;
        this->value = value;
        this->state = state;
    }

    Value(uint8_t width, uint64_t value, uint64_t unknown, uint64_t error) {
        this->width = width;
        this->value = value;
        this->value |= error;
        this->state = unknown | error;
    }

    uint8_t getWidth();
    uint64_t getValue();
    uint64_t getState();

    uint64_t getLogicalValue();
    uint64_t getError();
    uint64_t getUnknown();
};

#endif