#include <value.h>

uint8_t Value::get_size() {
    return this->size;
}

uint64_t Value::get_value() {
    return this->value;
}

uint64_t Value::get_high_impedance() {
    return this->high_impedance;
}

uint64_t Value::get_unknown() {
    return this->unknown
}