#include "component.h"

Component::Component(std::string identifier) : identifier(identifier) {}

Component::~Component() {}

const std::string& Component::getIdentifier() const
{
    return identifier;
}
