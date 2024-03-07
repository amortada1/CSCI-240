#include <string>

#ifndef PET_H
#define PET_H

class Pet
{
public:
    Pet(const std::string&);
    virtual std::string speak() const = 0; // = 0 means function is not implemented here (pure virtual)
    std::string getName() const;
private:
    std::string name;
};

#endif