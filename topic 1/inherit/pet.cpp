#include <stdexcept>
#include "pet.h"

Pet::Pet(const std::string& name) /* : name{name} */  // list initialization for if no input validation
{
    if (name.empty()) throw std::logic_error("name cannot be empty!");
    this->name = name;      // we only do this bc of input validation
}

std::string Pet::getName() const {return name;}