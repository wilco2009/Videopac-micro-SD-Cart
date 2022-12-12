unsigned int addr_test = 0;

void readStr(char* str){
  boolean fin = false;
  int i = 0;
  while (!fin){
    if (Serial.available()>0) {
      char c = Serial.read();
      if ((c == 13) || (c==10)) fin = true;
      else if ((c>=' ')&&(c<='z')) {
        str[i] = c;
        str[i+1] = 0;
        i++;
      }
    }
  }
}

void printDirectory(void){
#ifdef SDFAT
SdFat sd;
SdFile file;
SdFile dirFile;
#else
File file;
File dirFile;
#endif


  Serial.print("Initializing SD card...");

  SD_Init(); 

  // List files in root directory.
#ifdef SDFAT
  if (!dirFile.open("/", O_READ)) {
    Serial.println("open root failed");
  }
#else
  dirFile = SD.open("/", FILE_READ);
  if (!dirFile)) {
    Serial.println("open root failed");
  }
#endif
  while (file.openNext(&dirFile, O_READ)) {
    file.printName(&Serial);
    Serial.println();
    file.close();
  }
  sd_led_off();
}

void testButton(int but, char* str){
  Serial.print(str);
  Serial.print("=");
  str1[0]=0;
  while ((digitalRead(but)==HIGH) && (str1[0]!='X')){
    if (Serial.available() > 0) {
      readStr(str1);
      upStr(str1);
    }
  }
  if (str1[0]=='X')
    Serial.println(F("SKIPPED"));
  else
    Serial.println("OK");    
}

void testButtons(void){
  Serial.println(F("PRESS BUTTON.... (x to exit)"));
  testButton(butLEFT, "LEFT");
  testButton(butUP, "UP");
  testButton(butRIGHT, "RIGHT");
  testButton(butDOWN, "DOWN");
  testButton(butESC, "ESC");
  testButton(butENTER, "ENTER");
}  

void printBit(unsigned int value, int index){
  unsigned int b = 1 << index;
  if ((b & value) == 0)
    Serial.print(F("0"));
  else 
    Serial.print(F("1"));
}

void printBinary(unsigned int value, byte bits, char* sep){
  int i;
  unsigned int b;
  for (i = bits-1; i>=0; i--){
    printBit(value,i);
    Serial.print(sep);
    b = 1 << i;
  }
}

void testDataBit(int i, boolean inverted){
  byte r1, r2, w, cl;
  w = 1 << (i); 
  if (inverted) { 
    w = ~w;
    cl = 255;
  } else cl = 0;
  RAM_write(addr_test,cl);
  r1 = RAM_read(addr_test);

  RAM_write(addr_test,w);
  r2 = RAM_read(addr_test);
  Serial.print(F("D"));
  Serial.print(i);
  Serial.print(": ");
  if ((r1==cl) && (r2==w))
    Serial.print(F(" OK "));
  else
    Serial.print(F("BAD "));
  Serial.print(F(" "));
  printBit(r1,i);
  Serial.print(F("   "));
  printBit(r2,i);
  Serial.print(F("  "));

  printBinary(r1, 8, "");
  Serial.print(F(" "));
  printBinary(r2, 8, "");
  
  Serial.println(F(" "));
}

void testAddrBit(byte i, boolean inverse){
  unsigned int addr = 1 << i;
  int comp;
  if (!inverse){
    comp = 0;
  } else {
//    comp = 32767;
    comp = 16383;
    addr = ~addr;
  }
  RAM_write(comp, 0);
  RAM_write(addr, 0);
  RAM_write(addr, 255);
  byte c1 = RAM_read(comp);
  byte c2 = RAM_read(addr);
  RAM_write(comp, 255);
  RAM_write(addr, 0);
  byte c3 = RAM_read(comp);
  byte c4 = RAM_read(addr);
  Serial.print(F("A"));
  Serial.print(i);
  if (i < 10) Serial.print(F(" "));
  Serial.print(F(": "));
  if ((c1==0) && (c2==255)&&(c3==255) && (c4==0)){
    Serial.print(F(" OK "));
  } else {
    Serial.print(F("BAD "));
  }
  printBinary(addr, 16, "");
  Serial.print(F(" "));
  printBinary(c1, 8, "");
  Serial.print(F(" "));
  printBinary(c2, 8, "");
  Serial.print(F(" "));
  printBinary(c3, 8, "");
  Serial.print(F(" "));
  printBinary(c4, 8, "");
  
  Serial.println(F(" "));
}

void RAM_test(void){
  unsigned int i,n;
  byte c;
  set_mode(MODE_SENDING_GAME, 0); 
  Serial.println(); 
  Serial.print(F("TESTING DATA BUS (ADDR="));
  Serial.print(addr_test);
  Serial.println(F(")"));
  Serial.println(F("     OK (0) (1) 76543210 76543210"));
  for (int i=7; i>=0; i--)
    testDataBit(i,false);
  Serial.println(); 

//  Serial.println(F("     OK (0) (1) 76543210 76543210"));
//  for (int i=7; i>=0; i--)
//    testDataBit(i,true);
//  Serial.println(); 
  Serial.println(); 
  Serial.println(F("TESTING ADDR BUS"));
  sprintf_P(str1,PSTR("                          --%04X-- --ADDR-- --%04X-- --ADDR--"),0,0);
  Serial.println(str1);
  Serial.println(F("      OK ------ADDR------ 76543210 76543210 76543210 76543210"));
  for (int i=13; i>=0; i--)
    testAddrBit(i, false);
  Serial.println(); 
  Serial.println(); 
  
//  sprintf_P(str1,PSTR("                          --%04X-- --ADDR-- --%04X-- --ADDR--"),32767,32767);
//  Serial.println(str1);
//  Serial.println(F("      OK ------ADDR------ 76543210 76543210 76543210 76543210"));
//  for (int i=13; i>=0; i--)
//    testAddrBit(i, true);
//  Serial.println(); 
//  Serial.println(); 

  Serial.println(F("TESTING MEMORY"));
  Serial.println(); 
  Serial.println(F("Filling with Zeroes"));
  for (i=0;i<16384;i++) RAM_write(i,0);

  str1[0]=0;
  n = 0;
  Serial.println(F("Checking"));
  for (i=0;i<16384;i++) {
    c = RAM_read(i);
    if (c!=0) {
      n++;
      Serial.print(F("Error in Address "));
      Serial.print(i);
      Serial.print(F("; readed "));
      Serial.print(c);
      Serial.println(F(" written 0"));
    }
    if (Serial.available() > 0) {
      readStr(str1);
      upStr(str1);
    }
    if (str1[0]=='X') return;
    if (str1[0]=='S') break;
  }
  if (n==0) Serial.print(F("No"));
  else Serial.print(n);
  Serial.println(F(" errors found."));
  Serial.println(); 
//  Serial.println(F("Filling with Ones"));
//  for (i=0;i<16384;i++) RAM_write(i,255);
//
//  str1[0]=0;
//  n = 0;
//  Serial.println(F("Checking"));
//  for (i=0;i<16384;i++) {
//    c = RAM_read(i);
//    if (c!=255) {
//      n++;
//      Serial.print(F("Error in Address "));
//      Serial.print(i);
//      Serial.print(F("; readed "));
//      Serial.print(c);
//      Serial.println(F(" written 255"));
//    }
//    if (Serial.available() > 0) {
//      readStr(str1);
//      upStr(str1);
//    }
//    if (str1[0]=='X') return;
//    if (str1[0]=='S') break;
//  }
//  if (n==0) Serial.print(F("No"));
//  else Serial.print(n);
//  Serial.println(F(" errors found."));
//  Serial.println(); 
  
  Serial.println(F("Filling with random values "));
  srand(1);
  for (i=0;i<16384;i++) RAM_write(i,rand()%256);

  str1[0]=0;
  n = 0;
  srand(1);
  Serial.println(F("Checking"));
  for (i=0;i<16384;i++) {
    c = RAM_read(i);
    int v = rand()%256;
    if (c!=(v)) {
      n++;
//      Serial.print(F("Error in Address "));
//      Serial.print(i);
//      Serial.print(F("; readed "));
//      Serial.print(c);
//      Serial.print(F(" written "));
//      Serial.println(v);
    } else {
//      Serial.print(F("OK Address "));
//      Serial.println(i);
//      Serial.print("-");
//  printBinary(i, 16, "");
//      Serial.print(F("; readed "));
//      Serial.print(c);
//      Serial.print(F(" written "));
//      Serial.println(v);
      
    }
    if (Serial.available() > 0) {
      readStr(str1);
      upStr(str1);
    }
    if (str1[0]=='X') return;
    if (str1[0]=='S') break;
  }
  if (n==0) Serial.print(F("No"));
  else Serial.print(n);
  Serial.println(" errors found.");
  ram_led_off();
} 

void RAM_delay_change(){
  Serial.print(F("Current RAM delay value: "));
  Serial.println(RAM_delay);
  str1[0]=0;
  while (((str1[0]<'0')||(str1[0]>'9'))&&(str1[0]!='X')){
    if (Serial.available() > 0) {
      readStr(str1);
      upStr(str1);
    }
  }
  if (str1[0]!='X') RAM_delay = atoi(str1);
  Serial.print(F("New RAM delay value: "));
  Serial.println(RAM_delay);
  save_RAM_delay();
}

void addr_test_change(){
  Serial.print(F("Current test addr value: "));
  Serial.println(addr_test);
  str1[0]=0;
  while (((str1[0]<'0')||(str1[0]>'9'))&&(str1[0]!='X')){
    if (Serial.available() > 0) {
      readStr(str1);
      upStr(str1);
    }
  }
  if (str1[0]!='X') addr_test = atoi(str1);
  Serial.print(F("New addr test value: "));
  Serial.println(addr_test);
}

void BUS_test(void){
  byte value1, value2, value3, value4;
  byte bak1, bak2, bak3, bak4;
  bak1 = 123;
  bak2 = 0;
  bak3 = 255;
  bak4 = 111;
  set_mode(MODE_PLAYING, PAG_TEST); 
  str1[0]=0;
  
  Serial.println();
  Serial.println(F("(X) TO EXIT"));
 
  while (str1[0]!='X'){
    if (Serial.available() > 0) {
      readStr(str1);
      upStr(str1);
    }
    value1 = BUS_read(0);
    value2 = BUS_read(1);
    value3 = BUS_read(2);    
    value4 = BUS_read(3); 
    if ((value1 != bak1)||(value2 != bak2)||(value3 != bak3)||(value4 != bak4)){
      Serial.println(F("T0  D0  D1  D2  D3  D4  D5  D6  D7  A10 P14 P11 P10 A11 A9  --"));
      printBinary(value1,8, "   ");
      printBinary(value2,8, "   ");
      Serial.println();
      
      Serial.println(F("A8  A6  A7  A5  A4  A3  A2  A1  A0  PS  ER  --  --  --  WR  --"));
      printBinary(value3,8, "   ");
      printBinary(value4,8, "   ");
      Serial.println();
      bak1 = value1;
      bak2 = value2;
      bak3 = value3;
      bak4 = value4;
    }
  }
}

void custom_test(){
  set_mode(MODE_SENDING_GAME, 0); 
  Serial.println(F("Custom test"));
  DDRA = B11111111;
  digitalWrite(OE,HIGH);
  digitalWrite(WR,LOW);
  
//  Serial.println(F("00100100"));
  PORTA = B11111111;

  waitkey();
  
}

//void display_RAM(){
//char A_pin [15] = { 21, 23, 24, 25, 26, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
//
//const int st = 20;
//const int chip_w = 28;
//const int chip_l = 100;
//const int pinlen = 10;
//  for (int i=0; i<13;i++){
//    while (digitalRead(butENTER)!=LOW){
//      u8g2.clearBuffer();          // clear the internal memory
//      u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
//      u8g2.setDrawColor(1);
//      for (int j=0; j<14; j++){
//        for (int k=0; k<2; k++){
//          u8g2.drawVLine(st+4+j*7, 32-14-pinlen+k*38, pinlen);
//        }
//      }
//      u8g2.drawBox(st, 32-chip_w/2,chip_l, chip_w);
//
//      u8g2.drawBox(st, 32-chip_w/2,chip_l, chip_w);
//      
//      u8g2.setDrawColor(0);
//      u8g2.drawBox(st+chip_l-4, 32-4,4, 8);
//      u8g2.sendBuffer(); // transfer internal memory to the display   
//    }
//    waitNoKey();
//  }
//  
//}
void signal_by_signal_test(){
  int pin = 0;
  int value = 0;
  int RAM_pin[] = {-1, A12, A7, A6, A5, A4, A3, A2, A1, A0, 22, 23, 24, -1,  25,  26,  27,  28,  29,  -1, A10, OE, A11, A9, A8, A13,  WR, -1};
  int RAM_val[] = {  0,   0,  0,  0, 0, 0, 0, 0, 0, 0, 0, 0,  0,  0,  0,  0,   0,   0,   0,   0,   0,  0,   0, 0,   0,  0,  0,   0,  0,  1};

  set_mode(MODE_SENDING_GAME, 0); 
  DDRA = B11111111;
  PORTA = 255;
  for (int i=0; i<28; i++){
    if (RAM_pin[i]>0){
      pinMode(RAM_pin[i],OUTPUT);
      digitalWrite(RAM_pin[i],value);
    }
  }

  str1[0] = 0;
  while (str1[0]!='X'){
    fin = false;
    Serial.print("PIN? ");
    while ((fin == false) && (str1[0]!='X')){
      if (Serial.available() > 0) {
        readStr(str1);
        upStr(str1);
        if (str1[0]=='S'){
          Serial.println();
          for (int i=0; i<14; i++){
            int v1 = RAM_val[i];
            int v2 = RAM_val[27-i];
            if (RAM_val[26]==1){
              if ((i>=10)&&(i<=12)) v1 = 255;
              if ((28-i>=14)&&(28-i<=18)) v2 = 255;
            }
            sprintf(str1, "%02d - %02X       %02d - %02X", i+1, v1, 28-i, v2);
            Serial.println(str1);
          }
          Serial.print("PIN? ");
        } else {
          pin = atoi(str1);
          fin = true;
        }
      }
      
    }
    fin = false;
    Serial.print(pin);
    Serial.print(" VALUE? ");
    while ((fin == false) && (str1[0]!='X')){
      
      if (Serial.available() > 0) {
        readStr(str1);
        upStr(str1);
        value = atoi(str1);
        if (value > 1) value = 1;
        if (value < 0) value = 0;
        fin = true;
       }
    }
    Serial.println(value);
    if (pin == 0) {
      for (int i=0; i<28; i++){
        if (RAM_pin[i]>0){
          RAM_val[i] = value;
          if (RAM_pin[i]==3) {
            if (value == 0) DDRA = B11111111;
            else DDRA = B00000000;
          }
          digitalWrite(RAM_pin[i],value);
        }
      }
    } else if ((RAM_pin[pin-1] > 0) && (pin>0) && (pin<=28)) {
      digitalWrite(RAM_pin[pin-1], value);
      RAM_val[pin-1] = value;
    }
  }
}

void diagnostics(void){
  show_message("DIAGNOSTICS");
  boolean fin = false;
  while (!fin){
    Serial.println(); 
    Serial.println(); 
    Serial.println(F("**** DIAGNOSTICS ****"));
    Serial.println(F("(1) DISPLAY"));
    Serial.println(F("(2) LEDs"));
    Serial.println(F("(3) SD"));
    Serial.println(F("(4) BUTTONS"));
    Serial.println(F("(5) SPEAKER"));
    Serial.println(F("(6) RAM"));
    Serial.println(F("(7) BUS"));
    Serial.print(F("(8) SET RAM DELAY FOR WRITE("));
    Serial.print(RAM_delay);
    Serial.println(")");
    Serial.print(F("(9) SET ADDR FOR DATA BUS TEST ("));
    Serial.print(addr_test);
    Serial.println(F(")"));
    Serial.println(F("(A) SIGNAL BY SIGNAL TEST"));
    Serial.println(F("(Q) QUIT"));
    Serial.println(F("*********************"));
    Serial.print(F("OPTION? "));
  
    readStr(str1);
    upStr(str1);
    Serial.println(str1);
    if (strcmp(str1,"1")==0){
      show_logo();
      delay(2000);
      show_message(disp);
      Serial.print(F("DISPLAY MODEL="));
      Serial.println(disp);
      delay(3000);
      show_message("DIAGNOSTICS");
    } else if (strcmp(str1,"2")==0){
      sd_led_off();
      ram_led_off();
      for (int i=0; i< 5; i++){
        Serial.println(F("SD LED ON"));
        ram_led_off();
        sd_led_on();
        delay(1000);
        Serial.println(F("RAM LED ON"));
        sd_led_off();
        ram_led_on();
        delay(1000);
      }
      sd_led_off();
      ram_led_off();
    } else if (strcmp(str1,"3")==0){
      printDirectory();
    } else if (strcmp(str1,"4")==0){
      testButtons();
    } else if (strcmp(str1,"5")==0){
      sonido_select_game();
    } else if (strcmp(str1,"6")==0){
      RAM_test();
    } else if (strcmp(str1,"7")==0){
      BUS_test();
    } else if (strcmp(str1,"8")==0){
      RAM_delay_change();
    } else if (strcmp(str1,"9")==0){
      addr_test_change();
    } else if (strcmp(str1,"0")==0){
      custom_test();
    } else if (strcmp(str1,"A")==0){
      signal_by_signal_test();
    } else if (strcmp(str1,"Q")==0){
      fin = true;
    }

  }
}
