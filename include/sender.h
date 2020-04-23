#ifndef SENDER_H
#define SENDER_H

#include <cstdint>
#include <vector>

#include "connection.h"
#include "value.h"



class Sender {
private:
    std::vector< Value* > outputs;
    std::vector< uint8_t > outputWidths;
    std::vector< Connection > nodeConnection;

public:
    ~Sender();

    std::vector< Value* > getOutputs() const;
    std::vector< uint8_t > getOutputWidths() const;
    std::vector< Connection > getConnection() const;

    void addOutput(Value* value);
    void addConnection(const Connection& newConnection);

    void setOutputs(const std::vector< Value* >& outputValues);
    void setOutputWidths(const std::vector< uint8_t >& outputWidthValues);

    virtual void calculate() = 0;
};

#endif
