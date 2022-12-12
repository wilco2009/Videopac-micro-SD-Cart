bool begin_data;

void parse_header_string(char* s){

char token[16];
char value[100];
int i;

  s = trimleft(s);
  upStr(s);
  i = indexOf('=', s);
  if ((i >= 0) && (i < 15)){   
    strmid(token, s, 0, i);    
//    s[i+30]=0;
    strmid(value, s, i+1, strlen(s)-i-1);
    trimright(value);
    if (strcmp(token, "ADDRESS")==0){
        sscanf(value, "%d", &RAM_pos);
    } else
    if (strcmp(token, "SIZE")==0){
        sscanf(value, "%d", &game_size);
    } else
    if (strcmp(token, "NAME")==0){
      strcpy(file_name, value);
      
    } else
    if (strcmp(token, "PAGGING")==0){
        game_pagging = string2pagging(value);
        Serial.println(game_pagging);
    }
  }
}

void read_header(void){
  const unsigned long int INITIAL_TIMER = 20000;
  const unsigned long int READING_TIMER = 100;
  unsigned long int serial_timer = 0;
  unsigned long int inicio = 0;
  unsigned long int bytes_readed = 0;
  inicio = millis();
  while (serial_timer < INITIAL_TIMER){
    serial_timer = millis()-inicio;
    if (Serial1.available() > 0) {
      break;
    }
  }
  if (serial_timer < INITIAL_TIMER){
    inicio = millis();
    serial_timer = 0;
    while (serial_timer < READING_TIMER){
      if (Serial1.available() > 0) {

        bytes_readed = Serial1.readBytesUntil(13,str1,100);
        str1[bytes_readed]=0;
        if (bytes_readed > 1) {
          parse_header_string(str1);
        }
        inicio = millis();
      }
      serial_timer = millis()-inicio;
    }
  } else {
  }
}

void receivefile(unsigned long int baudios){
  const unsigned long int INITIAL_TIMER = 1500;
  const unsigned long int READING_TIMER = 200;
  unsigned long int serial_timer = 0;
  unsigned long int inicio = 0;
  unsigned long int bytes_readed = 0;
  byte incomingByte;
//  int bytes_written = 0;
  int page1k;
  int offset1k;
  
  Serial1.begin(baudios);

  sprintf_P(str1, PSTR("Reading %lu bps"), baudios);
  show_message(str1);

  read_header();
  switch (game_pagging) {
    case PAG_P10_P11:
    case PAG_SELECT_GAME:
      show_transfer_status(game_size, 8192-game_size, file_name, game_pagging, 0);
      break;
    case PAG_VP_PLUS:
      show_transfer_status(game_size, 16384-game_size, file_name, game_pagging, 0);
      break;
    case PAG_SOREN:
      show_transfer_status(game_size, 1024, file_name, game_pagging, 0);
      break;
  }
  int k = 0;
  set_mode(MODE_SENDING_GAME, game_pagging);
  inicio = millis();
  while (serial_timer < INITIAL_TIMER){
    serial_timer = millis()-inicio;
    if (Serial1.available() > 0) {
      break;
    }
  }
  switch (game_pagging){
    case PAG_P10_P11:
    case PAG_SELECT_GAME:

      for (unsigned int i=0;i<(game_size/1024);i++){
        for (int j=0; j<1024;j++){
          inicio = millis();
          while (Serial1.available() <= 0) {
            if (millis()-inicio > READING_TIMER) {
              sprintf_P(str1, PSTR("read error (%d)"), k);
              show_message(str1);
              delay(1500);
              return;
            }
          }
          incomingByte = Serial1.read();
          k++;
          RAM_write(8192-game_size+1024*i+j, incomingByte);
        }
      }
      RAM_pos = 8192;
      break;
    case PAG_VP_PLUS:
      if (game_size==16384){
        for (unsigned int i=0;i<16;i++){
          for (int j=0; j<1024;j++){
            inicio = millis();
            while (Serial1.available() <= 0) {
              if (millis()-inicio > READING_TIMER) {
                sprintf_P(str1, PSTR("read error (%d)"), k);
                show_message(str1);
                delay(1500);
                return;
              }
            }
            k++;
            incomingByte = Serial1.read();
            RAM_write(1024*i+j, incomingByte);
          }
        }
      } else {
        for (unsigned int i=0;i<12;i++){
          for (int j=0; j<1024;j++){
            inicio = millis();
            while (Serial1.available() <= 0) {
              if (millis()-inicio > READING_TIMER) {
                sprintf_P(str1, PSTR("read error (%d)"), k);
                show_message(str1);
                delay(1500);
                return;
              }
            }
            incomingByte = Serial1.read();
            k++;
            RAM_write(1024*i+j+4096, incomingByte);
          }
        }
      }
      RAM_pos = 16384;
      break;
    case PAG_SOREN:
      for (int j=0; j<3072;j++){
        inicio = millis();
        while (Serial1.available() <= 0) {
          if (millis()-inicio > READING_TIMER) {
            sprintf_P(str1, PSTR("read error (%d)"), k);
            show_message(str1);
            delay(1500);
            return;
          }
        }
        incomingByte = Serial1.read();
        k++;
        RAM_write(j+1024, incomingByte);
      }

      for (int j=0; j<3072;j++){
        inicio = millis();
        while (Serial1.available() <= 0) {
          if (millis()-inicio > READING_TIMER) {
            sprintf_P(str1, PSTR("read error (%d)"), k);
            show_message(str1);
            delay(1500);
            return;
          }
        }
        incomingByte = Serial1.read();
        k++;
        RAM_write(j+1024+4096, incomingByte);
      }

      for (int j=0; j<3072;j++){
        inicio = millis();
        while (Serial1.available() <= 0) {
          if (millis()-inicio > READING_TIMER) {
            sprintf_P(str1, PSTR("read error (%d)"), k);
            show_message(str1);
            delay(1500);
            return;
          }
        }
        incomingByte = Serial1.read();
        k++;
        RAM_write(j+1024+8192, incomingByte);
      }
      RAM_pos = 16384;
    break;
  }

  Serial1.end();
  ram_led_off();
  show_transfer_status(bytes_readed, RAM_pos, file_name, game_pagging, 500);
  set_mode(MODE_PLAYING, game_pagging);
  
  show_ready_to_play();
  sonido_select_game();
  delay(1500);
}
