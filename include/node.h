#ifndef NODE_H
#define NODE_H

#include <cstdint>
#include <string>
#include <unordered_map>

#include "status_codes.h"
#include "sender.h"
#include "receiver.h"
#include "value.h"



class AbstractNode {
private:
    std::unordered_map<std::string, uint8_t> properties;

public:
    std::unordered_map<std::string, uint8_t> getProperties() const;
    void setProperties(const std::unordered_map<std::string, uint8_t>& properties);

    virtual status_t init() = 0;
};

class AbstractGate : public Sender, public Receiver, public AbstractNode {
    
};

#endif
