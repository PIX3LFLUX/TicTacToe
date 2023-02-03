#ifndef WEBSERVER_TICTACTOE_H
#define WEBSERVER_TICTACTOE_H

#include <string.h>
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESPAsyncTCP.h>
#include <ESPAsyncWebServer.h>
#include <TaskSchedulerDeclarations.h>
#include "game.h"


#define ESP_SSID "ESP8266"
#define PASSWORD ""
#define WIFI_CHANNEL_NUMBER 1
#define DONT_HIDE_SSID 0
#define MAX_CLIENTS 1

typedef struct{
    String player1;
    String player2;
    String color_player1;
    String color_player2;
    String color_panel;
}RECEIVED_PARAMS;

const char page_html[] PROGMEM = R"rawliteral(<!DOCTYPE html><html><head><meta charset="utf-8"><meta name="viewport" content="width=device-width, initial-scale=1.0"><link rel="stylesheet" type="text/css" media="screen" /><title>Tic-Tac-Toe</title><style type="text/css">.container {display:flex;flex-direction:column;align-items:center;gap:10px;}.header {order:1;}.tic-tac-toe {order:2;}.tic-tac-toe table {border:2px;border-collapse:collapse;}
.tic-tac-toe td {border:1px solid black;height:6em;position:relative;text-align:center;width:6em;vertical-align:top}.tic-tac-toe td button {position:absolute;display:table-cell;height:98%;width:98%;border:0px;background-color:white;}.tic-tac-toe .o, .tic-tac-toe .x {background:white;color:white;z-index:-1;}.tic-tac-toe .o::after, .tic-tac-toe .x::after {color:black;display:block;font-size:10em;position:absolute;width:100%;}
#show_text {order:3;text-align:center;border:2px solid black;width:18.5em;}.wrapper {order:4;display:flex;flex-direction:row;justify-content:center;gap:1em;border:0px solid black;width:18.5em;}.box {text-align:center;}.Spieler {font-size:16pt;}#player1, #player2 {border:0px solid black;text-align:center;}.box #player1 {order:1;}.box #player2 {order:2;}
form {text-align:left;}.colorPlayer {margin-top:2px;}.color-panel-box {order:5;border:0px solid black;text-align:center;margin-top:10px;}#start_button {order:6;border:0px solid black;text-align:center;margin-top:10px;}.footer {order:7;text-align:center;margin-top:10px;}</style><script type="text/javascript">function start(){var xhr=new XMLHttpRequest();
var colorPlayer1,colorPlayer2,player1,player2,colorPanel,string,data,stylesheet,field,pos;player1=document.getElementById("select_1").options[document.getElementById("select_1").selectedIndex].value;player2=document.getElementById("select_2").options[document.getElementById("select_2").selectedIndex].value;if((player1=="Computer")&&(player2=="Computer"))
{document.getElementById("show_text").innerHTML="Computer vs. Computer ist nicht möglich.";}else{colorPlayer1=document.getElementById("color_1").value;colorPlayer1=colorPlayer1.replace("#","");colorPlayer2=document.getElementById("color_2").value;colorPlayer2=colorPlayer2.replace("#","");colorPanel=document.getElementById("color_3").value;
colorPanel=colorPanel.replace("#","");string="/start?p1="+player1+"&p2="+player2+"&cP1="+colorPlayer1+"&cP2="+colorPlayer2+"&cPl="+colorPanel;document.getElementsByName("Player").forEach(element=>{element.disabled=true});document.getElementsByName("color").forEach(element=>{element.disabled=true});document.getElementsByName("fld").forEach(element=>{element.disabled=false});stylesheet=document.styleSheets[0];
stylesheet.insertRule(".tic-tac-toe .x::after{content:\"×\";color:"+document.getElementById("color_1").value+";top:-0.27em;}",stylesheet.cssRules.length);stylesheet.insertRule(".tic-tac-toe .o::after{content:\"○\";color:"+document.getElementById("color_2").value+";top:-0.32em;}",stylesheet.cssRules.length);xhr.open("GET",string,false);xhr.send();
data=xhr.responseText;document.getElementById("show_text").innerHTML=data.substring(data.indexOf("<p>"),data.indexOf("</p>")+"</p>".length);document.getElementById("start_button").innerHTML=data.substring(data.indexOf("<form"),data.indexOf("</form>")+"</form>".length);if(player1=="Computer"){field=data.substring(data.indexOf("<fld>")+"<fld>".length, data.indexOf("</fld>"));
pos=document.getElementById(field);pos.removeChild(pos.childNodes[0]);pos.setAttribute("class","x");pos.innerText="x";}}}function end(){var xhr=new XMLHttpRequest();var data,stylesheet;xhr.open("GET","/end",false);xhr.send();data=xhr.responseText;document.getElementById("show_text").innerHTML="";document.getElementById("t_body").innerHTML="";document.getElementById("start_button").innerHTML="";
document.getElementById("t_body").innerHTML=data.substring(data.indexOf("<tbody>"),data.indexOf("</tbody>")+"</tbody".length);document.getElementById("show_text").innerHTML=data.substring(data.indexOf("<p>"),data.indexOf("</p>")+"</p>".length);document.getElementById("start_button").innerHTML=data.substring(data.lastIndexOf("<form id=\"f_start_button\">"),data.lastIndexOf("</form>")+"</form>".length);
document.getElementsByName("Player").forEach(element=>{element.disabled=false});document.getElementsByName("color").forEach(element=>{element.disabled=false});stylesheet=document.styleSheets[0];stylesheet.deleteRule(stylesheet.cssRules.length-1);stylesheet.deleteRule(stylesheet.cssRules.length-1);}function s_fld(element){var xhr=new XMLHttpRequest();var string,data,field,cur_player_field,comp_field,game_end,field2,pos;string="/s_fld?fld="+element.value;
xhr.open("GET",string,false);xhr.send();data=xhr.responseText;field=document.getElementById(element.value);field.removeChild(field.childNodes[0]);cur_player_field=data.substring(0,1);comp_field=data.substring(1,2);game_end=data.substring(2,3);field.setAttribute("class",cur_player_field);field.innerText=cur_player_field;if((comp_field=="x")||(comp_field=="o")){field2=data.substring(data.indexOf("<fld>")+"<fld>".length,data.indexOf("</fld>"));
pos=document.getElementById(field2);pos.removeChild(pos.childNodes[0]);pos.setAttribute("class",comp_field);pos.innerText=comp_field;}document.getElementById("show_text").innerHTML=data.substring(data.indexOf("<p>"),data.lastIndexOf("</p>")+"</p>".length);}</script></head><body><div class="container" id="body_container"><div class="header"><h1>Tic Tac Toe</h1></div><div class="tic-tac-toe"><table id="t_body"><tbody><tr><td id="fld1"><form>
<button name="fld" type="button" value="fld1" onclick="s_fld(this)" disabled> </button></form></td><td id="fld2"><form><button name="fld" type="button" value="fld2" onclick="s_fld(this)" disabled> </button></form></td><td id="fld3"><form><button name="fld" type="button" value="fld3" onclick="s_fld(this)" disabled> </button></form></td></tr><tr><td id="fld4"><form><button name="fld" type="button" value="fld4" onclick="s_fld(this)" disabled> </button>
</form></td><td id="fld5"><form><button name="fld" type="button" value="fld5" onclick="s_fld(this)" disabled> </button></form></td><td id="fld6"><form><button name="fld" type="button" value="fld6" onclick="s_fld(this)" disabled> </button></form></td></tr><tr><td id="fld7"><form><button name="fld" type="button" value="fld7" onclick="s_fld(this)" disabled> </button></form></td><td id="fld8"><form><button name="fld" type="button" value="fld8" onclick="s_fld(this)" disabled> </button></form>
</td><td id="fld9"><form><button name="fld" type="button" value="fld9" onclick="s_fld(this)" disabled> </button></form></td></tr></tbody></table></div><div id="show_text"><p>&nbsp;</p></div><div class="wrapper"><div class="box" id="player1"><p class="Spieler">X Spieler 1</p><form name="form_player1">Spieler:  <select name="Player"class="combo" id="select_1"><option value="Spieler" selected>Spieler</option><option value="Computer">Computer</option></select><br/>
Farbwahl:  <input type="color" id="color_1" class="colorPlayer" name="color" value="#00ff00"><br/></form></div><div class="box" id="player2"><p class="Spieler">O Spieler 2</p><form name="form_player2">Spieler:  <select name="Player" class="combo" id="select_2"><option value="Spieler">Spieler</option><option value="Computer" selected>Computer</option></select><br/>Farbwahl:  <input type="color" id="color_2" class="colorPlayer" name="color" value="#ff0000"><br/>
</form></div></div><div class="color-panel-box"><form name="form_panel">Farbwahl Spielfeld:  <input type="color" id="color_3" name="color" value="#0000ff" ><br/></form></div><div id="start_button"><form id="f_start_button"><input type="button" value="Spiel starten" onclick="start()"><br/></form></div><div class="footer">Projektarbeit Daniel Wünsch Matr.-Nr. 59527</div></div></body></html>)rawliteral";

void register_web_server_methods();
void set_wifi_params();


#endif