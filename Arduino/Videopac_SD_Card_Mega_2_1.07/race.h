#define STEP_TI 10
#define road_w 80

unsigned long int race_step_time = 0;
unsigned long int ti_mem = 0;

int score_race = 0;
int ti_race = 0;
byte minutes_race = 2;
byte seconds_race = 00;
bool choque = false;
bool acelerando = false;

unsigned long int ti_choque = 0;
unsigned long int ti_acelerando = 0;


int x_car = 10;
int y_car = 60;

int dir_enemy[2] = {1, -1};

int x_enemy[2] = {10, 30};
int y_enemy[2] = {8, -20};

int car_speed = 3;

void draw_explosion(int x, int y){
  u8g2.drawXBMP(x, y-4, 8, 8, explosion_img);
}

void draw_car(int x, int y){
  if (x >= 100) return;

  u8g2.drawXBMP(x, y-4, 8, 8, car_img);
  
//  u8g2.setDrawColor(1);
//  u8g2.drawBox(x+1,y-1,6,1);
//  u8g2.drawBox(x,y-3,8,2);
//  u8g2.drawBox(x+2,y-8,4,5);
//  u8g2.drawBox(x+1,y-7,6,2);  
//  u8g2.setDrawColor(2);
//  u8g2.drawBox(x+3,y-3,2,2);  
//  u8g2.setDrawColor(1);
}

void race_display_screen(){
  int fase = 0;
  int road_speed = 10;
  // display road
  u8g2.clearBuffer();          // clear the internal memory

  if (choque){
    fase = 0;
  } else if (acelerando) {
    if (ti_acelerando-millis() > 500)
      fase = millis() % (3*road_speed*10) / road_speed/10;
    else if (ti_acelerando-millis()> 0)
      fase = millis() % (3*road_speed*5) / road_speed/5;
  } else
      fase = millis() % (3*road_speed) / road_speed;
  switch (fase) {
    case 0:
      u8g2.drawVLine(0,0,10);
      u8g2.drawVLine(road_w,0,10);
      u8g2.drawVLine(0,15,20);
      u8g2.drawVLine(road_w,15,20);
      u8g2.drawVLine(0,40,20);
      u8g2.drawVLine(road_w,40,20);
      break;
    case 1:
      u8g2.drawVLine(0,0,20);
      u8g2.drawVLine(road_w,0,20);
      u8g2.drawVLine(0,25,20);
      u8g2.drawVLine(road_w,25,20);
      u8g2.drawVLine(0,50,10);
      u8g2.drawVLine(road_w,50,10);
      break;
    case 2:
      u8g2.drawVLine(0,10,20);
      u8g2.drawVLine(80,10,20);
      u8g2.drawVLine(0,35,20);
      u8g2.drawVLine(80,35,20);
      u8g2.drawVLine(0,60,5);
      u8g2.drawVLine(80,60,5);
      break;
  }

  draw_car(x_car, y_car);
  for (int i=0; i < 2; i++){
    draw_car(x_enemy[i], y_enemy[i]);
    if (((abs(x_enemy[i]-x_car) < 8) && (abs(y_enemy[i]-y_car)<8)) && !choque){
    if (minigame_sound)
      noTone(SPEAKER_PIN);      
      choque = true;
      ti_choque = millis()+1000;
    }
  }

  if (choque) {
    draw_explosion(x_car, y_car);
    if (minigame_sound) {
      if (ti_choque-millis() > 500)
        explosion();
      else
        noTone(SPEAKER_PIN);
    }
  }

  if ((millis() > ti_choque) && choque) {
    choque = false;
    acelerando = true;
    ti_acelerando = millis()+1000;
  }

  if (millis() > ti_acelerando) {
    acelerando = false;
  }

  draw_number(road_w+10, 40, score_race, 4);
  draw_time(road_w+10, 20, minutes_race, seconds_race);

  u8g2.sendBuffer();
}

void race_manage_controls(){


  if (!choque) {
    if (!acelerando){
      car_speed = 3;
      if (minigame_sound) 
        tone(SPEAKER_PIN, 80);
    } else if ((ti_acelerando-millis()) > 500){
      car_speed = 1;
      if (minigame_sound) 
        tone(SPEAKER_PIN, 60);
    } else if ((ti_acelerando-millis()) > 0){
      car_speed = 2;
      if (minigame_sound) 
        tone(SPEAKER_PIN, 40);
    }
  
    if ((digitalRead(butLEFT)==LOW) && (x_car > 1)) x_car-=5;
    if ((digitalRead(butRIGHT)==LOW) && (x_car < (road_w-10))) x_car+=5;  
  } 

  if (millis()-race_step_time > STEP_TI) {
    for (int i=0; i < 2; i++){
      if ((x_enemy[i] >= 100) || (!choque && (y_enemy[i] >= 63)) || (choque && y_enemy[i] <= 0) ) {
        if (choque)
          y_enemy[i] = 65;
        else
          y_enemy[i] = 8;
        x_enemy[i] = rand() % (road_w-10)-car_speed+3;
        dir_enemy[i] = rand() % 2;
        if (dir_enemy[i] == 0) dir_enemy[i]=-1;
      }
      x_enemy[i]+= dir_enemy[i]*car_speed;
      if (choque)
        y_enemy[i]-= car_speed;
      else 
        y_enemy[i]+= car_speed;
      if ((x_enemy[i] < 0)|| (x_enemy[i] >= (road_w-10))) dir_enemy[i]=-dir_enemy[i];
      race_step_time = millis();
    }
  }

  if ((millis()-ti_mem)>= 100) {
    if (!choque) score_race++;
    ti_race++;
    ti_mem = millis();
    if ((ti_race % 10) == 0) {
      seconds_race--;
    }
    if (seconds_race == 255) {
      seconds_race = 59;
      minutes_race--;
    }
  }
}

void race_main(){
  do {
    dir_enemy[0] = 1;
    dir_enemy[1] = -1;
    x_enemy[0] = 10;
    x_enemy[1] = 30;
    y_enemy[0] = 8;
    y_enemy[1] = -20;

    fin = false;
    score_race = 0;
    ti_race = 0;
    ti_mem = 0;
    seconds_race = 0;
    minutes_race = 2;
    race_display_screen();
    if (minigame_sound)
      sonido_select_game_2();
    choque = false;
    delay(1000);
    acelerando = true;
    ti_acelerando = millis()+1000;
    race_step_time = millis();
    do {
      race_display_screen();
      race_manage_controls();
      if ((minutes_race==0) && (seconds_race==0)) fin = true;
      if ((digitalRead(butESC)==LOW) && minigame_cfg()) {
        race_display_screen();
        fin = true;
      }
    } while (!fin);
    race_display_screen();
    if (minigame_sound) {
      noTone(SPEAKER_PIN);
    }
    u8g2.drawStr(30,35,str_GAMEOVER);
    u8g2.sendBuffer(); 
    delay(500);
    while ((digitalRead(butESC)==HIGH) && (digitalRead(butENTER)==HIGH));
  } while (digitalRead(butESC)==HIGH);  
  while((digitalRead(butENTER)==LOW) || (digitalRead(butESC)==LOW));
  
}
