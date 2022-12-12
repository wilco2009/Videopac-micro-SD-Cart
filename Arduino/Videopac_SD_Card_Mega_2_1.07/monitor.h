void SerialPrintRAM(void){
  Serial.println(F("Offset(h) 00 01 02 03 04 05 06 07 08 09 0A 0B 0C 0D 0E 0F"));
  for (int cont=0;cont<16384;cont+=16){
    sprintf_P(str1, PSTR("%08X "), cont);
    Serial.print(str1);
    for (int x=0; x<16; x++){
      int dato = RAM_read(cont+x);
      sprintf_P(str1, PSTR("%02X"), dato);
      Serial.print(F(" ")); 
      Serial.print(str1);
    }
    Serial.println();
  } 
}

void RAM_monitor(void){
  static long int addr = 0;
    set_mode(MODE_SENDING_GAME, game_pagging);
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_5x8_mf); // choose a suitable font
    for (int j=0; j<4; j++){
      sprintf_P(str1, PSTR("%04X"), addr+j*16);
      u8g2.drawStr(0,8+16*j,str1);
      for (byte i=0;i<8;i++){
        sprintf_P(str1, PSTR("%02X"), RAM_read(addr+j*16+i));
        u8g2.drawStr(23+i*12,8+16*j,str1);
      }
      sprintf_P(str1, PSTR("%04X"), addr+j*16+8);
      u8g2.drawStr(0,16+16*j,str1);
      for (byte i=0;i<8;i++){
        sprintf_P(str1, PSTR("%02X"), RAM_read(addr+j*16+i+8));
        u8g2.drawStr(23+i*12,16+16*j,str1);
      }
    }
    u8g2.sendBuffer(); // transfer internal memory to the display   

  if (digitalRead(butUP)==LOW){
    while(digitalRead(butUP)==LOW);
    addr-=64;
    if (addr < 0) addr = 32768-64;
  }
  if (digitalRead(butDOWN)==LOW){
    while(digitalRead(butDOWN)==LOW);
    addr+=64;
    if (addr > 32767) addr = 0;
  }
  if (digitalRead(butLEFT)==LOW){
    while(digitalRead(butLEFT)==LOW);
    addr=((addr-1024)/1024)*1024;
    if (addr < 0) addr = 32768-64;
  }
  if (digitalRead(butRIGHT)==LOW){
    while(digitalRead(butRIGHT)==LOW);
    addr=((addr+1024)/1024)*1024;
    if (addr > 32767) addr = 0;
  }
}



void signal_monitor(void){
    set_mode(MODE_PLAYING, game_pagging);
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_profont12_mf); // choose a suitable font
    sprintf_P(str1, PSTR("ADDR:%04X DATA:%02X"), PINF+PINK*256, PINA);
    u8g2.drawStr(0,15,str1);
//    sprintf_P(str1, PSTR("PSEN:%01X CS:%01X WR:%01X"), digitalRead(CE), digitalRead(OE), digitalRead(WR));
    u8g2.drawStr(0,30,str1);
//    sprintf_P(str1, PSTR("IC2:%01X%01X IC3:%01X%01X IC4:%01X%01X"), digitalRead(IC2_G), digitalRead(IC2_DIR), digitalRead(IC3_G), digitalRead(IC3_DIR), digitalRead(IC4_G), digitalRead(IC4_DIR));
    u8g2.drawStr(0,45,str1);
    sprintf_P(str1, PSTR("LUDR+-: %01X%01X%01X%01X%01X%01X"), digitalRead(butLEFT), digitalRead(butUP), digitalRead(butDOWN), digitalRead(butRIGHT), digitalRead(butENTER), digitalRead(butESC));
    u8g2.drawStr(0,60,str1);
    u8g2.sendBuffer(); // transfer internal memory to the display   
    
}

void show_monitor(void){
  static int scr_active = 0;
  while (digitalRead(butESC)==HIGH){
//    if (scr_active == 0) {
//      ram_led_off();
//      signal_monitor();
//    } else
     RAM_monitor();
  
    if (digitalRead(butENTER)==LOW){
      while(digitalRead(butENTER)==LOW);
      scr_active++;
      if (scr_active > 1) scr_active = 0;
    }
  }
  while(digitalRead(butESC)==LOW);
}

 
