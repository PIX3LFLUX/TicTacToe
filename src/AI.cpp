#include "AI.h"

int win(const int board[9])
{
    //determines if a player has won, returns 0 otherwise.
    /*
    | 0 | 1 | 2 |
    | 3 | 4 | 5 |
    | 6 | 7 | 8 |
    */
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};    // Every possible combination of winner fields
    int i;

    for(i = 0; i < 8; ++i)
    {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
           {
                return board[wins[i][2]];   // if player 1 has won it returns -1; if player 2 has won it returns 1
           }
    }
    return 0;
}

int min_max(int board[9], int player)
{
    //How is the position like for player (their turn) on board?
    int winner = win(board);// return -1 , 0 or 1
    if(winner != 0)
    {
        return winner*player;// player1 == -1; player2 == 1
    }
    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i)
    {//For all moves,
        if(board[i] == 0)
        {//If legal,
            board[i] = player;//Try the move
            int thisScore = -min_max(board, player*-1);
            if(thisScore > score)
            {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1)
    {
        return 0;
    }
    return score;
}

void computerMove(int board[9], int player)
{
    int move = -1;
    int score = -2;
    int other_player;
    int i;

    if(player == -1)    // player1
    {
        other_player = 1;   // player2
    }
    else
    {
        other_player = -1;
    }
    for(i = 0; i < 9; ++i)
    {
        if(board[i] == 0)
        {
            board[i] = player;
            int tempScore = -min_max(board, other_player);
            board[i] = 0;
            if(tempScore > score)
            {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on min_max() tree at a given node.
    board[move] = player;
}