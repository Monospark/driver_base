#pragma once
#include <string>

class Component
{
public:
    Component(std::string identifier);
    virtual ~Component();

    virtual void* getComponentPointer() = 0;
    const std::string& getIdentifier() const;

private:
    const std::string identifier;
};
