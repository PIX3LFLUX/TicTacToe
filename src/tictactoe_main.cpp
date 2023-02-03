
#include "tictactoe_main.h"
#include <TaskScheduler.h>

Scheduler scheduler;

bool web_server_enable_cb();
void refresh_board_cb();
void show_winner_cb();
void show_text_cb();
void tictactoe_demo_cb();

Task web_server_task( TASK_MILLISECOND, TASK_ONCE, NULL, &scheduler, false, &web_server_enable_cb);
Task show_winner_task( TASK_IMMEDIATE, TASK_FOREVER, &show_winner_cb, &scheduler, false);
Task refresh_board_task(TASK_IMMEDIATE, TASK_FOREVER, &refresh_board_cb, &scheduler, false);
Task show_text_task(TASK_IMMEDIATE, TASK_FOREVER, &show_text_cb, &scheduler, false);
Task run_demo_task(TASK_MILLISECOND, TASK_FOREVER, &tictactoe_demo_cb, &scheduler, false);

extern TICTACTOE tictactoe;
extern AsyncWebServer server;
extern IPAddress ip_address;

IRAM_ATTR void switch_between_modes()   // Interrupt for Spielbetrieb switch
{
  if(digitalRead(GPIO_PIN_SWITCH) == HIGH)
  {
    WiFi.softAPdisconnect();
    web_server_task.disable();
    show_text_task.disable();
    run_demo_task.enableIfNot();
  }
  else
  {
    set_wifi_params();
    run_demo_task.disable();
    web_server_task.enableIfNot();
  }
}

void tictactoe_main()
{
    pinMode( GPIO_PIN_SWITCH, INPUT_PULLUP);
    attachInterrupt( digitalPinToInterrupt( GPIO_PIN_SWITCH ), switch_between_modes, CHANGE);
    set_wifi_params();
    ip_address = WiFi.softAPIP();
    init_tictactoe( &tictactoe);
    tictactoe.betrieb = Spielbetrieb;
    register_web_server_methods();

    if(digitalRead(GPIO_PIN_SWITCH) == HIGH)
    {
        WiFi.softAPdisconnect();
        run_demo_task.enable();
    }
    else
    {
        web_server_task.enable();
    }

    while(1)
    {
        scheduler.execute();
    }
    
}

void tictactoe_demo_cb()
{
    TICTACTOE s_tictactoe;

    init_tictactoe( &s_tictactoe );

    #if not DEBUG
    initialize_board();
    set_color_text(DEMO_COLOR_TEXT);
    set_color_grid(DEMO_COLOR_GRID);
    set_color_o(DEMO_COLOR_PLAYER_O);
    set_color_x(DEMO_COLOR_PLAYER_X);
    #endif
    s_tictactoe.betrieb = Demobetrieb;

    do
    {
        switch (s_tictactoe.state_machine)
        {
            case start_game:
            {
                start_game_f( &s_tictactoe );
                s_tictactoe.state_machine = make_move;
                break;
            }

            case make_move:
            {
                make_move_f( &s_tictactoe);
                s_tictactoe.state_machine = refresh_display;
                break;
            }

            case refresh_display:
            {
                refresh_display_f( s_tictactoe.board, sizeof(s_tictactoe.board)/sizeof(int));
                s_tictactoe.state_machine = evaluate_game;
                break;
            }

            case evaluate_game:
            {
                int ret = 0;

                ret = evaluate_game_f( &s_tictactoe );
                if( ret == 0)   // No winner nad not every field is occupied
                {
                    s_tictactoe.state_machine = change_player;
                }
                else if ( ret == 1 )    // No winner, every field is occupied
                {
                    s_tictactoe.state_machine = end_game;
                }
                else if (ret == 2)  // Winner
                {
                    s_tictactoe.state_machine = show_winner;
                }
                break;
            }

            case change_player:
            {
                change_player_f( &s_tictactoe.current_p );

                s_tictactoe.state_machine = make_move;
                break;
            }

            case show_winner:
            {
                show_winner_f(&s_tictactoe.winner_st);

                s_tictactoe.state_machine = end_game;
                break;
            }

            case end_game:
            {
                end_game_f( &s_tictactoe);

                s_tictactoe.state_machine = start_game;
                break;
            }

        
            default:
                break;
        }
    } while (run_demo_task.isEnabled());
}

void show_text_cb()
{
    #if DEBUG
    
    
        while(show_text_task.isEnabled())
        {
            Serial.println(ip_address.toString().c_str());
            delay(500);
        }
    #else

    TEXT_ARRAY *text_array;
    String tmp = "";
    tmp = "IP:  "+ip_address.toString()+"   ";

    text_array = build_text_array(tmp.c_str()); // Build the text array for the set_pixel_text function

    if( ( text_array == NULL ) || ( text_array->text_array == NULL ) )
    {
        return;
    }

    set_board_to_0();   // Set every pixel to black

    do
    {
        if( set_pixel_text( text_array ) != 0 ) // set the text to the pixel array and rotate this text left by
                                                // one column every time this function is called
        {
            break;  // setPixelText failed
        }
        show_board();
        delay(150);

    } while (show_text_task.isEnabled());
    
    free( text_array );
    set_board_to_0();
    show_board();
    #endif
}

bool web_server_enable_cb()
{
    show_text_task.enableIfNot();
    server.begin();
    return true;
}

void show_winner_cb()
{
    show_winner_f(&tictactoe.winner_st);
    show_winner_task.disable();
}

void refresh_board_cb()
{
    refresh_display_f(tictactoe.board, sizeof(tictactoe.board)/sizeof(int));
    refresh_board_task.disable();
}
