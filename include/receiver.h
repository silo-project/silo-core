#ifndef RECEIVER_H
#define RECEIVER_H

#include <cstdint>
#include <vector>

#include "error_handling.h"
#include "value.h"



struct SingleBit {
    bool   value = 0;
    bool unknown = 0;
    bool   error = 0;
};

class Receiver {
private:
    std::vector< Value* >          inputs;
    std::vector< Value* >   previousInput;
    std::vector< uint8_t >    inputWidths;

    bool                 firstInputFlag =    true;
    SILO_STATUS               errorFlag = SUCCESS;

private:
    bool getBit(uint8_t digit, uint64_t value) const;

    SingleBit addSingleSignal(SingleBit nowValue, SingleBit newValue);
    Value* addSignal(Value* nowSignal, Value* newSignal, uint8_t width);

    uint64_t setBit(uint8_t digit, uint64_t value, bool setValue) const;

public:
    ~Receiver();

    inline std::vector< Value* > getInputs() const;
    inline std::vector< Value* > getPreviousInput() const;
    inline std::vector< uint8_t > getInputWidths() const;

    void addInput(Value *value);

    SILO_STATUS setInput(uint8_t inputNumber, Value *inputValue);
    void setInputs(const std::vector< Value* >& inputValues);
    void setPreviousInput(uint8_t inputNumber, Value inputValue);
    void setPreviousInputs(const std::vector< Value* >& inputValues);
    void setInputWidths(const std::vector< uint8_t >& inputWidthValues);
    void setFirstInputFlag();
};

#endif
