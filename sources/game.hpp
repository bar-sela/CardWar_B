//
// Created by barse on 3/22/2023.
//

#ifndef GAME_HPP
#define GAME_HPP

#include "card.hpp"
#include "player.hpp"
#include <array>



using namespace  std;
enum game{Jack = 11 ,Queen = 12  , King = 13 , Ace = 14 };
const array<size_t,13> num ={Ace ,2,3,4,5,6,7,8,9,10,Jack,Queen,King};
const array<string ,15> strings ={"-1","-1","2","3","4","5","6","7","8","9","10","Jack","Queen","King","Ace"};
const array<string,4> shape= {"Heart","Spade" , "Club","Diamond"};
class Game {

private:
    Player &a;
    Player &b;
    string lastTurn;
    string log ;
    int numberOfDraws;
public:
    Game();
    Game(Player &player1, Player &player2);
    void playAll(); //playes the game untill the end
    void printWiner(); // prints the name of the winning player
    void printLog(); // prints all the turns played one line per turn (same format as game.printLastTurn())
    void printStats();
    void printLastTurn();
    void playTurn();
    void winningSituation(Player &winingPlayer , int numberOfWars , vector<card> &playerCardsTurn1, vector<card> &playerCardsTurn2);
    /// myFunctions
    static int convert(Player&);


};
#endif //WAR_GAME_GAME_HPP