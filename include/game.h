#ifndef WEBSERVER_GAME_H
#define WEBSERVER_GAME_H

#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <Arduino.h>


#include "panel.h"
#include "AI.h"

#define DEBUG 0

#define NUMBER_FIELDS_OVERALL 9
#define NUMBER_REP_SHOW_WINNER_FIELDS 3
#define DELAY_SHOW_WINNER_MS 150
#define DELAY_COMPUTER_MOVE_MS 1000
#define DELAY_END_GAME_MS 2000

typedef enum{
    Spielbetrieb,
    Demobetrieb,
}BETRIEB;

typedef enum{
    no_fields,
    diag_left_upper_to_right_lower,
    diag_right_upper_to_left_lower,
    row_0,
    row_1,
    row_2,
    column_0,
    column_1,
    column_2
}WINNER_FIELDS;

typedef enum{
    start_game,
    refresh_display,
    make_move,
    evaluate_game,
    change_player,
    show_winner,
    end_game
}STATE_TICTACTOE;

typedef enum{
    c_player1 = -1,
    c_player2 = 1
}CURRENT_PLAYER;

typedef enum{
    w_no_winner,
    w_player1 = -1,
    w_player2 = 1,
    w_unentschieden
}WINNER;

typedef struct{
    WINNER winner;
    WINNER_FIELDS winner_fields;
}WINNER_STRUCT;

typedef enum{
    human,    
    computer,  // Spieler 1 ist der Computer
}PLAYER;

typedef struct{
    CURRENT_PLAYER current_p;
    WINNER_STRUCT winner_st;
    STATE_TICTACTOE state_machine;
    BETRIEB betrieb;
    PLAYER player1;
    PLAYER player2;
    int computer_move;   // Beinhaltet die Koordinaten des aktuellen Zugs des Computers
    int prev_board[9];
    int board[9];
    bool first_move;
}TICTACTOE;

void refresh_display_f(const int board[9], const int length);
int evaluate_game_f( TICTACTOE *tictactoe);
void init_tictactoe( TICTACTOE *tictactoe);
void start_game_f( TICTACTOE *tictactoe);
void change_player_f( CURRENT_PLAYER *current_p);
void make_move_f( TICTACTOE *tictactoe);
void show_winner_f(WINNER_STRUCT *winner);
void end_game_f( TICTACTOE *tictactoe);

#endif