#ifndef STATUS_CODES_H
#define STATUS_CODES_H

#include <cstdint>



using status_t = uint8_t ;

constexpr status_t SUCCESS  = 0b00000000;

constexpr status_t WARNING                          = 0b01000000;
constexpr status_t WARNING_CONFLICTING_INPUT_VALUE  = 0b01000001;

constexpr status_t ERROR                            = 0b10000000;
constexpr status_t ERROR_INVALID_GATE_PROPERTIES    = 0b10000001;
constexpr status_t ERROR_INVALID_GATE_ID            = 0b10000010;
constexpr status_t ERROR_INFINITE_LOOP              = 0b10000011;

constexpr status_t FATAL                = 0b11000000;
constexpr status_t FATAL_OUT_OF_MEMORY  = 0b11000001;

#endif