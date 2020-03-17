#include <cstdint>

#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

using                              SILO_STATUS = uint8_t;

constexpr SILO_STATUS               SUCCESS = 0b00000000;

constexpr auto INPUT_VALUE_CONFLICT_WARNING = 0b01000000;

constexpr auto          OUT_OF_MEMORY_ERROR = 0b10000000;
constexpr auto          INFINITE_LOOP_ERROR = 0b10000001;
constexpr auto        GATE_PROPERTIES_ERROR = 0b10000010;
constexpr auto                GATE_ID_ERROR = 0b10000011;

#endif