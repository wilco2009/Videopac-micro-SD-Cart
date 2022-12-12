#define NUM_SCRLINES 5

char scr_lines[NUM_SCRLINES][MAX_FILENAME_LEN];

int file_selected = 0;

void read_screen(int index, int selected){
  cache.seekSet((MAX_FILENAME_LEN)*index);
  byte i = 0;
  while (i < NUM_SCRLINES) {
     if (cache.read(scr_lines[i],MAX_FILENAME_LEN)<=0){
        scr_lines[i][0] = '\0';
     }
    i++;
  }
  cache.clearError();
}

void show_file_screen(int index, int selected){
  ti = 5000;
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
  for (byte i=0; i<NUM_SCRLINES;i++){
      if (i==(selected-index)) {
//        Serial.print("ch_ini: ")
//        Serial.print(ch_ini);
//        Serial.print("-- inicio: ");
//        Serial.println(inicio);
        rotate_str(str1, scr_lines[i], 21, true, &ch_ini, &inicio);
        
        u8g2.drawStr(1,(i+1)*12-1,str1);
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,i*12,127,12);
        u8g2.setDrawColor(1);
      } else {
          if (scr_lines[i][0]=='+') {
            strcpy(str1,"<");  
            strmid(str2,scr_lines[i],1,19);
            strcat(str1,str2);
            strcat(str1,">");
          } else {
            strmid(str1,scr_lines[i],0,21);
         }
         u8g2.drawStr(1,(i+1)*12-1,str1);
        u8g2.setDrawColor(1);
      }
    
  }
  u8g2.sendBuffer(); // transfer internal memory to the display   
}

void show_screen_desc(int index, int selected){
//  openDirectory(&dirFile, dir_name);
  ti = 5000;
  inicio = millis();
  while (digitalRead(butENTER)==LOW){
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    for (byte i=0; i<NUM_SCRLINES;i++){
      unsigned long int CRC32 = CalcCRC32(scr_lines[i]);
      if (scr_lines[i][0]!='+'){
        if (scr_lines[i][0]!='\0'){
          get_game_data(CRC32);
//          Serial.print(CRC32);
//          Serial.print(F("-"));
//          Serial.println(game_name);
        } else game_name[0] = '\0';
      } else strcpy(game_name, scr_lines[i]);
//      Serial.print(CRC32);
//      Serial.print(F(":"));
//      Serial.println(game_name);
      if (i==(selected-index)) {
        if (scr_lines[i][0]=='+') 
          rotate_str(str1, scr_lines[i], 21, true, &ch_ini, &inicio);
        else
          rotate_str(str1, game_name, 21, true, &ch_ini, &inicio);
        u8g2.drawStr(1,(i+1)*12-1,str1);
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,i*12,127,12);
        u8g2.setDrawColor(1);
      } else {
          if (scr_lines[i][0]=='+') {
            strcpy(str1,"<");  
            strmid(str2,scr_lines[i],1,19);
            strcat(str1,str2);
            strcat(str1,">");
          } else {
            strmid(str1,game_name,0,21);
         }
         u8g2.drawStr(1,(i+1)*12-1,str1);
        u8g2.setDrawColor(1);
      }
    }
    u8g2.sendBuffer(); // transfer internal memory to the display  
  }
//  dirFile.close(); 
}

void show_info(char* file_name){
  static int ch_ini = 0;
  static long int inicio;
  static int ch_ini_c = 0;
  long int inicio_c;
  unsigned long int CRC32 = CalcCRC32(file_name);
  int screen = 0;
//  read_ini_file(CRC32);
  get_game_data(CRC32);
  while(1){
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    if (screen==0){
      if ((strlen(file_name)==0) || (file_name[0]=='+'))
        u8g2.drawStr(0,15,"NO FILE SELECTED");
      else {
        rotate_str(str1, file_name, 15, true, &ch_ini, &inicio);
        u8g2.drawStr(0,15,"FIL: ");
        u8g2.drawStr(30,15,str1);
        sprintf_P(str1, PSTR("CRC: %08lX"), CRC32);
        u8g2.drawStr(0,30,str1);
        sprintf_P(str1, PSTR("SIZE: %d"), file.fileSize());
        u8g2.drawStr(0,45,str1);
      }
    } else  if (screen==1){
        rotate_str(str1, game_name, 15, true, &ch_ini, &inicio);
        u8g2.drawStr(0,15,"GAME:");
        u8g2.drawStr(30,15,str1);
        rotate_str(str1, game_brand, 15, true, &ch_ini_c, &inicio_c);
        u8g2.drawStr(0,30,"COMP:");
        u8g2.drawStr(30,30,str1); 
        u8g2.drawStr(0,45,"YEAR:");
        u8g2.drawStr(30,45,game_year);
    } else {
        rotate_str(str1, game_variant, 12, true, &ch_ini, &inicio);
        u8g2.drawStr(0,15,"VARIANT:");
        u8g2.drawStr(54,15,str1);
        pagging2str(game_pagging, str2);
        rotate_str(str1, str2, 12, true, &ch_ini_c, &inicio_c);
        u8g2.drawStr(0,30,"PAGGING:");
        u8g2.drawStr(54,30,str1); 
    }
    u8g2.drawStr(0,63,"ESC=EXIT ENTER=MORE");
    u8g2.sendBuffer(); // transfer internal memory to the display   
    if (digitalRead(butESC)==LOW) {
      while(digitalRead(butESC)==LOW);    
      return;    
    }
    if ((digitalRead(butENTER)==LOW) || (digitalRead(butRIGHT)==LOW)) {
      delay(200);
      screen++;
      if (screen>2) screen = 0;
    } else if (digitalRead(butLEFT)==LOW) {
      delay(200);
      screen--;
      if (screen<0) screen = 2;
    }
  }
}

bool file_menu(char* file_name){
  int option = 0;

  while (1) {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
  
    if (option == 0) {
      u8g2.drawStr(1,15,"INFO");
      u8g2.setDrawColor(2);
      u8g2.drawBox(0,3,25,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(1,15,"INFO");
      u8g2.setDrawColor(1);
    }
    if (option == 1) {
      u8g2.drawStr(31,15,"MON");
      u8g2.setDrawColor(2);
      u8g2.drawBox(30,3,18,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(31,15,"MON");
      u8g2.setDrawColor(1);
    }
    if (option == 2) {
      u8g2.drawStr(55,15,"VOICE");
      u8g2.setDrawColor(2);
      u8g2.drawBox(54,3,30,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(55,15,"VOICE");
      u8g2.setDrawColor(1);
    }    
    if (TheVoice == 0) strcpy(str1, "OFF");
    else if (TheVoice==1) strcpy(str1, "REAL");
    else if (TheVoice==2) strcpy(str1, "EMUL");
    u8g2.drawStr(54,30,str1);

    if (option == 3) {
      u8g2.drawStr(91,15,"EXIT");
      u8g2.setDrawColor(2);
      u8g2.drawBox(90,3,25,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(91,15,"EXIT");
      u8g2.setDrawColor(1);
    }
    u8g2.sendBuffer(); // transfer internal memory to the display   
    
    if (digitalRead(butRIGHT)==LOW){
      delay(100);
      option++;
      if (option > 3) option = 0;
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      option--;
      if (option <0) option = 3;
    }

    if (digitalRead(butENTER)==LOW){
      delay(100);
      switch (option) {
        case 0: 
          SD_Init();
          if (SDOK) {
            openDirectory(&dirFile, dir_name);
            if (file_name[0]!='+'){
              if (file_name[0]!='\0'){
                show_info(file_name);
              }
            } 
            dirFile.close();
          } else {
            show_message(msgSDNOTOK);
            waitkey();
          }
          break;
        case 1:
          show_monitor();
          set_mode(MODE_PLAYING, game_pagging);
         break;
        case 2:
          TheVoice++;
          if (TheVoice==2) TheVoice = 0;

          if ((TheVoice==0) || (TheVoice==2)) {
            pinMode(THEVOICE_SELECT_PIN, OUTPUT);
            digitalWrite(THEVOICE_SELECT_PIN,LOW);
          } else if (TheVoice==1) {
            pinMode(THEVOICE_SELECT_PIN, INPUT_PULLUP);
          }
          break;
        case 3:
          return true;
          break;
        default:

          break;
      }
     }
    if (digitalRead(butESC)==LOW){
      delay(100);
      return false;
    }
  }
}

void select_file(){
  ch_ini = 0;
  inicio = millis();
  int index = 0;
  int selected = 0;
  openDirectory(&dirFile, dir_name);
  openCache_file(&dirFile);
  num_files = cache.fileSize()/MAX_FILENAME_LEN;
  Serial.print(F("NUMFILES="));
  Serial.println(num_files);
  read_screen(index, selected);
  show_file_screen(index, selected);
  while (1) {
    if (digitalRead(butDOWN)==LOW){
      delay(100);
      inicio = millis();
      ch_ini = 0;
      selected++;
      if (selected >= num_files) {
        selected = 0;
        index = 0;
        read_screen(index, selected);
      } else if (selected-index==NUM_SCRLINES){
        index=selected;
        read_screen(index, selected);
      }
    }
    if (digitalRead(butRIGHT)==LOW){
      delay(100);
      inicio = millis();
      selected+=20;
      ch_ini = 0;
      index+=20;
      if (selected >= num_files) {
        selected = 0;
        index = 0;
        read_screen(index, selected);
      }
      read_screen(index, selected);
    }
    if (digitalRead(butUP)==LOW){
      delay(100);
      inicio = millis();
      ch_ini = 0;
      selected--;
      if (selected<index){
        index-=NUM_SCRLINES;
       if (selected < 0) {
          index = ((num_files-1)/NUM_SCRLINES)*NUM_SCRLINES;
          selected = num_files-1;
        }
        read_screen(index, selected);
      }
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      inicio = millis();
      selected-=20;
      index -=20;
      if (selected < 0) {
        selected = ((num_files-1)/NUM_SCRLINES)*NUM_SCRLINES;
        index = selected;
      }
      read_screen(index, selected);
    }
    if (digitalRead(butENTER)==LOW){
      delay(100);
      if (scr_lines[selected-index][0]=='+') { // directory
        if (strcmp(scr_lines[selected-index],"+..")==0){
          remove_last_dir(dir_name);
          if (strlen(dir_name)==0) strcat(dir_name, "/");

          if(autorebuild || !file_exists(dir_name, strCacheFName))readDirectory(dir_name);
          index = 0;
          selected = 0;
          openDirectory(&dirFile, dir_name);
          openCache_file(&dirFile);
          read_screen(index, selected);
        } else {
          strmid(str1, scr_lines[selected-index], 1, strlen(scr_lines[selected-index])-1);
          if (strlen(dir_name) > 1)
          strcat(dir_name, "/");
          strcat(dir_name, str1);
          Serial.println(dir_name);
          if(autorebuild || !file_exists(dir_name, strCacheFName)){
            Serial.print(F("Rebuilding "));
            Serial.println(dir_name);
            readDirectory(dir_name);
          }
          index = 0;
          selected = 0;
          openDirectory(&dirFile, dir_name);
          openCache_file(&dirFile);
          read_screen(index, selected);
        }
      } else {
        strcpy(file_loaded, scr_lines[selected-index]);
        run_game(scr_lines[selected-index]);
      }
    }
    show_file_screen(index, selected);
    if (digitalRead(butESC)==LOW){
      while((digitalRead(butESC)==LOW) && (digitalRead(butENTER)==HIGH));
      if (digitalRead(butENTER)==LOW){
        show_screen_desc(index, selected);
        delay(1500);
        show_file_screen(index, selected);
      } else {
        while(digitalRead(butESC)==LOW);
        if (file_menu(scr_lines[selected-index])){
          return;
        }
      }
    }
  }
}

void select_baudrate(void){
//  unsigned long int bauds[] = {9600, 19200, 38400, 57600, 115200};
  byte bx[] =                 {   0,    30,    66,     0,     36};
  byte by[] =                 {  15,    15,    15,    30,     30};     
  bool selected = false;
  int option = 0;
  int i;
  
  delay(200);
  
//  for (i==0; i<4; i++)
//    if(bauds[i]==baudrate) option = i;

  option = baudrate;
    
  while (!selected) {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    for (i = 0; i<5; i++){
      sprintf_P(str1, PSTR("%lu"), bauds[i]);
      if (i==option){
        u8g2.drawStr(bx[i],by[i],str1);
        u8g2.setDrawColor(2);
        u8g2.drawBox(bx[i]-1,by[i]-12,(strlen(str1)+1)*6,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(bx[i],by[i],str1);
        u8g2.setDrawColor(1);
      }
    }
    u8g2.sendBuffer(); // transfer internal memory to the display   
    if (digitalRead(butRIGHT)==LOW){
      delay(100);
      option++;
      if (option > 4 ) option = 0;
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      option--;
      if (option <0) option = 4;
    }
    if (digitalRead(butENTER)==LOW){
      delay(100);
      selected = true;
      baudrate = option;
      save_baudrate();
    }
    if (digitalRead(butESC)==LOW){
      delay(100);
      selected = true;
      return;
    }
  }
  
}

void select_pagemode(void){
  char pgm[][8] = {"P10/P11", "VP+", "SOREN"};
  byte bx[] =   {   0,   48,   72};
  byte by[] =   {  15,   15,   15};     
  bool selected = false;
  int option = 0;
  int i;

  
  delay(200);
  
  for (i==0; i<3; i++)
    if(pgm[i]==remotepgm) option = i;
    
  while (!selected) {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    for (i = 0; i<3; i++){
      if (i==option){
        u8g2.drawStr(bx[i],by[i],pgm[i]);
        u8g2.setDrawColor(2);
        u8g2.drawBox(bx[i]-1,by[i]-12,(strlen(pgm[i])+1)*6,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(bx[i],by[i],pgm[i]);
        u8g2.setDrawColor(1);
      }
    }
    u8g2.sendBuffer(); // transfer internal memory to the display   
    if (digitalRead(butRIGHT)==LOW){
      delay(100);
      option++;
      if (option > 2 ) option = 0;
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      option--;
      if (option <0) option = 2;
    }
    if (digitalRead(butENTER)==LOW){
      delay(100);
      selected = true;
      remotepgm = pgm[option];
    }
    if (digitalRead(butESC)==LOW){
      delay(100);
      selected = true;
      return;
    }
  }
  
}


void rebuild_menu(void){
 int option = 0;
 int ch_ini_d = 0;
 long int inicio_d;

  inicio_d = millis();
  while (1) {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    
    u8g2.drawStr(1,11,"****REBUILD MENU****");
    u8g2.setDrawColor(1);
    u8g2.drawFrame(0,0,128,12);
//    u8g2.setDrawColor(1);
    if (((option >= 0) && (option <= 2)) || (option > 20)){ 
      if (option == 0) {
        u8g2.drawStr(1,24,"WHEN");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,13,6*4+2,12);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,24,"WHEN");
        u8g2.setDrawColor(1);
      }
      if (autorebuild)
        u8g2.drawStr(6*7,24,"--> (ALLWAYS)");
      else
        u8g2.drawStr(6*7,24,"--> (MANUALLY)");
      if (option == 1) {
        u8g2.drawStr(1,36,"REBUILD GAMELIST");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,25,6*17+2,12);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,36,"REBUILD GAMELIST");
        u8g2.setDrawColor(1);
      }
  
      if (option == 2) {
        u8g2.drawStr(1,48,"REBUILD DIRECTORY");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,37,6*17+2,12);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,48,"REBUILD DIRECTORY");
        u8g2.setDrawColor(1);
      }
    }
    u8g2.setDrawColor(1);
    
    rotate_str(str1, initial_dir, 21, true, &ch_ini_d, &inicio_d);
    u8g2.drawStr(1,60,str1);
    u8g2.drawHLine(0,49,128);
    u8g2.sendBuffer(); // transfer internal memory to the display 

    if (digitalRead(butUP)==LOW){
      delay(100);
      option--;
    }
    if (digitalRead(butDOWN)==LOW){
      delay(100);
      option++;
    }
    if (option >= 2) option = 2;
    if (option <0) option = 0;

    if (digitalRead(butENTER)==LOW){
      delay(100);
      switch (option) {
        case 0:
          autorebuild = !autorebuild;
          save_autorebuild();
          break;
        case 1:
          SD_Init();
          if (SDOK) {
            show_message("please wait");
            openDirectory(&dirFile, "/");
            rebuild_ini_file();
            dirFile.close();
          }
          break;
        case 2:
          readDirectory(initial_dir);
          break;
      }
    }
    if (digitalRead(butESC)==LOW){
      delay(100);
      return;
    }

  }
}

void config_menu (void){

 int option = 0;
 int ch_ini_f = 0;
 long int inicio_f;
 int ch_ini_d = 0;
 long int inicio_d;

  inicio_f = millis();
  inicio_d = millis();
  while (1) {
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    
    if (((option >= 0) && (option <= 2)) || (option > 20)){ 
      if (option == 0) {
        u8g2.drawStr(1,15,"SETDIR");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,3,37,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,15,"SETDIR");
        u8g2.setDrawColor(1);
      }
      if (option == 1) {
        u8g2.drawStr(43,15,"AUTOLOAD");
        u8g2.setDrawColor(2);
        u8g2.drawBox(42,3,49,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(43,15,"AUTOLOAD");
        u8g2.setDrawColor(1);
      }
  
      if (option == 2) {
        u8g2.drawStr(97,15,"LOGO");
        u8g2.setDrawColor(2);
        u8g2.drawBox(96,3,25,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(97,15,"LOGO");
        u8g2.setDrawColor(1);
      }
      if (to_show_logo)
        u8g2.drawStr(97,30,"YES");
      else
        u8g2.drawStr(97,30,"NO");    
    
      if (option == 30) {
        u8g2.drawStr(1,30,"RESET");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,18,31,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,30,"RESET");
        u8g2.setDrawColor(1);
      }
      
    } else {
      if (option == 3) {
        u8g2.drawStr(1,15,"REBUILD");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,3,43,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,15,"REBUILD");
        u8g2.setDrawColor(1);
      }
      if (option == 4) {
        u8g2.drawStr(48,15,"BAUD");
        u8g2.setDrawColor(2);
        u8g2.drawBox(47,3,24,16);
        u8g2.setDrawColor(1);
        sprintf_P(str1, PSTR("%lu bps"), bauds[baudrate]);
        u8g2.drawStr(1,30,str1);
      } else {
        u8g2.drawStr(48,15,"BAUD");
        u8g2.setDrawColor(1);
      }
      if (option == 5) {
        u8g2.drawStr(78,15,"SORTED");
        u8g2.setDrawColor(2);
        u8g2.drawBox(77,3,36,16);
        u8g2.setDrawColor(1);
        if (sorted)
          u8g2.drawStr(1,30,"YES");
        else
          u8g2.drawStr(1,30,"NO");
      } else {
        u8g2.drawStr(78,15,"SORTED");
        u8g2.setDrawColor(1);
      }
    }
    rotate_str(str1, autoload_file, 21, true, &ch_ini_f, &inicio_f);
    u8g2.drawStr(1,45,str1);
    rotate_str(str1, initial_dir, 21, true, &ch_ini_d, &inicio_d);
    u8g2.drawStr(1,60,str1);
    u8g2.sendBuffer(); // transfer internal memory to the display 

    if (digitalRead(butRIGHT)==LOW){
      delay(100);
      option++; 
      if (option >= 20) { 
        option = 30;
      } else {
        if (option > 5 ) option = 0;
      }
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      option--;
      if (option >= 20) { 
        option = 30;
      } else {
        if (option <0) option = 5;
      }
    }

    if (digitalRead(butDOWN)==LOW){
      delay(100);
      if ((option == 0) || (option==1)) option+=30; 
    }
    if (digitalRead(butUP)==LOW){
      delay(100);
      if ((option == 30) || (option==31)) option-=30; 
    }
    if (digitalRead(butENTER)==LOW){
      delay(100);
      switch (option) {
        case 0:
          if (SDOK) {
            strcpy(initial_dir, dir_name);
            ch_ini_d = 0;
            inicio_d = millis();
            save_initial_dir();
          } else {
            show_message(msgSDNOTOK);
            waitkey();
          }
          break;
        case 1:
          if (autoload_file[0]==0) {
            strcpy(autoload_file, "SELECTGAME.BIN");
            ch_ini_f = 0;
            inicio_f = millis();
            save_autoload_file();
            ch_ini_d = 0;
            inicio_d = millis();
          } else autoload_file[0] = 0;
          save_autoload_file();
          break;
        case 2:
          to_show_logo = not to_show_logo;
          save_show_logo();
          break;
        case 3:
          rebuild_menu();
          break;
//        case 4:
//          generate_selectgame(dir_name, 0, true);
//          break;
        case 4:
          select_baudrate();
          break;
        case 5:
          sorted = !sorted;
          save_sorted();
          break;
        case 30:
          strcpy(initial_dir,"/");
          save_initial_dir();
          break;
        case 31:
          autoload_file[0]='\0';
          save_autoload_file();
          break;
        default:
          break;
      }
    }
    if (digitalRead(butESC)==LOW){
      delay(100);
      return;
    }
  }
  
  waitforever();
    
}

void game_menu(){
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
          pong_main();
          break;
        case 1: // Native menu
          race_main();
          break;
//        case 2: // Native menu
//          runBitlash();
//          break;
        default:
          break;
      }
    }
    if (digitalRead(butESC)==LOW){
      delay(100);
      while (digitalRead(butENTER)==LOW);
      return;
    }
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font

    if (option == 0) {
      u8g2.drawStr(1,15,"PONG");
      u8g2.setDrawColor(2);
      u8g2.drawBox(0,3,26,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(1,15,"PONG");
      u8g2.setDrawColor(1);
    }
    if (option == 1) {
      u8g2.drawStr(31,15,"RACE");
      u8g2.setDrawColor(2);
      u8g2.drawBox(30,3,25,16);
      u8g2.setDrawColor(1);
    } else {
      u8g2.drawStr(31,15,"RACE");
      u8g2.setDrawColor(1);
    }
//    if (option == 2) {
//      u8g2.drawStr(61,15,"SCRIPT");
//      u8g2.setDrawColor(2);
//      u8g2.drawBox(60,3,31,16);
//      u8g2.setDrawColor(1);
//    } else {
//      u8g2.drawStr(61,15,"SCRIPT");
//      u8g2.setDrawColor(1);
//    }
    
    u8g2.sendBuffer(); // transfer internal memory to the display 
  }
}

unsigned long int inicio_dir = 0;
int ch_ini_dir = 0;
unsigned long int inicio_fil = 0;
int ch_ini_fil = 0;

void draw_main_menu(int option){
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font

    if (option <= 2) {
      if (option == 0) {
        u8g2.drawStr(1,15,"LOAD");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,3,26,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,15,"LOAD");
        u8g2.setDrawColor(1);
      }
      if (option == 1) {
        u8g2.drawStr(31,15,"VPMENU");
        u8g2.setDrawColor(2);
        u8g2.drawBox(30,3,37,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(31,15,"VPMENU");
        u8g2.setDrawColor(1);
      }
      if (option == 2) {
        u8g2.drawStr(73,15,"CONFIG");
        u8g2.setDrawColor(2);
        u8g2.drawBox(72,3,38,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(73,15,"CONFIG");
        u8g2.setDrawColor(1);
      }
    } else {
      if (option == 3) {
        u8g2.drawStr(1,15,"RECEIVE");
        u8g2.setDrawColor(2);
        u8g2.drawBox(0,3,42,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(1,15,"RECEIVE");
        u8g2.setDrawColor(1);
      }
      if (option == 4) {
        u8g2.drawStr(48,15,"ABOUT");
        u8g2.setDrawColor(2);
        u8g2.drawBox(47,3,30,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(48,15,"ABOUT");
        u8g2.setDrawColor(1);
      }
      if (option == 5) {
        u8g2.drawStr(48+36,15,"GAME");
        u8g2.setDrawColor(2);
        u8g2.drawBox(47+36,3,6*4,16);
        u8g2.setDrawColor(1);
      } else {
        u8g2.drawStr(48+36,15,"GAME");
        u8g2.setDrawColor(1);
      }
    }  
    
    rotate_str(str1, dir_name, 21, true, &ch_ini_dir, &inicio_dir);
    u8g2.drawStr(1,30,str1);
    rotate_str(str1, file_loaded, 21, true, &ch_ini_fil, &inicio_fil);
    u8g2.drawStr(1,45,str1);
    printVolt(0,63);
    u8g2.sendBuffer(); // transfer internal memory to the display 
}

void main_menu(void){
  int option = 0;
  draw_main_menu(option);
  while (1) {
    if (digitalRead(butRIGHT)==LOW){
      delay(200);
      option++;
      if (option > 5) option = 0;
    }
    if (digitalRead(butLEFT)==LOW){
      delay(100);
      option--;
      if (option <0) option = 5;
    }

    if (digitalRead(butENTER)==LOW){
      delay(100);
      switch (option) {
        case 0:
          SD_Init();
          if (SDOK) {
            if(autorebuild || !file_exists(dir_name, strCacheFName))readDirectory(dir_name);
            show_select_game(true);
            select_file();
            while (digitalRead(butENTER)==LOW);
          }
          break;
        case 1: // Native menu
            SD_Init();
            if (SDOK) {
              if (dirFile.isOpen())
                dirFile.close();
              openDirectory(&dirFile, dir_name);
              run_game("selectgame.bin");
              dirFile.close();
            }
          break;
        case 2:
          while (digitalRead(butENTER)==LOW);
          delay(100); 
          config_menu();
          break;
        case 3:
          // pagging2str(remotepgm, str1);
          // select_pagemode();
          receivefile(bauds[baudrate]);
          break;
        case 4:
          delay(100);
          show_logo();
          break;
        case 5:
          delay(100);
          waitNoKey();
          game_menu();
          break;
        default:
          break;
      }
    }
    draw_main_menu(option);
    if (digitalRead(butESC)==LOW){
      delay(100);
      file_menu(file_loaded);
      draw_main_menu(option);
      while (digitalRead(butENTER)==LOW);
    }
  }
  

  waitforever();
    
}
