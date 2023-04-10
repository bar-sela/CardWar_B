//
// Created by barse on 3/22/2023.
//
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <iostream>
#include <utility>
#include <vector>

#include "card.hpp"



class Player {
private:
    int cardsTaken ;
    std::string name ;
    std::vector<card> v;
    std::vector<card> winCards ;
    int numberOfWins  ;


public:
    /// constructors
    explicit Player(std::string s) {
        this->name = std::move(s);
        this-> cardsTaken = this ->numberOfWins =0 ;
    }
    /// getters
    std::vector<card> &getV() {
        return this->v;
    }
    std::vector<card>& getWinCards() {
        return this->winCards;
    }
    std::string getName() {
        return this->name;
    }
    int getNumberOfWins() const {
        return this->numberOfWins;
    }
    void setNumberOfWins(int number) {
        this->numberOfWins++;
    }
    void setCardsTaken(int number) {
        this->cardsTaken = this->cardsTaken + number;
    }

    int stacksize(); //prints the amount of cards left. should be 21 but can be less if a draw was played
    int cardesTaken();// prints the amount of cards this player has won.

};









#endif //PLAYER_HPP
