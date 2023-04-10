//
// Created by barse on 3/22/2023.
//

#ifndef CARD_HPP
#define CARD_HPP

#include <string>


namespace ariel{

};

class card {
private:
    size_t number;
    std::string shape;
public:
    size_t getNumber() const {
        return this->number;
    }
    std::string getShape() {
        return this->shape ;
    }

    card(size_t number , const std::string& shape){
       this->number = number;
       this->shape = shape;
    }
    std::string tpString();
};



#endif //WAR_GAME_CARD_HPP
