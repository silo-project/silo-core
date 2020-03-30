#ifndef BUFFER_GATE_H
#define BUFFER_GATE_H

#include "node.h"



struct BufferGateProperties {
    uint8_t    dataBits = 0;
    uint8_t outputValue = 0;
};

class BufferGate : public AbstractGate {
private:
    BufferGateProperties properties;

public:
    virtual SILO_STATUS init();
    virtual void calculate();
};

#endif