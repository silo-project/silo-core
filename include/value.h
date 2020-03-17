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

    inline uint8_t getWidth() const;
    inline uint64_t getValue() const;
    inline uint64_t getState() const;

    inline uint64_t getLogicalValue() const;
    inline uint64_t getError() const;
    inline uint64_t getUnknown() const;
};

#endif