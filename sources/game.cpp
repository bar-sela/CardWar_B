
#include "game.hpp"
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <random>
//https://www.geeksforgeeks.org/rand-and-srand-in-ccpp/ srand and rand
//https://www.geeksforgeeks.org/vector-erase-and-clear-in-cpp/ erase
using namespace std;



Game::Game(Player& player1 , Player& player2) : a(player1) , b(player2) {
    
   
    srand(time(nullptr));
    /// initial log :
    this ->lastTurn = "";
    this->log = "";
    this->numberOfDraws = 0;
    ///Randomly distribute cards to players
    vector<card> cards;
    for(size_t i =0 ; i < num.size(); i++){
        for(size_t j =0 ; j < shape.size() ; j++){
               size_t number = num[i]; 
               const string s = shape[j];
               card carD(number, s);
               cards.push_back(carD);
    }
}
    for (size_t i = 0; i < 26; i++) {
      size_t index1 = static_cast<size_t>(rand()) % cards.size();
       this->a.getV().push_back(cards.at(index1));
       cards.erase(cards.begin() + (std::vector<card>::difference_type )index1);
        size_t index2 = static_cast<size_t>(rand()) % cards.size();
        this->b.getV().push_back(cards.at(index2));
       cards.erase(cards.begin() + (std::vector<card>::difference_type )index2);
    }
/*
    default_random_engine rng( std::random_device rd);
    shuffle(cards.begin(), cards.end(), rng);
    for (size_t i = 0; i < 52; i++) {
        if(i % 2  == 0 )
            this->a.getV().push_back(cards[i]);
        else
              this->b.getV().push_back(cards[i]);
              */
      
        /*
      this->a.getV().at(i) = cards.at(index1);
       cards.erase(cards.begin() + index1);
        size_t index2 = static_cast<size_t>(rand()) % cards.size();
       this->b.getV().at(i) = cards.at(index2);
       cards.erase(cards.begin() + index2);
       */
    }







void Game::playTurn() {
     if (&this->a == &this->b) 
          throw "same!";
    if(this->a.stacksize() == 0)
        throw "you already finished the game";
    std::string name1 = this->a.getName();
    std::string name2 = this->b.getName();
    this->lastTurn = "";
    /// the game finished while were in war situation
    int numberOfDrawsInTurn = 0;
    bool done = false;
    vector<card> playerCardsTurn1;
    vector<card> playerCardsTurn2;
    while ( !done){
    if (this->a.stacksize() == 0) {  /// cards done during tie or their are no more cards for another turn
        for (auto &turnPuttedCard: playerCardsTurn1) {
            this->a.getWinCards().push_back(turnPuttedCard);
        }
        for (auto &turnPuttedCard: playerCardsTurn2) {
            this->b.getWinCards().push_back(turnPuttedCard);
        }
        done = true;
        continue;
    }
       /// convert
        size_t cardNumberA = this->a.getV().back().getNumber();
        size_t cardNumberB = this->b.getV().back().getNumber();
      //  cout<< "("+ strings[cardNumberA]+","+strings[cardNumberB] +")"<<endl;
        /// get the next element from each stack
        card *playerCard1 = &this->a.getV().back();
        playerCardsTurn1.push_back(*playerCard1);
        card *playerCard2 = &this->b.getV().back();
        playerCardsTurn2.push_back(*playerCard2);
        /// pop the first element from each  player stack
        this->a.getV().pop_back();
        this->b.getV().pop_back();
        /// lastTurn adding
        this->lastTurn += name1 +" "+ strings[cardNumberA] + " of " + (*playerCard1).getShape()+ " ";
        this->lastTurn += name2 + " " +strings[cardNumberB] + " of " + (*playerCard2).getShape() + " ";
        /// wining situation
        if (cardNumberA == Ace && cardNumberB == 2) {
            winningSituation(this->b, numberOfDrawsInTurn, playerCardsTurn1, playerCardsTurn2);
            cout << "speciel situation" << endl;
            done = true;
        } else if (cardNumberB == Ace && cardNumberA == 2) {
            winningSituation(this->a, numberOfDrawsInTurn, playerCardsTurn1, playerCardsTurn2);
            cout << "speciel situation" << endl;
            done = true;
        } else if (cardNumberA > cardNumberB) {
            winningSituation(this->a, numberOfDrawsInTurn, playerCardsTurn1, playerCardsTurn2);
            done = true;
        }
        else if (cardNumberB > cardNumberA) {
            winningSituation(this->b, numberOfDrawsInTurn, playerCardsTurn1, playerCardsTurn2);
            done = true;
        }
        else /// tie situation
        {
            this->lastTurn += " . Draw . ";
            numberOfDrawsInTurn++;
            if(a.stacksize() != 0) {
                playerCardsTurn1.push_back(this->a.getV().back()); /// pop another closed card
                playerCardsTurn2.push_back(this->b.getV().back());/// pop another closed card
                this->a.getV().pop_back();
                this->b.getV().pop_back();
            }
            this->numberOfDraws++;
        }
    }
}

void Game::winningSituation(Player &winingPlayer , int numberOfWars , vector<card> &playerCardsTurn1, vector<card> &playerCardsTurn2) {
    winingPlayer.setCardsTaken(numberOfWars * 4+2);
    this->lastTurn += "."+ winingPlayer.getName() + ".wins//" ;
    this->log += this->lastTurn;
    for (auto &turnPuttedCard: playerCardsTurn1) {
        winingPlayer.getWinCards().push_back(turnPuttedCard);
    }
    for (auto &turnPuttedCard: playerCardsTurn2) {
        winingPlayer.getWinCards().push_back(turnPuttedCard);
    }
    winingPlayer.setNumberOfWins(1);
}



void Game::printLastTurn() {
    cout << this ->lastTurn << endl;
}

void Game::printStats() {
       cout<< "player1 win cards:" <<endl;
       for(auto & item : this->a.getWinCards()){
           item.tpString();
       }
       cout<< "wining rate:" + std::to_string(this->a.getNumberOfWins()) <<endl;

       cout<< "player2 win cards:" <<endl;
       for(size_t i =0 ; i < this->b.getWinCards().size(); i++){
            this->b.getWinCards()[i].tpString();
       }
    cout<< "wining rate:" + std::to_string(this->b.getNumberOfWins()) <<endl;


       cout<< "draw number"+ std::to_string(this->numberOfDraws)<< endl;
}

void Game::printWiner() {
    if (this->a.cardesTaken() > this->b.cardesTaken())
        cout << this->a.getName() << endl;
    else if (this->a.cardesTaken() < this->b.cardesTaken())
        cout << this->b.getName() << endl;
    else /// draw
          cout << "its a tie!!" << endl;

}
    void Game::playAll() {
        while (this->a.stacksize() != 0) {
            this->log += "\n";
            this->playTurn();
        }
    }

    void Game::printLog() {
        cout << this->log << endl;
    }






