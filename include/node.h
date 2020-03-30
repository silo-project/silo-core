#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "error_handling.h"
#include "sender.h"
#include "receiver.h"
#include "value.h"



class AbstractNode {
private:
    std::unordered_map< std::string, uint8_t > gateProperties;

public:
    inline std::unordered_map< std::string, uint8_t > getGateProperties() const;

    inline void setGateProperties(const std::unordered_map< std::string, uint8_t >& properties);

    virtual SILO_STATUS init() = 0;
};

class AbstractGate 
    : public Sender, 
      public Receiver,
      public AbstractNode { };

#endif
