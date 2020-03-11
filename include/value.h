#ifndef VALUE_H
#define VALUE_H

#include <cstdint>

class Value {
private: 
  uint8_t width;
  uint64_t value;
  uint64_t unknown;
  uint64_t error;

public:
  Value(uint8_t width, uint64_t value, uint64_t unknown, uint64_t error) : width(width), value(value), unknown(unknown), error(error) { }

  uint8_t getWidth();
  uint64_t getValue();
  uint64_t getUnknown();
  uint64_t getError();
};

#endif

#ifndef INT64_MAX
#define INT64_MAX 0xffffffffffffffff
#endif