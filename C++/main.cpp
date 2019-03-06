#include <iostream>
#include <fstream>
#include <vector>

#include "BinarySearchTree.h"
#include "Animal.h"
#include "mammal.h"
#include "reptile.h"
#include "bird.h"

using namespace std;

struct animaltype{
    animaltype(animal* pointer, string animalName, int type){
        this->pointer = pointer;
        this->name = std::move(animalName);
        this->type = type;
    }

    animal* pointer;
    string name;
    int type;
}typedef animalType;

vector<string> getTokens(string line){
    size_t pos = 0;
    string delimiter = " ";

    string token;
    vector<string> toReturn;
    while((pos = line.find(delimiter)) != string::npos){
        token = line.substr(0, pos);
        toReturn.push_back(token);
        line.erase(0, pos + delimiter.length());
    }

    toReturn.push_back(line.substr(pos + delimiter.length(), line.length()));

    return toReturn;
}

void displayAnimal(animalType* animal_type){
    if(animal_type->type == 1){
        auto* currentAnimal = reinterpret_cast<mammal *>(animal_type->pointer);
        cout << "Type: Mammal" << endl;
        cout << "Name: " << currentAnimal->getName() << endl;
        cout << "Length: " << currentAnimal->getLength() << endl;
        cout << "Average Litter Size: " << currentAnimal->getAverageLitterSize() << endl;
    }else if(animal_type->type == 2){
        auto* currentAnimal = reinterpret_cast<reptile *>(animal_type->pointer);
        cout << "Type: Reptile" << endl;
        cout << "Name: " << currentAnimal->getName() << endl;
        cout << "Length: " << currentAnimal->getLength() << endl;
        if(currentAnimal->getVenomous()) {
            cout << "Is venomous" << endl;
        }else{
            cout << "Is not venomous" << endl;
        }
    }else if(animal_type->type == 3){
        auto* currentAnimal = reinterpret_cast<bird *>(animal_type->pointer);
        cout << "Type: Bird" << endl;
        cout << "Name: " << currentAnimal->getName() << endl;
        cout << "Length: " << currentAnimal->getLength() << endl;
        if(currentAnimal->getCanFly()) {
            cout << "Can fly" << endl;
        }else{
            cout << "Cannot fly" << endl;
        }
    }else{
        cout << "ERROR unknown type: " << animal_type->type << endl;
        return;
    }
    cout << "--------" << endl;
}

void loadFile(const string path){
    string line;
    ifstream myFile;
    myFile.open(path, ifstream::binary);
    auto animals = new BST<animal*>();
    vector<animalType*> lookupTable; //todo fix addition

    if(myFile.is_open()){
        while(getline(myFile, line)){
            vector<string> lineSplit = getTokens(line);

            string command = lineSplit[0];

            if(command == "Insert"){
                if(lineSplit.size() != 5){
                    cout << "invalid number of parameters on Insert expected 4, found " << lineSplit.size() - 1 << endl;
                    return;
                }
                string type = lineSplit[1];
                if(type == "mammal"){
                    auto newAnimal = new mammal(lineSplit[2], stof(lineSplit[3]), stof(lineSplit[4]));
                    animals->insert(newAnimal);
                    auto* typeObj = new animaltype(newAnimal, lineSplit[2], 1);
                    lookupTable.push_back(typeObj);
                }else if(type == "reptile"){
                    bool isVenomous;
                    if(lineSplit[4] == "venomous"){
                        isVenomous = true;
                    }else if(lineSplit[4] == "non-venomous"){
                        isVenomous = false;
                    }else{
                        cout << "invalid input in venomous/non-venomous category" << endl;
                        return;
                    }
                    auto newAnimal = new reptile(lineSplit[2], stof(lineSplit[3]), isVenomous);
                    animals->insert(newAnimal);
                    auto* typeObj = new animaltype(newAnimal, lineSplit[2], 2);
                    lookupTable.push_back(typeObj);
                }else if(type == "bird"){
                    bool canFly;
                    if(lineSplit[4] == "can-fly"){
                        canFly = true;
                    }else if(lineSplit[4] == "cannot-fly"){
                        canFly = false;
                    }else{
                        cout << "invalid input in can/cannot fly category" << endl;
                        return;
                    }
                    auto newAnimal = new bird(lineSplit[2], stof(lineSplit[3]), canFly);
                    animals->insert(newAnimal);
                    auto* typeObj = new animaltype(newAnimal, lineSplit[2], 3);
                    lookupTable.push_back(typeObj);
                }else{
                    cout << "Unexpected animal type" << endl;
                    return;
                }
            }else if(command == "Remove"){
                if(lineSplit.size() != 2){
                    cout << "invalid number of parameters on Remove expected 1, found " << lineSplit.size() - 1 << endl;
                    return;
                }
                for(int i = 0; i < lookupTable.size(); i++){
                    if(lookupTable[i]->name == lineSplit[1]){
                        animals->remove(lookupTable[i]->pointer);
                        lookupTable.erase(lookupTable.begin() + i); //deletes the current element
                    }
                }
            }else if(command == "Find"){
                if(lineSplit.size() != 2){
                    cout << "invalid number of parameters on Find expected 1, found " << lineSplit.size() - 1 << endl;
                    return;
                }

                for (auto &i : lookupTable) {
                    if(i->name == lineSplit[1]){
                        displayAnimal(i);
                    }
                }
            }
        }
    }else{
        cout << "Error opening file" << endl;
    }

    myFile.close();
    cout << "------" << endl;
    vector<animal*> returned = animals->inOrder(animals->getRootNode());

    for(auto &i: returned){
        for(auto &j: lookupTable){
            if(i == j->pointer){
                displayAnimal(j);
            }
        }
    }

    for(auto &i: lookupTable){
        delete(i->pointer);
        delete(i);
    }

    delete(animals);
}

int main(int argc, char *argv[]) {
    if(argc <= 1) {
        cout << "No file specified, loading default file" << endl;
        loadFile("oop-cpp-example.txt");
    }else{
        cout << "Loading file specified: " << argv[1] << endl;
        loadFile(argv[1]);
    }

    return 0;
}