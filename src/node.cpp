#include "node.h"

std::unordered_map<std::string, uint8_t> AbstractNode::getProperties() const {
        return this->properties;
}

void AbstractNode::setProperties(const std::unordered_map<std::string, uint8_t>& properties) {
    this->properties = properties;
}