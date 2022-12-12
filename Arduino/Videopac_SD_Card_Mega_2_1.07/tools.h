#define digit_w 3
#define digit_h 3

void draw_digit(byte x, byte y, byte digit){
  byte digits [10] = {
      0b00111111,   // cero
      0b00000110,   // uno
      0b01011011,   // dos
      0b01001111,   // tres
      0b01100110,   // cuatro
      0b01101101,   // cinco
      0b01111101,   // seis
      0b00000111,   // siete
      0b01111111,   // ocho
      0b01101111    // nueve
  };
  byte v = digits[digit];
  if (v & 1)
    u8g2.drawHLine(x,y,digit_w);
  if (v & 2)
    u8g2.drawVLine(x+digit_w,y,digit_h);
  if (v & 4)
    u8g2.drawVLine(x+digit_w,y+digit_h+1,digit_h);
  if (v & 8)
    u8g2.drawHLine(x,y+digit_h*2,digit_w);
  if (v & 16)
    u8g2.drawVLine(x,y+digit_h+1,digit_h);
  if (v & 32)
    u8g2.drawVLine(x,y,digit_h);
  if (v & 64)
    u8g2.drawHLine(x,y+digit_h,digit_w+1);
  
}

void printVolt(byte x, byte y){
  if (showVolt) {
    float voltaje_entrada;
    float voltaje_final;
    float resistencia1 = 100000; //Resistencia de 100K
    float resistencia2 = 10000; //Resistencia de 10k
    voltaje_entrada = (analogRead(A15) * 2.56) / 1024;  //Lee el voltaje de entrada
    voltaje_final = voltaje_entrada / (resistencia2 / (resistencia1 + resistencia2));
    dtostrf(voltaje_final, 6, 4, str1);
    u8g2.setCursor(x, y);
    u8g2.print(str1);
  }
}

void draw_number(byte x, byte y, int number, byte digits){
  byte digit = 0;
  byte i;
  int d = 1;
  for (i=1; i<digits;i++) d *=10;
  for (i=0; i< digits; i++){
    digit = number / d;
    draw_digit(x,y,digit);
    x+=digit_w+2;
    number = number % d;
    d /=10;
    
  }
  
}

void draw_time(byte x, byte y, byte minutes, byte seconds) {
  draw_number(x, y, minutes, 2);
  u8g2.drawBox(x+11,y+digit_h/2, 2, 2);
  u8g2.drawBox(x+11,y+digit_h*3/2, 2, 2);
  draw_number(x+15, y, seconds, 2);
}

static const unsigned char chartable [128]PROGMEM = 
  { 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, // 0..9
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, // 10..19
    0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, 0x3F, // 20..29
    0x3F, 0x3F, 0x0C, 0x3F, 0x3F, 0x3F, 0x0B, 0x3E, 0x10, 0x3F, // 30..39
    0x2E, 0x3B, 0x29, 0x10, 0x27, 0x28, 0x27, 0x2A, 0x00, 0x01, // 40..49 
    0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08, 0x09, 0x0A, 0x0A, // 50..59
    0x3F, 0x2B, 0x3F, 0x0D, 0x3F, 0x20, 0x25, 0x23, 0x1A, 0x12, // 60..69
    0x1B, 0x1C, 0x1d, 0x16, 0x1E, 0x1F, 0x0E, 0x26, 0x2D, 0x17, // 70..79
    0x0F, 0x18, 0x13, 0x19, 0x14, 0x15, 0x24, 0x11, 0x22, 0x2C, // 80..89
    0x21, 0x3F, 0x3B, 0x3F, 0x3F, 0x28, 0x3F, 0x20, 0x25, 0x23, // 90..99
    0x1A, 0x12, 0x1B, 0x1C, 0x1d, 0x16, 0x1E, 0x1F, 0x0E, 0x26, // 100..109
    0x2D, 0x17, 0x0F, 0x18, 0x13, 0x19, 0x14, 0x15, 0x24, 0x11, // 110..119
    0x22, 0x2C, 0x21, 0x2E, 0x2E, 0x3B, 0x3F, 0x3F};            // 120..127
    
char ASCII_to_VP(char c){
   if (c <128) {
      return pgm_read_byte_near(chartable + c);
   } else {
      return 0x3F;
   }
  
}

void convert_ascii_file_to_VP(char* dest, char* source){
  dest[0]=ASCII_to_VP(' ');
  for (int i=1; i<16; i++){
    if (i-1 < strlen(source))
      dest[i]=ASCII_to_VP(source[i-1]);
    else
      dest[i] = ASCII_to_VP(' ');
  }
}

void dump_block(void){
  for (int j=0; j<256; j++){
    sprintf_P(str1, PSTR("%02X "), block[j]);
    Serial.print(str1);
    if ((j % 16)==15) Serial.println();
  }
  Serial.println();
}

void waitforever(void){
  while(1);
}

void waitkey(void){
  while((digitalRead(butENTER)==HIGH) && (digitalRead(butESC)==HIGH));
  while((digitalRead(butENTER)==LOW) || (digitalRead(butESC)==LOW));
}

void waitNoKey(void){
  while((digitalRead(butENTER)==LOW) || (digitalRead(butESC)==LOW));
}

void sd_led_on(void){
  digitalWrite(LED_SD, LOW);
}

void sd_led_off(void){
  digitalWrite(LED_SD, HIGH);
}

void ram_led_on(void){
  digitalWrite(LED_RAM, LOW);
}

void ram_led_off(void){
  digitalWrite(LED_RAM, HIGH);
}

void explosion(){
  tone(SPEAKER_PIN, random(10, 200));   // change the parameters of random() for different sound
}

void rebote(){
  tone(SPEAKER_PIN, 250, 83);
//  delay(90);
//  noTone(SPEAKER_PIN);
}

void raquetazo(){
  tone(SPEAKER_PIN, 200, 83);
//  delay(90);
//  noTone(SPEAKER_PIN);
}

void sonido_punto(){
  tone(SPEAKER_PIN, 85, 180);
//  delay(180);
//  noTone(SPEAKER_PIN);
}

void sonido_select_game(){
  int melody[] = {82.407,164.01,329.66,659.26,1975.5};

  for (int thisNote = 0; thisNote < 7; thisNote++) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote], 83);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
//    int pauseBetweenNotes = noteDuration * 1.30;
    delay(90);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }
}
void sonido_select_game_2(){
  int melody[] = {82.407,164.01,329.66,659.26,1975.5};

  for (int thisNote = 6; thisNote >=0; thisNote--) {
    // to calculate the note duration, take one second divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
//    int noteDuration = 1000 / noteDurations[thisNote];
    tone(SPEAKER_PIN, melody[thisNote], 83);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
//    int pauseBetweenNotes = noteDuration * 1.30;
    delay(90);
    // stop the tone playing:
    noTone(SPEAKER_PIN);
  }
}

void click(){
    tone(SPEAKER_PIN, 500, 83);
    delay(10);
    noTone(SPEAKER_PIN);
 }

char *trimwhitespace(char *str)
{
  char *end;

  // Trim leading space
  while(isspace((unsigned char)*str)) str++;

  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && isspace((unsigned char)*end)) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;
}

void upStr(char* str){
  for (int i=0; i<strlen(str);i++){
    str[i]=toupper(str[i]);
  }
}

char *trimleft(char *str)
{
  int i = 0;
  int j = 0;
  // Trim leading space
  while((str[i]==' ') || (str[i]==13)|| (str[i]==10)) i++;
  while(str[i]!=0) {
    str[j]=str[i];
    i++;
    j++;
  }
  str[j] = 0;

  return str;
}

char *trimright(char *str)
{
  char *end;
  if(*str == 0)  // All spaces?
    return str;

  // Trim trailing space
  end = str + strlen(str) - 1;
  while(end > str && ((end[0]==' ')||(end[0]==13)||(end[0]==10))) end--;

  // Write new null terminator character
  end[1] = '\0';

  return str;  
}

char indexOf(char c, char* str){
  int i;
  for (i=0; str[i]!=0; i++){
    if (str[i]==c)
      return i;
  }
  return -1;
}

void strmid(char* dest, char* source, int st, int len){
  for (int i=0; i < len; i++){
    dest[i] = source[st+i];
  }
  dest[len]='\0';
}

byte string2pagging(char* s){
  if (strcmp(s, "P10/P11")==0) return PAG_P10_P11;
  if (strcmp(s, "VP+")==0) return PAG_VP_PLUS;
  if (strcmp(s, "VPPLUS")==0) return PAG_VP_PLUS;
  if (strstr(s, "SOREN")!=0) return PAG_SOREN;
  if (strstr(s, "SOEREN")!=0) return PAG_SOREN;
  if (strcmp(s, "SELECT GAME")==0) return PAG_SELECT_GAME;
  if (strcmp(s, "XROM")==0) return PAG_XROM;
  return -1;
}

void pagging2str(byte game_pagging, char* str2){
  switch (game_pagging) {
    case PAG_P10_P11: 
      strcpy(str2,"P10/P11");
      break;
    case PAG_VP_PLUS:
      strcpy(str2,"VP+");
      break;
    case PAG_SOREN:
      strcpy(str2,"A10(SOEREN)");
      break;
    case PAG_SELECT_GAME:
      strcpy(str2,"SELECT FILE");
      break;
    case PAG_XROM:
      strcpy(str2,"XROM");
      break;
    default:
      strcpy(str2,"P10/P11");          
  }
}

void rotate_str(char* dest, char* source, int maxlen, bool isfilename, int *ch_ini, long int *inicio){
  char stmp[MAX_FILENAME_LEN];
  long int ti;
  if (source[0]=='\0'){
    dest[0] = '\0';
    return;
  }
  if ((*ch_ini) == 0) ti = 2000;
  else ti = 500;
  if ((millis()-(*inicio))>ti) {
    (*inicio) = millis();
    (*ch_ini)++;
  }
  if (((*ch_ini)+maxlen) >= strlen(source)) {
    (*ch_ini) = 0;
  }
  if (isfilename & (source[0]=='+')) {
    strcpy(dest,"<");  
    strmid(stmp,source,(*ch_ini)+1,maxlen-2);
    strcat(dest,stmp);
    strcat(dest,">");
  } else {
    strmid(dest,source,*ch_ini,maxlen);
  }
}

void show_select_game(boolean sound){
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.drawXBMP(21, 25, 86, 7, selectgame);
  u8g2.sendBuffer(); // transfer internal memory to the display   
  if (sound){
    sonido_select_game();
    delay(500);
  }
}

void show_logo(){
  u8g2.clearBuffer();          // clear the internal memory
#ifdef ATARI
  u8g2.drawXBMP(0, 0, 128, 64, ATARI_LOGO);
  u8g2.setFont(u8g2_font_profont12_mf); // choose a suitable font
  u8g2.drawStr(0,15,strVER);
#endif
#ifdef VIDEOPAC
  u8g2.drawXBMP(0, 0, 128, 64, LOGO);
  u8g2.setFont(u8g2_font_profont12_mf); // choose a suitable font
  u8g2.drawStr(2,45,strVER);
#endif
  u8g2.sendBuffer(); // transfer internal memory to the display   
  
  delay(1000);
}


void show_message(char* s){
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
  u8g2.drawStr((128-u8g2.getStrWidth(s))/2,35,s);
  u8g2.sendBuffer(); // transfer internal memory to the display 
}

void show_ready_to_play(void){
//  int dato = PINA; 
//  sprintf(str1,"%d",dato);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_profont12_mf); // choose a suitable font
  u8g2.drawStr(6,31,"PRESS RESET TO PLAY");
//  u8g2.drawStr(15,48,str1);  
  u8g2.sendBuffer(); // transfer internal memory to the display   
}

void show_transfer_status(int bytes, int RAM_pos, char* filename, byte pagemode, int millisec){
  unsigned long int stimer;
  unsigned long int inicio;
  unsigned long int ini;
  int ch_ini = 0;
  
  inicio = millis();
  ini = millis();
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_profont12_mf); // choose a suitable font
  rotate_str(str1, filename, 16, true, &ch_ini, ini);
//  strmid(str1, filename, 
  sprintf_P(str2, PSTR("NAME:%s"), str1);
  u8g2.drawStr(0,15,str2);
  sprintf_P(str1, PSTR("ADDR:%d"), RAM_pos);
  u8g2.drawStr(0,30,str1);
  pagging2str(game_pagging, str2);
  sprintf_P(str1, PSTR("PAGG:%s"), str2);
  u8g2.drawStr(0,45,str1);
  if (bytes < 0)
    strcpy(str1, "SIZE: UNKNOWN");
  else
    sprintf_P(str1, PSTR("SIZE:%d"), bytes);
  u8g2.drawStr(0,59,str1);
  u8g2.sendBuffer(); // transfer internal memory to the display   
  do {
    stimer = millis()-inicio;
  } while ((digitalRead(butENTER)==HIGH)&&(digitalRead(butESC)==HIGH)&&(stimer < millisec));
}

void remove_last_dir(char* dir_name){
  int i = strlen(dir_name)-1;
  while (dir_name[i] != '/'){
    i--;
  }
  dir_name[i] = '\0';
}

void save_initial_dir(void){
  for (int i=0;i<MAXDIR;i++){
    EEPROM.write(i, initial_dir[i]);
  }    
}

void save_autoload_file(void){
  for (int i=0;i<MAX_FILENAME_LEN;i++){
    EEPROM.write(MAXDIR+1+i, autoload_file[i]);
  }    
}

void save_show_logo(void){
  EEPROM.write(MAXDIR+MAX_FILENAME_LEN+2, to_show_logo);
}

void save_baudrate(void){
  EEPROM.put(MAXDIR+MAX_FILENAME_LEN+3, baudrate);
}

void save_sorted(void){
  EEPROM.put(MAXDIR+MAX_FILENAME_LEN+4, sorted);
}
void save_autorebuild(void){
  EEPROM.put(MAXDIR+MAX_FILENAME_LEN+5, autorebuild);
}

void save_RAM_delay(void){
  EEPROM.put(MAXDIR+MAX_FILENAME_LEN+6, RAM_delay);
}

void load_initial_dir(void){
  for (int i=0;i<MAXDIR;i++){
    initial_dir[i] = EEPROM.read(i);
  }    
}

void load_autoload_file(void){
  for (int i=0;i<MAX_FILENAME_LEN;i++){
    autoload_file[i] = EEPROM.read(MAXDIR+1+i);
  }    
}

void load_show_logo(void){
  to_show_logo = EEPROM.read(MAXDIR+MAX_FILENAME_LEN+2);
}

void load_baudrate(void){
  EEPROM.get(MAXDIR+MAX_FILENAME_LEN+3, baudrate);
}

void load_sorted(void){
  EEPROM.get(MAXDIR+MAX_FILENAME_LEN+4, sorted);
}

void load_autorebuild(void){
  EEPROM.get(MAXDIR+MAX_FILENAME_LEN+5, autorebuild);
}
void load_RAM_delay(void){
  EEPROM.get(MAXDIR+MAX_FILENAME_LEN+6, RAM_delay);
}

bool minigame_cfg(){
  noTone(SPEAKER_PIN);
  while (digitalRead(butESC)==LOW);
  int option = 0;
  while (1) {
    if (digitalRead(butRIGHT)==LOW){
      delay(200);
      option++;
      if (option > 1) option = 0;
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      option--;
      if (option <0) option = 1;
    }

    if (digitalRead(butENTER)==LOW){
      delay(100);
      switch (option) {
        case 0:
          minigame_sound = !minigame_sound;
          break;
        case 1: 
          return true;
          break;
        default:
          break;
      }
    }
    if (digitalRead(butESC)==LOW){
      delay(100);
      while (digitalRead(butESC)==LOW);
      return false;
    }
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font

    if (minigame_sound)
      u8g2.drawStr(1,30,"ON");
    else
      u8g2.drawStr(1,30,"OFF");
      
    if (option == 0) {
      u8g2.drawStr(1,15,"SOUND");
      u8g2.setDrawColor(2);
      u8g2.drawBox(0,3,31,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(1,15,"SOUND");
      u8g2.setDrawColor(1);
    }
    if (option == 1) {
      u8g2.drawStr(37,15,"QUIT");
      u8g2.setDrawColor(2);
      u8g2.drawBox(36,3,25,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(37,15,"QUIT");
      u8g2.setDrawColor(1);
    }
    
    u8g2.sendBuffer(); // transfer internal memory to the display 
  }
}
