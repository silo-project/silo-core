#include <cstdint>

#ifndef VALUE_H
#define VALUE_H

class Value {
private:
    uint8_t width;
    uint64_t value;
    uint64_t state;

public:
    Value(uint8_t width, uint64_t value, uint64_t state);

    Value(uint8_t width, uint64_t value, uint64_t unknown, uint64_t error);

    inline uint8_t getWidth() const;
    inline uint64_t getValue() const;
    inline uint64_t getState() const;

    inline uint64_t getLogicalValue() const;
    inline uint64_t getError() const;
    inline uint64_t getUnknown() const;
};

#endif