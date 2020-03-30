#ifndef AND_GATE_H
#define AND_GATE_H

#include "node.h"



struct AndGateProperties {
    uint8_t       dataBits = 0;
    uint8_t numberOfInputs = 0;
    uint8_t    outputValue = 0;
};

class AndGate : public AbstractGate {
private:
    AndGateProperties properties;

public:
    virtual SILO_STATUS init();
    virtual void calculate();
};

#endif