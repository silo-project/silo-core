#include <value.h>

uint8_t Value::getSize() {
    return this->size;
}

uint64_t Value::getValue() {
    return this->value;
}

uint64_t Value::getUnknown() {
    return this->unknown;
}

uint64_t Value::getError() {
    return this->error;
}