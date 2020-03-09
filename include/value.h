#include <cstdint>

#ifndef VALUE_H
#define VALUE_H

<<<<<<< Updated upstream
struct Value {
    uint8_t  size;
    uint64_t value;
=======
struct value {
    uint8_t  size;
    uint64_t value;
    uint64_t highImpedance;
>>>>>>> Stashed changes
    uint64_t unknown;
};

#endif