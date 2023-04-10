//
// Created by barse on 3/22/2023.
//

#include "player.hpp"


int Player::stacksize() {
    return this->getV().size();
}

int Player::cardesTaken() {
    return this->cardsTaken ;
};