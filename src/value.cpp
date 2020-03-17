#include "value.h"

Value::Value(uint8_t width, uint64_t value, uint64_t state) 
    : width(width), value(value), state(state) {

}

Value::Value(uint8_t width, uint64_t value, uint64_t unknown, uint64_t error) 
    : width(width), value(value | error), state(unknown | error) {

}

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