//
// Created by seanp on 10/01/2019.
//

#ifndef OBJECTORIENTEDPROGRAMMING_C_REPTILE_H
#define OBJECTORIENTEDPROGRAMMING_C_REPTILE_H

#include "Animal.h"

class reptile:public animal{
private:
    bool Venomous;

public:
    reptile(std::string name, float length, bool venomous){
        setName(std::move(name));
        setLength(length);
        Venomous = venomous;
    }

    bool getVenomous(){
        return Venomous;
    }
};
#endif //OBJECTORIENTEDPROGRAMMING_C_REPTILE_H
