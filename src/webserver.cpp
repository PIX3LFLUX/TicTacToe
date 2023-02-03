
#include "webserver.h"

extern Task show_text_task;
extern Task show_winner_task;
extern Task refresh_board_task;

const char* PLAYER1 = "p1";
const char* COLOR_PLAYER1 = "cP1";
const char* PLAYER2 = "p2";
const char* COLOR_PLAYER2 = "cP2";
const char* COLOR_PANEL = "cPl";
const char* FIELD = "fld";
const String ZUG_SPIELER_1 = "Spieler 1 ist am Zug";
const String ZUG_SPIELER_2 = "Spieler 2 ist am Zug";
const String GEWINNER_SPIELER_1 = "Spieler 1 hat das Spiel gewonnen";
const String GEWINNER_SPIELER_2 = "Spieler 2 hat das Spiel gewonnen";
const String UNENTSCHIEDEN = "Das Spiel ist unentschieden ausgegangen";

const char* tbody_html = "<tbody><tr>\
<td id=\"fld1\"><form><button name=\"fld\" type=\"button\" value=\"fld1\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
<td id=\"fld2\"><form><button name=\"fld\" type=\"button\" value=\"fld2\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
<td id=\"fld3\"><form><button name=\"fld\" type=\"button\" value=\"fld3\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
</tr><tr><td id=\"fld4\"><form><button name=\"fld\" type=\"button\" value=\"fld4\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
<td id=\"fld5\"><form><button name=\"fld\" type=\"button\" value=\"fld5\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
<td id=\"fld6\"><form><button name=\"fld\" type=\"button\" value=\"fld6\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
</tr><tr><td id=\"fld7\"><form><button name=\"fld\" type=\"button\" value=\"fld7\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
<td id=\"fld8\"><form><button name=\"fld\" type=\"button\" value=\"fld8\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
<td id=\"fld9\"><form><button name=\"fld\" type=\"button\" value=\"fld9\" onclick=\"s_fld(this)\" disabled> </button></form></td>\
</tr></tbody>";

RECEIVED_PARAMS received_params;
TICTACTOE tictactoe;
AsyncWebServer server(80);
IPAddress ip_address;

void set_wifi_params()
{
    WiFi.softAP(ESP_SSID, PASSWORD, WIFI_CHANNEL_NUMBER, DONT_HIDE_SSID, MAX_CLIENTS);
}

uint32_t parse_color( const String colorString)
{
    uint8_t temp[6]; // stores preconverted chars to hex values
    uint8_t tempSize = 0;

    for (uint8_t indexChar = 0; indexChar < colorString.length() && indexChar < 8; indexChar++)
    {
        char c = colorString.c_str()[indexChar];
        if (c >= '0' && c <= '9')
        {
            c -= '0';
        }
        else
        {
            // Convert a letter to lower case (only for ASCII letters)
            // It's faster & smaller than tolower()
            c |= 32;
            if (c >= 'a' && c <= 'f')
            {
                c = c - 'a' + 10;
            }
            else
            {
                // we found an non hexidecimal char
                // which could be null, deliminator, or other spacing
                break;
            }
        }

        temp[tempSize] = c;
        tempSize++;
    }

    if (tempSize != 3 && tempSize != 6)
    {
        // invalid count of numerical chars
        return 0;
    }
    else
    {
        uint32_t color = 0;
        for (uint8_t indexChar = 0; indexChar < tempSize; indexChar++)
        {
            color = color * 16 + temp[indexChar];
            if (tempSize == 3)
            {
                // 3 digit hexadecimal notation can be supported easily
                // duplicating digits.
                color = color * 16 + temp[indexChar];
            }
        }

        return color;
    }
}

void set_received_params(const RECEIVED_PARAMS *params)
{
    uint32_t color_number = 0;

    color_number = parse_color(received_params.color_player1);
    set_color_x(color_number);

    color_number = parse_color(received_params.color_player2);
    set_color_o(color_number);

    color_number = parse_color(received_params.color_panel);
    set_color_grid(color_number);

    if(received_params.player1 == "Spieler")
    {
        tictactoe.player1 = human;
    }
    else
    {
        tictactoe.player1 = computer;
    }

    if(received_params.player2 == "Spieler")
    {
        tictactoe.player2 = human;
    }
    else
    {
        tictactoe.player2 = computer;
    }
}

void parse_field(const char *field, TICTACTOE *tictactoe)
{
    if(strcmp(field, "fld1") == 0)
    {
        tictactoe->board[0] = tictactoe->current_p;
        
    }
    else if(strcmp(field, "fld2") == 0)
    {
        tictactoe->board[1] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld3") == 0)
    {
        tictactoe->board[2] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld4") == 0)
    {
        tictactoe->board[3] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld5") == 0)
    {
        tictactoe->board[4] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld6") == 0)
    {
        tictactoe->board[5] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld7") == 0)
    {
        tictactoe->board[6] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld8") == 0)
    {
        tictactoe->board[7] = tictactoe->current_p;
    }
    else if(strcmp(field, "fld9") == 0)
    {
        tictactoe->board[8] = tictactoe->current_p;
    }
}

void get_field( String *comp_field, int field)
{
    switch(field)
    {
        case 0:
        {
            *comp_field = "fld1";
            break;
        }
        case 1:
        {
            *comp_field = "fld2";
            break;
        }
        case 2:
        {
            *comp_field = "fld3";
            break;
        }
        case 3:
        {
            *comp_field = "fld4";
            break;
        }
        case 4:
        {
            *comp_field = "fld5";
            break;
        }
        case 5:
        {
            *comp_field = "fld6";
            break;
        }
        case 6:
        {
            *comp_field = "fld7";
            break;
        }
        case 7:
        {
            *comp_field = "fld8";
            break;
        }
        case 8:
        {
            *comp_field = "fld9";
            break;
        }
    }
}

void register_web_server_methods()
{
    // Route for root / web page
    server.on("/", HTTP_GET, [] (AsyncWebServerRequest *request)
    {
        show_text_task.disable();
        request->send_P(200, "text/html", page_html);
    });

    server.on("/start", HTTP_GET, [] (AsyncWebServerRequest *request)
    {
        String tmp = "";
        String comp_field = "";
        
        if (request->hasParam(PLAYER1) && request->hasParam(PLAYER2) && request->hasParam(COLOR_PLAYER1) // Safe received params
            && request->hasParam(COLOR_PLAYER2) && request->hasParam(COLOR_PANEL))
        {
            received_params.player1 = request->getParam(PLAYER1)->value();
            received_params.player2 = request->getParam(PLAYER2)->value();
            received_params.color_player1 = request->getParam(COLOR_PLAYER1)->value();
            received_params.color_player2 = request->getParam(COLOR_PLAYER2)->value();
            received_params.color_panel = request->getParam(COLOR_PANEL)->value();
            
            set_received_params( &received_params);
            start_game_f( &tictactoe);
            
            tictactoe.betrieb = Spielbetrieb;   // Set to Spielbetrieb so that the computer can make his move in fct. make_move_f without delay

            if(tictactoe.player1 == computer)   // First move is made by the computer
            {
                make_move_f( &tictactoe);
                change_player_f(&tictactoe.current_p);
                get_field( &comp_field, tictactoe.computer_move);
                tmp += "<p>"+ZUG_SPIELER_2+"</p>";
                tmp += "<form id=\"f_start_button\"><input type=\"button\" value=\"Spiel beenden\" onclick=\"end()\"><br /></form>";
                tmp += "<fld>"+comp_field+"</fld>";
            }
            else
            {
                tictactoe.first_move = false;   // Just to be shure that the computer does not make any move by random number
                tmp += "<p>"+ZUG_SPIELER_1+"</p>";
                tmp += "<form id=\"f_start_button\"><input type=\"button\" value=\"Spiel beenden\" onclick=\"end()\"><br /></form>";
            }
            #if DEBUG
            Serial.println(tmp);
            #endif
            refresh_board_task.enable();
            request->send(200, "text/html", tmp);
        }
    });

    server.on("/s_fld", HTTP_GET, [] (AsyncWebServerRequest *request)
    {
        String tmp = "";                	// String wird säter als Antwort an den Client zurückgesendet und hat den folgenden Aufbau
                                            // "XXX<p>Text</p><fld>fldX</fld>" Das dritte Zeichen kann 0 oder 1 sein und signalsiert, dass das Spiel zu Ende ist. Der "Text" wird entsprechend angepasst
                                            // Das erste Zeichen signalisiert dem Client ob er ein 'o' oder 'x' zu setzen hat.
                                            // Das zweite Zeichen signalisiert dem Client ob er ein weiteres Feld belegen soll. Dies wäre der Fall, wenn einer der Spieler der Computer ist. Das dritte Zeichen kann '0', 'x' oder 'o' sein.
                                            // Wenn '0', dann soll kein zweites Feld belegt werden
        String current_field = "";
        String comp_field = "";
        int ret = -1;
         
        if(!request->hasParam(FIELD))
        {
            return;
        }
        current_field = request->getParam(FIELD)->value();
        parse_field(current_field.c_str(), &tictactoe);
    
        if(tictactoe.current_p == c_player1)    // Set first char
        {
            tmp += "x";
        }
        else
        {
            tmp += "o";
        }
        
        if(tictactoe.winner_st.winner == w_player1 || tictactoe.winner_st.winner == w_player2)  // Check for winner
        {
            ret = 2;
        }
        else if(tictactoe.winner_st.winner == w_unentschieden)
        {
            ret = 1;
        }
        else
        {
            ret = evaluate_game_f( &tictactoe);
        }

        change_player_f( &tictactoe.current_p);

        switch(ret)
        {
            case 0: // No winner and not every field is occupied
            {
                if((tictactoe.player1 == computer) || (tictactoe.player2 == computer))  // If computer is one of the player 
                                                                                        // let the computer make his move
                {
                    if(tictactoe.player1 == computer)
                    {
                        tmp += "x"; // Set second char
                    }
                    else if(tictactoe.player2 == computer)
                    {
                        tmp += "o";
                    }
                    memcpy(tictactoe.prev_board, tictactoe.board, sizeof(tictactoe.board)); // Copy fields to prev_board for later evaluation
                
                    make_move_f(&tictactoe);
                    ret = evaluate_game_f(&tictactoe);
                    get_field( &comp_field, tictactoe.computer_move);
                    change_player_f( &tictactoe.current_p);
                    
                    switch(ret)
                    {
                        case 0:
                        {
                            tmp += "0"; // Set third char
                            if(tictactoe.current_p == c_player1)
                            {   
                                tmp += "<p>"+ZUG_SPIELER_1+"</p>";  // Next player1
                            }
                            else
                            { 
                                tmp += "<p>"+ZUG_SPIELER_2+"</p>";  // Next player2
                            }
                            break;
                        }
                        case 1:
                        {
                            tmp += "1"; // Set third char
                            tmp += "<p>"+UNENTSCHIEDEN+"</p>";
                            break;
                        }   
                        case 2:
                        {
                            tmp += "1"; // Set third char
                            if(tictactoe.winner_st.winner == w_player1)
                            {
                                tmp += "<p>"+GEWINNER_SPIELER_1+"</p>";
                            }
                            else if(tictactoe.winner_st.winner == w_player2)
                            {
                                tmp += "<p>"+GEWINNER_SPIELER_2+"</p>";
                            }
                            show_winner_task.enable();
                            break;
                        }
                    }
                    tmp += ("<fld>"+comp_field+"</fld>"); // Contains current move of computer
                }
                else
                {
                    tmp += "0"; // Set second char to '0', because no computer
                    tmp += "0"; // Drittes char setzen
                    if(tictactoe.current_p == c_player1)    // Current player has already been changed
                    {   
                        tmp += "<p>"+ZUG_SPIELER_1+"</p>";  // Next player1
                    }
                    else
                    { 
                        tmp += "<p>"+ZUG_SPIELER_2+"</p>";  // Next player2
                    }
                }
                break;
            }

            case 1: // No winner, every field is occupied
            {
                tmp += "0"; // Set second char.
                tmp += "1"; // Set third char.
                tmp += "<p>"+UNENTSCHIEDEN+"</p>";
                break;
            }

            case 2: // Winner
            {
                tmp += "0"; // Set second char.
                tmp += "1"; // Set third char.
                if(tictactoe.winner_st.winner == w_player1)
                {
                    tmp += "<p>"+GEWINNER_SPIELER_1+"</p>";
                }
                else if(tictactoe.winner_st.winner == w_player2)
                {
                    tmp += "<p>"+GEWINNER_SPIELER_2+"</p>";
                }
                show_winner_task.enable();
                break;
            }
        }

        #if DEBUG
        Serial.println(tmp);
        #endif
        refresh_board_task.enable();
        request->send(200, "text/html", tmp);
    });

    server.on("/end", HTTP_GET, [] (AsyncWebServerRequest *request)
    {
        tictactoe.current_p = c_player1;
        String tmp = "";
        tmp += tbody_html;
        tmp += "<p>&nbsp;</p>";
        tmp += "<form id=\"f_start_button\"><input type=\"button\" value=\"Spiel starten\" onclick=\"start()\"><br /></form>";
        request->send(200, "text/html", tmp);
    });
}





