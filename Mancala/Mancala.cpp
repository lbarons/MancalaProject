//
//  Mancala.cpp
//  Mancala
//
//  Created by Leah Bar-On Simmons on 10/24/14.
//  Copyright (c) 2014 Leah Bar-On Simmons. All rights reserved.
//
#include "Mancala.h"
#include <iostream>
#include <cassert>
using namespace std;



void initializePlayers(Player &player1, Player &player2){
    string player1_name;
    string player2_name;
    cout << "Player 1 please enter your name: " << endl;
    cin >> player1_name;
    player1.setName(player1_name);
    player1.setNum(0);
    
    cout << "Player 2 please enter your name: " << endl;
    cin >> player2_name;
    player2.setName(player2_name);
    player2.setNum(1);
}


int switchSides(int i){
    if (i == 0){
        return 1;
    }
    else{
        return 0;
    }
}


void fillBoard(Board &board){
    cout << endl << endl << "Filling Board..." << endl << endl;
    for (int i = 0; i < 6; ++i){
        board.side0[i] = 4; //changed to 0/1
    }
    
    for (int i = 0; i < 6; ++i){
        board.side1[i] = 4;
    }
    
    cout << "Your current Board: " << endl << endl;
}

void complete_final_capture(Board &board, int winner_side, Player players[]){
    
    //player who didn't clear side takes all remaining pieces and they go to their store
    if (winner_side == 0){
        for (int i = 0; i < board.full_side; ++i){
            board.store[1] += board.side1[i];
            board.side1[i] = 0;
        }
    }
    else{
        for (int i = 0; i < board.full_side; ++i){
            board.store[0] += board.side0[i];
            board.side0[i] = 0;
        }
        
    }
    
    printBoard(board, players);
    
}


//STOPPED WORK HERE
//ONLY NEED TO CHECK CURRENT PLAYERS SIDE FOR COMPLETION (not possible any other way)
//account for side and final capture?
bool check_if_done(Board &board, Player players[]){

    int side = -1;
    bool win = true;
    
    for (int i = 0; i < board.full_side; ++i){
        if (board.side0[i] != 0){
            win = false;
            break;
        }

    }
    //if all empty on side0
    if (win){
        side = 0;
        complete_final_capture(board, side, players);
        return true;
    }
    else{
        for (int i = 0; i < board.full_side; ++i){
            if (board.side1[i] != 0){
                win = false;
                break;
            }
        }
    }
    
    if (win){
        side = 1;
        complete_final_capture(board, side, players);
        return true;
    }
    
    return false;

}



//if the opposite hole is empty do they still get their piece into the store??
//@@@THIS IS ONLY IF THEY LAND IN EMPTY SPOT ON THEIR OWN SIDE!!!@@@
void capture(Board &board, Player *currentplayer, int &player_num, int *currentside, int index, Player players[]){
    
    int side_num = 0;
    
    int *savedside = 0;
    
    //is this the best way to compare?
    if (*currentside == *board.side0){
        side_num = 0;
        savedside = board.side0;
    }
    else if (*currentside == *board.side1){
        side_num = 1;
        savedside = board.side1;
    }
    
    //sees if the player placed their last piece in an empty slot
    //currentside will be whatever side they ended on by emptying their hand
    
    if (currentside[index] == 1){
        
        printBoard(board, players);
        
        currentside = board.determine_side(switchSides(side_num));
         //player_num isnt what we want to use here to determine side
         //updated to side_num
         
        board.store[player_num] += currentside[board.full_side - index - 1] + 1; //also get last placed piece (+1)
         

         
        currentside[board.full_side - index - 1] = 0; //empty that space
        
        //also need to empty current space of the one just placed
        savedside[index] = 0;

        
        //they capture the pieces across from that spot on the other side of the board
        cout << "Nice capture!" << endl;
        
        //THIS IS WORKING NOW

    }

    
}

void playOtherSide(Board &board, Player* currentplayer, int &player_num, int* currentside, int &pieces_in_hand, Player players[]){
    currentside = board.determine_side(switchSides(player_num)); //side is now 2
    int lastPlayedIndex = 0;
    int i = 0;
    for (; i < board.full_side; ++i){
        if (pieces_in_hand > 0){
            currentside[i] += 1;
            pieces_in_hand--;
            lastPlayedIndex = i;
        }
    }
    
    if (pieces_in_hand > 0){
        playInitialSide(board, currentplayer, player_num, currentside, pieces_in_hand, players);
    }
    else{
        capture(board, currentplayer, player_num, currentside, lastPlayedIndex, players);
    }
    //PUT THIS AT THE END OF EACH ONE
}

void playStore(Board &board, Player* currentplayer, int &player_num, int* currentside, int &pieces_in_hand, Player players[]){

        board.store[player_num]++;
        pieces_in_hand--;
    
    if (pieces_in_hand > 0){
        playOtherSide(board, currentplayer, player_num, currentside, pieces_in_hand, players);
    }
    else if(pieces_in_hand == 0){
        bool freeturn = true;
        playTurn(board, currentplayer, 3, false, freeturn, players);
    }

}



void playInitialSide(Board &board, Player* currentplayer, int &player_num, int* currentside, int &pieces_in_hand, Player players[]){
    int lastPlayedIndex = 0; //save where play stopped, pass that in to capture

    int i = 0;
    if (pieces_in_hand > 0){
        currentside = board.determine_side(player_num); //original side
        for (; i < board.full_side; ++i){
            if (pieces_in_hand > 0){
                currentside[i] += 1;
                pieces_in_hand--;
                lastPlayedIndex = i;
            }
        }
    }
    if (pieces_in_hand > 0){
        playStore(board, currentplayer, player_num, currentside, pieces_in_hand, players);
    }
    //call capture function
    else{
        capture(board, currentplayer, player_num, currentside, lastPlayedIndex, players);
    }
    
}


//GET NUMBER OF ROTATIONS FROM HOW MANY PIECES IN HAND!!!!!
//LIKE 20/2 = 10 ROTATIONS

void playTurn(Board &board, Player* current_player, int round, bool redo,
              bool freeturn, Player players[]){
    //player will choose a hole, that is where we will start
    //increment each hole counterclockwise on one side (Player 1's loop starts at index 5 and decrements to 0, whereas player 2's loop starts at index 0 and counts up
    //decrement count of pieces in hand
    //if count isn't done, place into appropriate store, and continue to other side
    if (check_if_done(board, players)){
        //end the game
        board.player_finished = true;
        return;
    }
    if ((round == 1 or round == 2) and !redo){
        cout << endl << current_player->getName() << ", it's your turn!" << endl;
        cout << "Please choose a space on your side and pick up your pieces!" << endl;
        cout << "Remember: you move counterclockwise" << endl;
    }
    else if (!redo and freeturn){
        printBoard(board, players);
        cout << "Nice! You get a free turn" << endl << endl;
    }
    else if (!redo){
        cout << endl << current_player->getName() << ", it's your turn!" << endl;
    }
    
    
    int chosenHole = 0;
    cout << "Chosen space: "; cin >> chosenHole;
    
    while (chosenHole > 6 or chosenHole < 1){
        cout << "That is not a valid space" << endl << "Please Try Again!" << endl;;
        cout << "Chosen space: "; cin >> chosenHole;
    }
    
    
    int player_num = current_player->getNum();
    
    int* currentside = board.determine_side(player_num);
    
    int index = 0;
    //index = chosenHole - 1;
    
    if (player_num == 0){
        index = chosenHole - 1;
    }
    
    else if (player_num == 1){
        index = board.full_side - chosenHole;
    }

    
    int pieces_in_hand = currentside[index];
    currentside[index] = 0; //empty chosen hole

    if (pieces_in_hand > 0){
        //need to determine player here, since they have different loops
        /*if (player_num == 0){ //current player is player 1
            */
        int i = index + 1;
        for (; i < board.full_side; ++i){
            if (pieces_in_hand > 0){
                currentside[i] += 1;
                pieces_in_hand--;
            }

        }
        if (pieces_in_hand > 0){
            
            playStore(board, current_player, player_num, currentside,
                      pieces_in_hand, players);
            
        }
        
        round++;
    }//for big if
    
    //NEED TO DEAL WITH NEGATIVES?? how to make sure this doesnt happen
    else{//pieces in hand is 0
        cout << "Sorry that space is empty! Please pick another space." << endl;
        playTurn(board, current_player, round, true, false, players);
        //recall function that chooses hole and plays turn
        //Don't want to reprint instructions
    }
    
    
    assert(pieces_in_hand >= 0);
    
}


Player* switchPlayer(Player* current_player, Player players[]){
    if (current_player->getNum() == 0){
        current_player = &players[1];
    }
    else if (current_player->getNum() == 1){
        current_player = &players[0];
    }
    return current_player;
}

void printBoard(Board &board, Player players[]){
    //cout << endl << "Your current Board: " << endl << endl;
    cout << endl << endl;
    cout << "        " << players[1].getName() << endl;

    for (int i = board.full_side - 1; i >= 0; --i){ //TO PRINT BACKWARDS
        cout << "  " << board.side1[i];
    }
    
    cout << endl << board.store[1] << "                  " << board.store[0] << endl;
    for (int i = 0; i < 6; ++i){
        cout << "  " << board.side0[i];
    }
    cout << endl << "        " << players[0].getName() << endl;
}



void determine_winner(Board &board, Player players[]){
    
    if (board.store[0] > board.store[1]){
        cout << "Congratulations " << players[0].getName() <<
        "! You're the winner!" << endl;
        
        cout << "You won with " << board.store[0] << " in your bank!";
        cout << " Your opponent had " << board.store[1] << " in their bank." << endl;
    }
    
    else if (board.store[1] > board.store[0]){
        cout << "Congratulations " << players[1].getName() <<
        "! You're the winner!" << endl;
        
        
        cout << "You won with " << board.store[1] << " in your bank!";
        cout << " Your opponent had " << board.store[0] << " in their bank." << endl;
    }
    
    else{//same value
        cout << "It's a tie!" << endl;
        cout << "Both players had " << board.store[0] << "in their bank!" << endl;
    }
    
    
    cout << endl;
    cout << "Thanks for playing!" << endl;
}
