//
// Created by barse on 3/22/2023.
//

#include "card.hpp"
#include "game.hpp"


std::string card::tpString() {
    std::string s = "("+this->shape +","+ strings[this->number]+")";
    return s;
}
