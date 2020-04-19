#ifndef NOT_GATE_H
#define NOT_GATE_H

#include "node.h"



struct NotGateProperties {
    uint8_t    dataBits = 0;
    uint8_t outputValue = 0;
};

class NotGate : public AbstractGate {
private:
   NotGateProperties properties;

public:
    virtual status_t init();
    virtual void calculate();
};

#endif