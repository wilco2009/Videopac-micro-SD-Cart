void take_money_display_screen(){
}

void take_money_manage_controls(){
  
}

void take_money_main(){
  do {
    fin = false;
    score1 = 0;
    take_money_display_screen();
    sonido_select_game_2();
    delay(1000);
    sacando = millis();
    do {
      take_money_display_screen();
      take_money_manage_controls();
    } while (!fin);
  
    u8g2.drawStr(30,35,str_GAMEOVER);
    u8g2.sendBuffer(); 
    delay(500);
    while ((digitalRead(butESC)==HIGH) && (digitalRead(butENTER)==HIGH));
  } while (digitalRead(butESC)==HIGH);  
  while((digitalRead(butENTER)==LOW) || (digitalRead(butESC)==LOW));
  
}
