#include <utility>

//
// Created by seanp on 10/01/2019.
//

#ifndef OBJECTORIENTEDPROGRAMMING_C_MAMMAL_H
#define OBJECTORIENTEDPROGRAMMING_C_MAMMAL_H

#include "Animal.h"
class mammal:public animal{
    float averageLitterSize;

public:
    mammal(std::string name, float length, float avLitterSize){
        setName(std::move(name));
        setLength(length);
        averageLitterSize = avLitterSize;
    }

    float getAverageLitterSize(){
        return averageLitterSize;
    }
};
#endif //OBJECTORIENTEDPROGRAMMING_C_MAMMAL_H
