//
//  Mancala.h
//  Mancala
//
//  Created by Leah Bar-On Simmons on 12/18/14.
//  Copyright (c) 2014 Shawn and Leah. All rights reserved.
//

#ifndef Mancala_Header_h
#define Mancala_Header_h

#include <iostream>
#include <cassert>
#include <vector>

//
//  main.cpp
//  Mancala
//
//  Created by Leah Bar-On Simmons on 10/24/14.
//  Copyright (c) 2014 Leah Bar-On Simmons. All rights reserved.
//

#include <iostream>
#include <cassert>
using namespace std;

//two rows of six holes/pits
//four pieces in each of the 12 holes
//each player a 'store' to their right side of the board
//one player starts by picking all pieces from one hole on his/her side, and depositing them counterclockwise in each hole that is not their opponents 'store' until the pieces they picked up run out
//player's alternate turns

//rules:
//If you run into your own store, deposit one piece and continue. If you run into your opponents store, skip it and continue
//If the last piece you drop is in your last store, you get a free turn
//If the last piece you drop is in an empty hole on your side, you capture the pieces opposite the hole, and they are deposited into your store
//the game ends when all holes on a single side are empty -- the player who still has pieces left on his side captures all remaining pieces, and deposits them into his/her store
//the winner is the player with the most pieces in his/her store

class Board{
    
public:
    static const int full_side = 6;
    
    //MAKE STORE AN ARRAY WITH STORE 1, 2 [STORE1,STORE2]
    bool player_finished = false;
    
    int side0[full_side] = {0, 0, 0, 0, 0, 0}; //player 1's side
    
    int store[2] = {0, 0}; //stores array, store[0] = player 1's store, store[1] = player 2's store

    int side1[full_side] = {0, 0, 0, 0, 0, 0}; //player 2's side
    
    int* determine_side(int i)
    {
        if (i == 0){
            return side0;
        }
        else{
            return side1;
        }
    }
    

};


class Player{
    string name;
    int number;
public:
    string getName(){
        return name;
    }
    
    void setName(string name_in){
        name = name_in;
    }
    void setNum(int num_in){
        number = num_in;
    }
    int getNum(){
        return number;
    }
};



void initializePlayers(Player &player1, Player &player2);


int switchSides(int i); //switches side of board


void fillBoard(Board &board); //fills board


//sees if the player placed their last piece in an empty slot/
//if so they capture the pieces across from that spot on the other side of the board
void capture(Board &board, Player*currentplayer, int &player_num, int*currentside,
             int index, Player players[]);

void playOtherSide(Board &board, Player* currentplayer, int &player_num,
                   int* currentside, int &pieces_in_hand, Player players[]); //3rd in the set of functions to play turn

void playStore(Board &board, Player* currentplayer, int &player_num,
               int* currentside, int &pieces_in_hand, Player players[]);//2nd in the set of functions to play turn


void playInitialSide(Board &board, Player* currentplayer, int &player_num,
                     int* currentside, int &pieces_in_hand, Player players[]); //first in the set of functions to play turn

void playTurn(Board &board, Player* current_player, int round, bool redo,
              bool freeturn, Player players[]); //plays through a turn


Player* switchPlayer(Player* current_player, Player players[]); //switches player

void printBoard(Board &board, Player players[]); //prints board

void determine_winner(Board &board, Player players[]);



#endif
