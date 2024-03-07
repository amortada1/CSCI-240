#include "dog.h"

Dog::Dog(const std::string& name) : Pet(name) {} // Calls on Pet's constructor

std::string Dog::speak() const {return getName() + " says: woof-woof";}