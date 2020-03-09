#include <cstdint>

#ifndef VALUE_H
#define VALUE_H

struct Value {
    uint8_t  size;
    uint64_t value;
    uint64_t unknown;
};

#endif