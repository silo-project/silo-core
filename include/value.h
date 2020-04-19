#ifndef VALUE_H
#define VALUE_H

#include <cstdint>



class Value {
private:
    uint8_t width;
    uint64_t value;
    uint64_t state;

public:
    Value(uint8_t width, uint64_t value, uint64_t state);
    Value(uint8_t width, uint64_t value, uint64_t unknown, uint64_t error);

    inline uint8_t getWidth() const {
        return this->width;
    }

    inline uint64_t getRawValue() const {
        return this->value;
    }

    inline uint64_t getState() const {
        return this->state;
    }

    inline uint64_t getValue() const {
        return this->value & ~this->state;
    }

    inline uint64_t getError() const {
        return this->value & this->state;
    }

    inline uint64_t getUnknown() const {
        return ~this->value & this->state;
    }
};

#endif