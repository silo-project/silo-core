#include "value.h"

inline uint8_t Value::getWidth() const {
    return this->width;
}

inline uint64_t Value::getValue() const {
    return this->value;
}

inline uint64_t Value::getState() const {
    return this->state;
}

inline uint64_t Value::getLogicalValue() const {
    return this->value & ~this->state;
}

inline uint64_t Value::getError() const {
    return this->value & this->state;
}

inline uint64_t Value::getUnknown() const {
    return ~this->value & this->state;
}