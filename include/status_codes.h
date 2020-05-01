#ifndef STATUS_CODES_H
#define STATUS_CODES_H

#include <cstdint>



using status_t = uint8_t ;

constexpr status_t SUCCESS  = 0b00000000u;

constexpr status_t WARNING                                  = 0b01000000u;
constexpr status_t WARNING_CONFLICTING_INPUT_VALUE  =WARNING| 0b00000001u;

constexpr status_t ERROR                                    = 0b10000000u;
constexpr status_t ERROR_INVALID_GATE_PROPERTIES    = ERROR | 0b00000001u;
constexpr status_t ERROR_INVALID_GATE_ID            = ERROR | 0b00000010u;
constexpr status_t ERROR_INFINITE_LOOP              = ERROR | 0b00000011u;

constexpr status_t FATAL                                    = 0b11000000u;
constexpr status_t FATAL_OUT_OF_MEMORY              = FATAL | 0b00000001u;

#endif