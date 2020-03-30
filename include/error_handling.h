#ifndef ERROR_HANDLING_H
#define ERROR_HANDLING_H

#include <cstdint>

using                                  SILO_STATUS =    uint8_t;

constexpr SILO_STATUS					   SUCCESS = 0b00000000;

constexpr SILO_STATUS INPUT_VALUE_CONFLICT_WARNING = 0b01000000;

constexpr SILO_STATUS          OUT_OF_MEMORY_ERROR = 0b10000000;
constexpr SILO_STATUS		   INFINITE_LOOP_ERROR = 0b10000001;
constexpr SILO_STATUS		 GATE_PROPERTIES_ERROR = 0b10000010;
constexpr SILO_STATUS				 GATE_ID_ERROR = 0b10000011;

#endif