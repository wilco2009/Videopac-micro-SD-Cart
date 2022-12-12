void set_mode(int mode, int pagging){
//  direccion = 0; // hacia el bus
// direccion = 1; // hacia la RAM

#ifdef ATARI
  if (mode==MODE_PLAYING){
        digitalWrite(PAGEMODE0,0);  
        digitalWrite(PAGEMODE1,0);    
        digitalWrite(PAGEMODE2,0);  
        DDRA = B00000000;
        DDRK = B00000000; 
        DDRF = B00000000;
        PORTA = 0;
        PORTK = 0;
        PORTF = 0;
        digitalWrite(OE,LOW);
        digitalWrite(WR,HIGH);
  } else if (mode==MODE_SENDING_GAME) {
        digitalWrite(PAGEMODE0,0);  
        digitalWrite(PAGEMODE1,0);    
        digitalWrite(PAGEMODE2,1);  
        DDRA = B00000000;
        DDRK = B00000000;
        DDRF = B00000000;
        PORTA = 0;
        PORTK = 0;
        PORTF = 0;
        digitalWrite(OE,LOW);
        digitalWrite(WR,HIGH);
  }
#endif

#ifdef VIDEOPAC
  if (mode==MODE_PLAYING){
      switch (pagging){
        case PAG_SELECT_GAME:
          digitalWrite(PAGEMODE0,1);  
          digitalWrite(PAGEMODE1,1);    
          digitalWrite(PAGEMODE2,0);  
          DDRA = B00000000;
          DDRK = B00000000;
          DDRF = B00000000;
          PORTA = 0;
          PORTK = 0;
          PORTF = 0;
          digitalWrite(OE,LOW);
          digitalWrite(WR,HIGH);
          break;
        case PAG_P10_P11:
          digitalWrite(PAGEMODE0,0);  
          digitalWrite(PAGEMODE1,0);    
          digitalWrite(PAGEMODE2,0);  
          DDRA = B00000000;
          DDRK = B00000000;
          DDRF = B00000000;
          PORTA = 0;
          PORTK = 0;
          PORTF = 0;
          digitalWrite(OE,LOW);
          digitalWrite(WR,HIGH);
          break;
        case PAG_VP_PLUS:
          digitalWrite(PAGEMODE0,1);  
          digitalWrite(PAGEMODE1,0);    
          digitalWrite(PAGEMODE2,0);  
          DDRA = B00000000;
          DDRK = B00000000;
          DDRF = B00000000;
          PORTA = 0;
          PORTK = 0;
          PORTF = 0;
          digitalWrite(OE,LOW);
          digitalWrite(WR,HIGH);
          break;
        case PAG_SOREN:
          digitalWrite(PAGEMODE0,0);  
          digitalWrite(PAGEMODE1,1);    
          digitalWrite(PAGEMODE2,0);  
          DDRA = B00000000;
          DDRK = B00000000;
          DDRF = B00000000;
          PORTA = 0;
          PORTK = 0;
          PORTF = 0;
          digitalWrite(OE,LOW);
          digitalWrite(WR,HIGH);
          break;
         case PAG_XROM:
          digitalWrite(PAGEMODE0,1);  
          digitalWrite(PAGEMODE1,0);    
          digitalWrite(PAGEMODE2,1);  
          DDRA = B00000000;
          DDRK = B00000000;
          DDRF = B00000000;
          PORTA = 0;
          PORTK = 0;
          PORTF = 0;
          digitalWrite(OE,LOW);
          digitalWrite(WR,HIGH);
          break;
        case PAG_TEST:
          digitalWrite(PAGEMODE0,0);  
          digitalWrite(PAGEMODE1,1);    
          digitalWrite(PAGEMODE2,1);  
          DDRA = B00000000;
          DDRK = B00000000;
          DDRF = B00000000;
          PORTA = 0;
          PORTK = 0;
          PORTF = 0;
          digitalWrite(OE,LOW);
          digitalWrite(WR,HIGH);
          break;
      }
  } else if (mode==MODE_SENDING_GAME) {
        digitalWrite(PAGEMODE0,0);  
        digitalWrite(PAGEMODE1,0);    
        digitalWrite(PAGEMODE2,1);  
        DDRA = B00000000;
        DDRK = B00000000;
        DDRF = B00000000;
        PORTA = 0;
        PORTK = 0;
        PORTF = 0;
        digitalWrite(OE,LOW);
        digitalWrite(WR,HIGH);
  }
#endif
}

void RAM_write(unsigned int addr, unsigned char data){
  DDRA = B11111111;
  DDRK = B01111111;
  DDRF = B11111111;
  PORTA = data;
  PORTF = addr % 256;
  PORTK = addr / 256;
  digitalWrite(OE,HIGH);
  digitalWrite(WR,LOW);
//  waitforever();
  
//  digitalWrite(CE,LOW);
// delay(1);
//  digitalWrite(CE,HIGH);
  for (int i = 0; i<RAM_delay;i++) digitalWrite(WR,LOW); //delay for write
  
  digitalWrite(OE,LOW);
  digitalWrite(WR,HIGH);  
  if (millis()%64 < 32) 
    ram_led_on();
  else
    ram_led_off();
}

unsigned char RAM_read(unsigned int addr){
  
  unsigned char dato;
  
  DDRA = B00000000;
  DDRK = B01111111;
  DDRF = B11111111;
  PORTF = addr % 256;
  PORTK = addr / 256;
  digitalWrite(OE,LOW);
  digitalWrite(WR,HIGH);
//  digitalWrite(CE,LOW);
//  delay(1);
  dato = PINA; 
//  digitalWrite(CE,HIGH);
  digitalWrite(OE,HIGH);  
  if (millis()%64 < 32) 
    ram_led_on();
  else
    ram_led_off();
  return dato;
}

unsigned char BUS_read(unsigned int addr){
  unsigned char dato;
  digitalWrite(WR,HIGH);
  DDRA = B00000000;
  DDRK = B01111111;
  DDRF = B11111111;
  PORTF = addr % 256;
  PORTK = addr / 256;
  dato = PINA;
  dato = PINA;
  dato = PINA;
  return dato;
}

void sendblock(int destination, int blocksize){
  int j;

  for (j=0; j<blocksize;j++){
    RAM_write(destination+j, block[j]);
  }
}
