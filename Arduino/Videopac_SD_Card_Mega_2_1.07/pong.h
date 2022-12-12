#define h_pad 10
#define x_pad 80
#define ti_sacando 2000

boolean fin = false;
int score1 = 0;
int y_pad = 15;
int x_ball = 90;
int y_ball = 15;
byte dx_ball = 3;
byte dy_ball = 3;
short int dir_x = -1;
short int dir_y = -1;
unsigned long int sacando = 0;


void pong_display_screen(){
  u8g2.clearBuffer();          // clear the internal memory

  // draw field
  u8g2.drawHLine(0,0,90);
  u8g2.drawHLine(0,63,90);
  u8g2.drawVLine(0,0,63);

  // draw score
  draw_number(95, 0, score1, 2);

  // draw pads

  u8g2.drawVLine(x_pad, y_pad, h_pad);
  u8g2.drawVLine(x_pad+1, y_pad, h_pad);

  // draw ball
//  if ((millis() - sacando) > ti_sacando)
    u8g2.drawBox(x_ball,y_ball,2,2);  
  
  u8g2.sendBuffer(); // transfer internal memory to the display  
}
void pong_manage_controls(){
  if (score1 == 15) fin = true;
  if ((digitalRead(butESC)==LOW) && minigame_cfg()) {
    pong_display_screen();
    fin = true;
  }
  if ((digitalRead(butUP)==LOW) && (y_pad > 1)) y_pad-=3;
  if ((digitalRead(butDOWN)==LOW) && (y_pad <(63-h_pad))) y_pad+=3;

  if ((millis() - sacando) > ti_sacando) {
    x_ball+=dx_ball*dir_x;
    y_ball+=dy_ball*dir_y;
  
    if (x_ball < 1) {
      x_ball = 1;
      dir_x = -dir_x;
      if (minigame_sound)
        rebote();
    }
  
    if (x_ball > 90) { // punto
      x_ball = 90;
      dir_x = -dir_x;
      score1++;
      if (minigame_sound)
        sonido_punto();
      y_ball = rand() % 60 +1;
      sacando = millis();
    }
  
    if (y_ball < 0) {
      y_ball = 1;
      if (minigame_sound)
        rebote();
      dir_y = -dir_y;
    }
    if (y_ball > 61) {
      y_ball = 61;
      dir_y = -dir_y;
      if (minigame_sound)
        rebote();
    }
  
  
    if ((x_ball <= x_pad) && ((x_ball+dx_ball*dir_x)>=x_pad) && (y_ball >= y_pad) && (y_ball <= y_pad + h_pad)) {
      dir_x = -dir_x;    
      if (minigame_sound)
        raquetazo();
    }
  }

}

void pong_main(){
  do {
    fin = false;
    score1 = 0;
    y_pad = 15;
    x_ball = 90;
    y_ball = 15;
    dx_ball = 3;
    dy_ball = 3;
    dir_x = -1;
    dir_y = -1;
    pong_display_screen();
    if (minigame_sound)
      sonido_select_game_2();
    delay(1000);
    sacando = millis();
    do {
      pong_display_screen();
      pong_manage_controls();
    } while (!fin);
  
    u8g2.drawStr(30,35,str_GAMEOVER);
    u8g2.sendBuffer(); 
    delay(500);
    while ((digitalRead(butESC)==HIGH) && (digitalRead(butENTER)==HIGH));
  } while (digitalRead(butESC)==HIGH);  
  while((digitalRead(butENTER)==LOW) || (digitalRead(butESC)==LOW));
  
}
