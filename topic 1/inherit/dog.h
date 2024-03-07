#include "pet.h"

#ifndef DOG_H
#define DOG_H

class Dog : public Pet
{
public:
    Dog(const std::string&);
    std::string speak() const override;
};

#endif