#include "game.h"

WINNER winner_f( TICTACTOE *tictactoe)
{
    if ((tictactoe->board[0] == tictactoe->board[4]) && (tictactoe->board[4] == tictactoe->board[8]) && (tictactoe->board[8] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = diag_left_upper_to_right_lower;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[2] == tictactoe->board[4]) && (tictactoe->board[4] == tictactoe->board[6]) && (tictactoe->board[6] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = diag_right_upper_to_left_lower;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[0] == tictactoe->board[1]) && (tictactoe->board[1] == tictactoe->board[2]) && (tictactoe->board[2] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = row_0;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[3] == tictactoe->board[4]) && (tictactoe->board[4] == tictactoe->board[5]) && (tictactoe->board[5] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = row_1;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[6] == tictactoe->board[7]) && (tictactoe->board[7] == tictactoe->board[8]) && (tictactoe->board[8] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = row_2;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[0] == tictactoe->board[3]) && (tictactoe->board[3] == tictactoe->board[6]) && (tictactoe->board[6] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = column_0;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[1] == tictactoe->board[4]) && (tictactoe->board[4] == tictactoe->board[7]) && (tictactoe->board[7] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = column_1;
        return (WINNER)tictactoe->current_p;
    }
    else if((tictactoe->board[2] == tictactoe->board[5]) && (tictactoe->board[5] == tictactoe->board[8]) && (tictactoe->board[8] == tictactoe->current_p))
    {
        tictactoe->winner_st.winner_fields = column_2;
        return (WINNER)tictactoe->current_p;
    } 
    return w_no_winner;
}


void init_tictactoe( TICTACTOE *tictactoe)
{
    tictactoe->state_machine = start_game;
    tictactoe->current_p = c_player1;
    tictactoe->winner_st.winner = w_no_winner;
    tictactoe->winner_st.winner_fields = no_fields;
    tictactoe->first_move = true;
    
    for(int i = 0; i < 9; i++)
    {
        tictactoe->prev_board[i] = 0;
        tictactoe->board[i] = 0;
    }
}

void start_game_f( TICTACTOE *tictactoe)
{
    for(int i = 0; i<9; i++)
    {
        tictactoe->prev_board[i] = 0;
        tictactoe->board[i] = 0;
    }
    tictactoe->winner_st.winner = w_no_winner;
    tictactoe->winner_st.winner_fields = no_fields;
    tictactoe->first_move = true;
    tictactoe->current_p = c_player1;
    refresh_display_f( tictactoe->board, sizeof(tictactoe->board)/sizeof(int));
}

void refresh_display_f(const int *board, const int length)
{
    #if not DEBUG
    set_board_to_0();
    set_grid();
    #endif
    
    for(int i = 0; i < length; i++)
    {
        if(board[i] == -1)
        {           
            #if DEBUG
            Serial.print("board[");
            Serial.print(i);
            Serial.print("]");
            Serial.print(" == x\t");
            #else

            set_x(i);    // fields from 0 - 8
            #endif
        }
        else if(board[i] == 1)
        {
            #if DEBUG
            Serial.print("board[");
            Serial.print(i);
            Serial.print("]");
            Serial.print(" == o\t");
            #else
            set_o(i);    // fields from 0 - 8
            #endif
        }
        #if DEBUG
        else
        {
            Serial.print("board[");
            Serial.print(i);
            Serial.print("]");
            Serial.print(" == 0\t");
        }
        #endif
    
        #if DEBUG
        Serial.println();
        #endif
    }
    #if DEBUG
    Serial.println();
    #else
    show_board();    
    #endif
}

void coord_of_move( int *board, int *prev_board, const int length, int *pos)
{
    for(int i = 0; i < length; i++){

        if((prev_board[i] == 0) && (board[i] != 0))
        {
            *pos = i;
            break;  // New position found
        }
    }
}

void make_move_f( TICTACTOE *tictactoe)
{
    int first_field = 0;

    if(tictactoe->first_move == true)   // If true computer uses random number to make first move
    {
        tictactoe->first_move = false;
        srand(time(NULL));
        first_field = rand() % (NUMBER_FIELDS_OVERALL); // random number in % 9
        tictactoe->board[first_field] = -1; // player_1 is represented in board[] by -1
    }
    else
    {
        memcpy(tictactoe->prev_board, tictactoe->board, sizeof(tictactoe->board));  // safe previous score before new move of computer 
                                                                                    // to find out what his current move is. This information
                                                                                    // is required for Spielbetrieb. Webinterface requires the field
                                                                                    // of the computer
        computerMove( tictactoe->board, tictactoe->current_p);
        
    }

    if(tictactoe->betrieb == Demobetrieb)
    {
        delay(DELAY_COMPUTER_MOVE_MS);      // to slow down the game play
    }
    else
    {
        // Coordinates are neccessary for UI 
        coord_of_move( tictactoe->board, tictactoe->prev_board, sizeof(tictactoe->board)/sizeof(int),&tictactoe->computer_move);   
    }
}

int evaluate_game_f( TICTACTOE *tictactoe)
{
    WINNER tmp = w_no_winner;
    int count = 0;
    
    // Evaluate winner
    tmp = winner_f( tictactoe );

    if ( tmp == w_player1 )
    {
        tictactoe->winner_st.winner = w_player1;
        return 2;      
    }
    else if( tmp == w_player2 )
    {
        tictactoe->winner_st.winner = w_player2;
        return 2;
    }
   
    // No winner so far
    // Every field occupied?
    for(int i = 0; i < 9; i++)
    {   
        if((tictactoe->board[i] == -1) || (tictactoe->board[i] == 1))
        {
            count++;
        }
    }

    if( count == (NUMBER_FIELDS_OVERALL))   // If every field is occupied count == 9
    {
        tictactoe->winner_st.winner = w_unentschieden;
        return 1;
    }
    else
    {
        return 0; 
    }
}

void change_player_f( CURRENT_PLAYER *current_p)
{
    if( *current_p == c_player1)
    {
        *current_p = c_player2;
    }
    else
    {
        *current_p = c_player1;
    }
}

void fill_fields( WINNER_STRUCT *winner_st, int *win_board, int length)
{
    int tmp[9] = {0};

    switch( winner_st->winner_fields )
    {
        case diag_right_upper_to_left_lower:
        {
            tmp[2] = winner_st->winner;
            tmp[4] = winner_st->winner;
            tmp[6] = winner_st->winner;
            break;
        }

        case diag_left_upper_to_right_lower:
        {
            tmp[0] = winner_st->winner;
            tmp[4] = winner_st->winner;
            tmp[8] = winner_st->winner;
            break;
        }

        case row_0:
        {
            tmp[0] = winner_st->winner;
            tmp[1] = winner_st->winner;
            tmp[2] = winner_st->winner;
            break;
        }

        case row_1:
        {
            tmp[3] = winner_st->winner;
            tmp[4] = winner_st->winner;
            tmp[5] = winner_st->winner;
            break;
        }

        case row_2:
        {
            tmp[6] = winner_st->winner;
            tmp[7] = winner_st->winner;
            tmp[8] = winner_st->winner;
            break;
        }

        case column_0:
        {
            tmp[0] = winner_st->winner;
            tmp[3] = winner_st->winner;
            tmp[6] = winner_st->winner;
            break;
        }

        case column_1:
        {
            tmp[1] = winner_st->winner;
            tmp[4] = winner_st->winner;
            tmp[7] = winner_st->winner;
            break;
        }

        case column_2:
        {
            tmp[2] = winner_st->winner;
            tmp[5] = winner_st->winner;
            tmp[8] = winner_st->winner;
            break;
        }
        default:
        {
            break;// Sollte nicht passieren
        }
    }
    memcpy(win_board, tmp, sizeof(tmp));
}

void show_winner_f(WINNER_STRUCT *winner)
{
    int win_board[9] = {0};
    int empty_board[9] = {0};
    fill_fields( winner, win_board, sizeof(win_board)/sizeof(int));
    
    
    for(int i = 0; i < NUMBER_REP_SHOW_WINNER_FIELDS; i++)
    {
        refresh_display_f(empty_board, sizeof(empty_board)/sizeof(int));
        
        delay(DELAY_SHOW_WINNER_MS);

        refresh_display_f(win_board, sizeof(win_board)/sizeof(int));
        delay(DELAY_SHOW_WINNER_MS);
    }
}

void end_game_f( TICTACTOE *tictactoe)
{
    delay(DELAY_END_GAME_MS);
    tictactoe->first_move = true;
}


