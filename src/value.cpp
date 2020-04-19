#include "value.h"



Value::Value(uint8_t width, uint64_t raw_value, uint64_t state) : width(width), value(raw_value), state(state) {

}

Value::Value(uint8_t width, uint64_t value, uint64_t unknown, uint64_t error) : width(width), value(value | error), state(unknown | error) {

}