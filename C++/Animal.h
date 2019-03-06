#include <utility>

//
// Created by seanp on 10/01/2019.
//

#ifndef OBJECTORIENTEDPROGRAMMING_C_ANIMAL_H
#define OBJECTORIENTEDPROGRAMMING_C_ANIMAL_H

#include <iostream>

class animal {
    std::string Name;
    float Length;

public:
    void setName(std::string name){
        Name = std::move(name);
    }

    void setLength(float length){
        Length = length;
    }

    std::string getName(){
        return Name;
    }

    float getLength(){
        return Length;
    }

    ~animal() = default;
};


#endif //OBJECTORIENTEDPROGRAMMING_C_ANIMAL_H
