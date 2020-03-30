#ifndef SENDER_H
#define SENDER_H

#include <cstdint>
#include <vector>

#include "connection_info.h"
#include "value.h"



class Sender {
private:
    std::vector< Value* >                outputs;
    std::vector< uint8_t >          outputWidths;
    std::vector< ConnectionInfo > nodeConnection;

public:
    ~Sender();

    inline std::vector< Value* > getOutputs() const;
    inline std::vector< uint8_t > getOutputWidths() const;
    inline std::vector< ConnectionInfo > getConnection() const;

    void addOutput(Value* value);
    void addConnection(const ConnectionInfo& newConnection);

    inline void setOutputs(const std::vector< Value* >& outputValues);
    inline void setOutputWidths(const std::vector< uint8_t >& outputWidthValues);

    virtual void calculate() = 0;
};

#endif
