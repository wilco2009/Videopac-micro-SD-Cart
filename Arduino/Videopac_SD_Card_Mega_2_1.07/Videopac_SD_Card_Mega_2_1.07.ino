
#define VIDEOPAC
//#define SSD1306
#define SH1106

#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include "SdFat.h"
#include "FreeStack.h"
#include <EEPROM.h>

#ifdef U8X8_HAVE_HW_I2C
#include <Wire.h>
#endif
#define SD_ChipSelectPin 53 //SD_CS_PIN  
#include <TMRpcm.h>           

// #include "bitlash.h"
#include "globales.h"
#include "images.h"
#include "tools.h"
#include "CRC32.h"
#include "chip_handle.h"
#include "SerialCOM.h"
#include "File_Handle.h"
#include "monitor.h"
#include "pong.h"
#include "race.h"
#include "HMI.h"
#include "test.h"

void setup(void) {
//  Serial.begin(57600);
//    tmrpcm.speakerPin = 11;//46; //11 on Mega, 9 on Uno, Nano, etc
//  if (!sd.begin(SD_ChipSelectPin)) {  // see if the card is present and can be initialized:
//    Serial.println("SD Error");
//  return;   // don't do anything more if not
//  } else Serial.println("SD OK");
//  delay(3000);
////    tmrpcm.volume(1);
//    // tmrpcm.quality(1);
//    delay(3000);
//    tmrpcm.play("/WAV/1.wav");
//    waitforever();
//    //  tmrpcm.play("/WAV/E4A3.wav");
  u8g2.begin();
 
  pinMode(SPEAKER_PIN, INPUT);
  pinMode(VOICE_PIN, INPUT);

  pinMode(WR, OUTPUT);
  pinMode(OE, OUTPUT);
  pinMode(LED_SD, OUTPUT);
  pinMode(LED_RAM, OUTPUT);
  pinMode(butUP, INPUT_PULLUP);
  pinMode(butDOWN, INPUT_PULLUP);
  pinMode(butLEFT, INPUT_PULLUP);
  pinMode(butRIGHT, INPUT_PULLUP);
  pinMode(butENTER, INPUT_PULLUP);
  pinMode(butESC, INPUT_PULLUP);

  pinMode(PAGEMODE0, OUTPUT);
  pinMode(PAGEMODE1, OUTPUT);
  pinMode(PAGEMODE2, OUTPUT);
  
  pinMode(THEVOICE_SELECT_PIN, OUTPUT);
  digitalWrite(THEVOICE_SELECT_PIN,LOW);

  pinMode(pMISO, OUTPUT);

  pinMode(A15,INPUT);
  analogReference(INTERNAL2V56);

  digitalWrite(pMISO,LOW);
  digitalWrite(LED_SD, HIGH);
  digitalWrite(LED_RAM, LOW);

  audio.speakerPin = 46; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  pinMode(45,OUTPUT); //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45  

  set_mode(MODE_SENDING_GAME, 0);
  set_mode(MODE_PLAYING, 0);
  cont = 0;
  sd_led_off();
  ram_led_off();

  // initialize serial communication at 9600 bits per second:
  Serial.begin(57600);
//  initBitlash(57600);

  load_RAM_delay();
  load_show_logo();
  if (to_show_logo){
    show_logo();
  
    long int inicio = millis();
    while ((millis()-inicio < 1000) & (digitalRead(butESC)==HIGH));
  }
  if ((digitalRead(butLEFT)==LOW) && (digitalRead(butENTER)==LOW)) {
    Serial.println(F("LEFT+ENTER detected"));
    diagnostics();
  }
  if ((digitalRead(butLEFT)==LOW) && (digitalRead(butESC)==LOW)){
    strcpy(initial_dir, "/");
    strcpy(autoload_file, "SELECTGAME.BIN");
    Serial.println(F("LEFT+ESC detected"));
    Serial.println(F("Launching selectgame.bin"));
    save_autoload_file();
    save_initial_dir();
  }
  if ((digitalRead(butESC)==LOW) && (digitalRead(butENTER)==LOW)){
    resetting = true;
    u8g2.clearBuffer();          // clear the internal memory
    u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
    u8g2.drawStr(1,15,"Reset to factory...");
    u8g2.setDrawColor(1);
    u8g2.sendBuffer(); // transfer internal memory to the display 
    Serial.println(F("ESC+ENTER detected"));
    Serial.println(F("Reset to factory..."));
    delay(500);
    to_show_logo = true;
    autoload_file[0] = '\0';
    baudrate = 4;
    sorted = false;
    RAM_delay = 15;
    strcpy(initial_dir, "/");
    save_autoload_file();
    save_initial_dir();
    save_show_logo();
    save_baudrate();
    save_sorted();
    save_RAM_delay();
  }

  Serial.print(F("Initializing SD card..."));

  SD_Init(); 

//  audio.quality(1);
//
//  audio.play("/WAV/E880.wav");
//
//  while (audio.isPlaying());
//
//  audio.play("/WAV/E881.wav");
//
//  while (audio.isPlaying());
//
//  audio.play("/WAV/E49B.wav");
//
//  while (audio.isPlaying());
//
//  audio.play("/WAV/E487.wav");
//
//  while (audio.isPlaying());
//
//  audio.play("/WAV/E4AD.wav");
//
//  while (audio.isPlaying());
//
//  audio.play("/WAV/E4A0.wav");
//
//  audio.setVolume(0);
//
//  audio.disable();
//

  if (!resetting){
    load_autoload_file();
    load_initial_dir();
    load_baudrate();
    load_sorted();
    load_autorebuild();
    load_RAM_delay();
  }
  if (SDOK) {
    while(digitalRead(butESC)==LOW); 
  
    openDirectory(&dirFile, "/");
    if ((dirFile.exists("gamelist.dat")==false)||(dirFile.exists("gamelist.idx")==false)){
      rebuild_ini_file();
    }
    dirFile.close();
  
  //  Serial.println(autoload_file);  
    strcpy(dir_name, initial_dir);
    strcpy(file_loaded, autoload_file);
  
    if (autoload_file[0]!='\0'){
      openDirectory(&dirFile, dir_name);
      run_game(autoload_file);
      dirFile.close();
    }
  }
//  dump_vp_dir("/"); 
}

void test(void){
  
unsigned char data;

  unsigned int i;
  Serial.println(F("Writting...."));
  set_mode(MODE_SENDING_GAME, game_pagging);
  byte c = 0;
  for (i = 0; i<32768; i++){
    RAM_write(i, c);
    c++;
  }
  Serial.println(F("Checking...."));
  
  c = 0;
  for (i = 0; i<32768; i++){
    data = RAM_read(i);
    if (data != c) {
        Serial.print (i);
        Serial.print (F(", "));
        Serial.print (data);
        Serial.print (F(", "));
        Serial.println (c);
    }
    c++;
  }

  Serial.println(F("OK"));
  
  RAM_write(1, 0);
  data = RAM_read(65535);
  Serial.println(data);
  data = RAM_read(0);
  Serial.println(data);
  data = RAM_read(1);
  Serial.println(data);
  set_mode(MODE_PLAYING, game_pagging);
  waitforever();
}


void loop(void) {

//  test();
//  waitforever();

  main_menu();
  cache.close();
  dirFile.close();

  waitforever();
  

  while (1){
    
      show_monitor();  
  }

  waitforever();
}
