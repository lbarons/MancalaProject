//
//  Main.cpp
//  Mancala
//
//  Created by Leah Bar-On Simmons on 12/27/14.
//  Copyright (c) 2014 Shawn and Leah. All rights reserved.
//

#include <stdio.h>
#include "Mancala.h"
int main() {
    Board board;
    Player player1_var;
    Player player2_var;
    
    initializePlayers(player1_var, player2_var);
    Player* player1 = &player1_var;
    Player* player2 = &player2_var;
    Player players[] = {*player1, *player2};
    
    printBoard(board, players);
    cout << endl << endl << "Ready to Start?" << endl;
    string answer;
    cin >> answer;
    if (answer == "yes" or answer == "Yes"){
        fillBoard(board);
    }
    else{
        cout << "Play again later!" << endl;
        return 0;
    }
    
    printBoard(board, players);
    
    Player* currentPlayer = &player1_var;
    
    //cout << currentPlayer->getName();
    

    //while (player_finished == false)
    //BIG LOOP HERE
    //MAKE THIS A FUNCTION
    int round = 1;
    while (true){
        
        playTurn(board, currentPlayer, round, false, false,
                 players);
        if (board.player_finished){
            break;
        }
        
        printBoard(board, players);
        
        //is there a better way to do this
        currentPlayer = switchPlayer(currentPlayer, players); //(player pointer, array of players
        
        round++;
        
        
        //cout << currentPlayer->getNum();
        
        //setting bool if one player has cleared his/her side
        //need to figure out a way to set the side of the board given the current player
        //for (board->side)
        
    }
    
    determine_winner(board, players);
    
    
    return 0;
    
}//end main