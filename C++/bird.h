//
// Created by seanp on 10/01/2019.
//

#ifndef OBJECTORIENTEDPROGRAMMING_C_BIRD_H
#define OBJECTORIENTEDPROGRAMMING_C_BIRD_H

#include "Animal.h"

class bird:public animal{
private:
    bool CanFly;

public:
    bird(std::string name, float length, bool canFly){
        setName(std::move(name));
        setLength(length);
        CanFly = canFly;
    }

    bool getCanFly(){
        return CanFly;
    }
};
#endif //OBJECTORIENTEDPROGRAMMING_C_BIRD_H
