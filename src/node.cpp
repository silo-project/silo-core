#include "node.h"



inline std::unordered_map< std::string, uint8_t > AbstractNode::getGateProperties() const {
    return this->gateProperties;
}

inline void AbstractNode::setGateProperties(const std::unordered_map< std::string, uint8_t >& properties) {
    this->gateProperties = properties;
}
