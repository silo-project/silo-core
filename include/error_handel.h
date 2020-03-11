#ifndef ERROR_HANDEL_H
#define ERROR_HANDEL_H

#define SILO_ERRHANDEL uint8_t

#define SUCCESS 0b00000000

#define INPUT_VALUE_CONFLICT_WARNING 0b01000000

#define OUT_OF_MEMORY_ERROR 0b10000000 + 0
#define INFINITE_LOOP_ERROR 0b10000000 + 1
#define GATE_PROPERTIES_ERROR 0b10000000 + 2
#define GATE_ID_ERROR 0b10000000 + 3

#endif ERROR_HANDEL_H