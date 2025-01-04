void get_game_data(unsigned long int CRC32);

void test_dir(char* dir){
// SD card chip select pin.
const uint8_t SD_CS_PIN = SS;

#ifdef sdfat
SdFat sd;
#endif

SdFile file;
SdFile dirFile;

// Number of files found.
uint16_t n = 0;

// Max of ten files since files are selected with a single digit.
const uint16_t nMax = 10;

// Position of file's directory entry.
uint16_t dirIndex[nMax];
  
  // Print the location of some test files.
  Serial.println(F("\r\n"
                   "You can use test files located in\r\n"
                   "SdFat/examples/LongFileName/testFiles"));

  // Initialize at the highest speed supported by the board that is
  // not over 50 MHz. Try a lower speed if SPI errors occur.
//  if (!sd.begin(SD_CS_PIN, SD_SCK_MHZ(50))) {
//    sd.initErrorHalt();
//  }
  Serial.print(F("FreeStack: "));
  Serial.println(FreeStack());
  Serial.println();

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

  while (n < nMax && file.openNext(&dirFile, O_READ)) {

    // Skip directories and hidden files.
    if (!file.isSubDir() && !file.isHidden()) {

      // Save dirIndex of file in directory.
      dirIndex[n] = file.dirIndex();

      // Print the file number and name.
      Serial.print(n++);
      Serial.write(' ');
      file.printName(&Serial);
      Serial.println();
    }
    file.close();
  }
}

void openDirectory(SdFile *dirFile, char* dir_name){
  if (SDOK) {
//    Serial.println("OK");
    if (dirFile->isOpen())
      dirFile->close();
  
    if (!dirFile->open(dir_name, O_READ)){
      Serial.print("open dir "); 
      Serial.print(dir_name);
      Serial.println(" failed");
    } else {
      Serial.print("open dir "); 
      Serial.print(dir_name);
      Serial.println(" successful");
    }
  }
}

void close_directory(void){
  if (SDOK) 
    dirFile.close();  
}

//void open_cache_file(void){
//  if (SDOK) {
//    if (!cache.open(&dirFile, strCacheFName, O_CREAT | O_RDWR)) {
//      Serial.print("Error con el archivo de caché $$$$$$$$.$$$");
//    }
//  }
//}
//
void openCache_file(SdFile *dirFile){
#ifdef SDFAT
  if (SDOK) {
    if (cache.isOpen()) cache.close();
    if (!cache.open(dirFile, strCacheFName, O_CREAT | O_RDWR)) {
      Serial.print("Error con el archivo de caché $$$$$$$$.$$$");
      show_message("CACHE ERROR");
    }
  }
#else
  if (SDOK) {
    if (cache.isOpen()) cache.close();
    cache = SD.open(dirFile, strCacheFName, FILE_WRITE);
    if (!cache) {
      Serial.print("Error con el archivo de caché $$$$$$$$.$$$");
      show_message("CACHE ERROR");
    }
  }
#endif
}

void open_description_index(SdFile *dirFile){
#ifdef SDFAT
  if (SDOK) {
    if (descindex.isOpen()) descindex.close();
    if (!descindex.open(dirFile, "description.idx", O_CREAT | O_RDWR)) {
      Serial.print("Error con el archivo description.idx");
    }
  }
#else
  if (SDOK) {
    if (descindex.isOpen()) descindex.close();
    descindex = SD.open(dirFile, "description.idx", FILE_WRITE)
    if (!descindex) {
      Serial.print("Error con el archivo description.idx");
    }
  }
#endif
}

boolean file_exists(char* dir_name, char* FName){
  SdFile dirFile;
  openDirectory(&dirFile, dir_name);
  boolean found = dirFile.exists(FName);
  dirFile.close();
  return found;
}


int get_game_data_pos(unsigned long int CRC32){
  long int len;
  long int pos;
  bool found = false;
  unsigned long int CRC;
  char sCRC[10];
  char sCRC32[10];
  CRC = CRC32;
#ifdef SDFAT
  if (!CRCFile.open(&dirFile, "gamelist.idx", O_READ)) {
    Serial.println("Error con el archivo gamelist.idx");
    return;
  }
#else
  CRCFile = SD.open(&dirFile, "gamelist.idx", FILE_READ);
  if (!CRCFile) {
    Serial.println("Error con el archivo gamelist.idx");
    return;
  }
#endif
  CRCFile.seekSet(0);
  
  len = 0;
  found = false;
  do {
    len = CRCFile.read(&CRC, sizeof(CRC));
    len = CRCFile.read(&pos, sizeof(pos));
    if (CRC==CRC32) {
      found = true;
    }
  } while ((len > 0) && (found==false));

  CRCFile.close();
  return pos;
}


boolean get_description_index_item(int i, int* descitem){
  int j;
  descindex.seekSet(sizeof(int)*i);
  j = descindex.read(descitem,sizeof(int));
  if (millis()%64 < 32) 
    sd_led_on();
  else
    sd_led_off();
  if (j<0) return false;
  else return true;
}

boolean put_description_index_item(int i, int* descitem){
  descindex.seekSet(sizeof(int)*i);
  int k = descindex.write(descitem,sizeof(int));
  if (millis()%64 < 32) 
    sd_led_on();
  else
    sd_led_off();
  if (k<0) return false;
  else return true;
}

char* get_cache_str(int i, char* str){
  cache.seekSet(MAX_FILENAME_LEN*i);
  int j;
  j = cache.read(str,MAX_FILENAME_LEN);
  if (millis()%64 < 32) 
    sd_led_on();
  else
    sd_led_off();
  if (j<0) return "";
  else return str;
}

int put_cache_str(int i, char* str){
  cache.seekSet(MAX_FILENAME_LEN*i);
  int k = cache.write(str,MAX_FILENAME_LEN);
  if (millis()%64 < 32) 
    sd_led_on();
  else
    sd_led_off();
  return k;
}

int str_cmp(char* s1, char* s2){
  char a, b;
  int i = 0;
  while ((s1[i]!=0) && (b=s2[i]!=0) & (s1[i]==s2[i])){
    i++;
  }
  a=toupper(s1[i]);
  b=toupper(s2[i]);
  if (a > b) return 1;
  else if (a == b) return 0;
  else return -1;
}

void insertionSort(int n)  
{  
    int i, j;  
    int pos1, pos2;
    boolean fin;
    for (i = 1; i < n; i++) 
    {  
        get_cache_str(i, str1);
//        get_description_index_item(i,pos1);  
        j = i - 1;  
  
        /* Move elements of arr[0..i-1], that are  
        greater than key, to one position ahead  
        of their current position */
        fin = false;
        do  
        {  
          get_cache_str(j, str2);
//          get_description_index_item(j,pos2);  
          if (j >= 0 && (str_cmp(str2,str1)>0)){
            put_cache_str(j+1,str2);
//            put_description_index_item(j+1,pos2);  
            j = j - 1;
          } else fin = true;  
        } while (!fin);
        put_cache_str(j+1,str1);
//        put_description_index_item(j+1,pos1);  

    }  
}  

void quicksort(int first,int last){
  int i, j, pivot;
  int k;
  boolean fin;
  
  if(first<last){
    pivot=first;
    i=first;
    j=last;

    while(i<j){
      do{
        get_cache_str(i, str1);
        get_cache_str(pivot,str2);
        k=str_cmp(str1, str2);
        if ((k <= 0)&&(i<last)){
          fin = false;
          i++;
        } else { fin = true;}
      } while (!fin);
      do {
        k=str_cmp(get_cache_str(j,str1),get_cache_str(pivot,str2));
        if (k>0) {
          fin = false;
          j--;
        } else {
          fin = true;
        }
      } while(!fin);
      if(i<j){
        get_cache_str(i,str2);
        get_cache_str(j,str1);
        put_cache_str(i,str1);
        put_cache_str(j,str2);
      }
    }

    
    get_cache_str(pivot,str2);
    get_cache_str(j,str1);
    put_cache_str(pivot,str1);
    put_cache_str(j,str2);
    quicksort(first,j-1);
    quicksort(j+1,last);
  
  }
}

void ordena_cache(void){
  int last;
  show_message("Sorting directory.");
  openDirectory(&dirFile, dir_name);
  openCache_file(&dirFile);
//  open_description_index(&dirFile);
  last = cache.fileSize()/MAX_FILENAME_LEN-1;
  Serial.print("Cache files: ");
  Serial.println(last);
//  quicksort(0,last);
  insertionSort(cache.fileSize()/MAX_FILENAME_LEN);
  cache.close();
  dirFile.close(); 
//  descindex.close(); 
  sd_led_off();
}

void make_description_index(void){
  boolean fin;
  unsigned long int CRC32;
  int i;
  
  show_message("making desc. index.");
  openDirectory(&dirFile, dir_name);
  openCache_file(&dirFile);
  open_description_index(&dirFile);
  int n = cache.fileSize()/MAX_FILENAME_LEN-1;  
  for (i = 0; i < n; i++) 
  {  
    get_cache_str(i,str1);
    CRC32 = CalcCRC32(str1);
    int pos = get_game_data_pos(CRC32);
    put_description_index_item(i,pos);
//  char sCRC[10];
//  sprintf(sCRC, "%08lX", CRC32);
//  Serial.print(i);
//  Serial.print(": ");
//  Serial.println(sCRC);
    
  }
  cache.close();
  dirFile.close();  
  descindex.close();
  sd_led_off();
}


void SD_Init(void){
  if (!SDOK) {
    #ifdef SDFAT
    SDOK = sd.begin(53);
    #else
    SDOK = sd.begin(SD_ChipSelectPin);   
    #endif
    if (!SDOK) {
      Serial.println("initialization failed!");
      show_message(msgSDNOTOK);
      waitkey();
      return;
    } else
      Serial.println("initialization done.");
  }
}


const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void printCache(void){
  cache.seekSet(0);
  while (cache.read(file_name,MAX_FILENAME_LEN)>0) {
    Serial.println(file_name);
  }
}

bool parseSection(char* str1, char* section){
  int s = 0;
  int e = 0;
  bool found = false;
  if (strlen(str1)==0) return false;
  for (int i=0;i<strlen(str1);i++){
    if (str1[i]=='[') {
      s = i+1;
    } else
    if (str1[i]==']') {
      e = i-1;
      found = true;
      break;
    } else
    if ((s==0) & (str1[i]!=' ')) {
      found = false;
      break;
    }
  }
  if ((s <= e) & (found==true)) {
    strmid(section, str1, s, e-s+1);
    return true;
  } else return false;
}

bool parse_value(char* s, char* sname, char* svalue){
  bool reading_name = 1;
  int sn = -1;
  int en = 0;
  int sv = -1;
  int ev = 0;
  bool found = false;
//  Serial.print("SSSS:");
//  Serial.println(s);
  strcpy(sname, "");
  strcpy(svalue, "");
  for (int i=0;i<strlen(s);i++){
    if (reading_name==1){
      if ((s[i]=='[') & (reading_name==1)) {
        return true;
      } else {
        if (s[i]!=' ') {
          if (sn < 0) sn = i;
          if (s[i]=='='){
            en = i-1;
            sv = i+1;
            reading_name = 0;
            found = true;
          }
        }
      } 
    }
  }
  if (found==true) {
    ev = strlen(s)-1;
    int ln = en-sn+1;
//    int lv = ev-sv+1;
    int lv = ev-sv;
    strmid(sname, s, sn, ln);
    strmid(svalue, s, sv, lv);
    upStr(sname);
  }
  return false;
}

void get_game_data(unsigned long int CRC32){
  long int len;
  long int pos;
  bool found = false;
  unsigned long int CRC;
  char sCRC[10];
  char sCRC32[10];
  strcpy(game_name, "NO INFO");
  strcpy(game_brand,"NO INFO");
  strcpy(game_year,"NO INFO");
  strcpy(game_variant, "NO INFO");
  game_pagging = 0;
  CRC = CRC32;
//  sprintf(sCRC, "%08lX", CRC32);
//  Serial.print("Searching for ");
//  Serial.print(sCRC);
//  Serial.print(" = ");
//  Serial.println(CRC32);

#ifdef SDFAT
  if (!CRCFile.open(&dirFile, "gamelist.idx", O_READ)) {
    Serial.println("Error con el archivo gamelist.idx");
    return;
  }
  CRCFile.seekSet(0);
  
  if (!dataFile.open(&dirFile, "gamelist.dat", O_READ)) {
    Serial.println("Error con el archivo gamelist.dat");
    return;
  }
#else
  CRCFile = SD.open(&dirFile, "gamelist.idx", FILE_READ);
  if (!CRCFile) {
    Serial.println("Error con el archivo gamelist.idx");
    return;
  }
  CRCFile.seekSet(0);
  dataFile = SD.open(&dirFile, "gamelist.dat", FILE_READ);
  if (!dataFile) {
    Serial.println("Error con el archivo gamelist.dat");
    return;
  }
#endif
  dataFile.seekSet(0);

  len = 0;
  found = false;
  do {
    len = CRCFile.read(&CRC, sizeof(CRC));
    len = CRCFile.read(&pos, sizeof(pos));
//    sprintf(sCRC32, "%08lX", CRC32);
//    sprintf(sCRC, "%08lX", CRC);
//    Serial.print("readed ");
//    Serial.print(CRC);
//    Serial.print(" - ");
//    Serial.print(sCRC);
//    Serial.print(" - searched ");
//    Serial.print(CRC32);
//    Serial.print(" - ");
//    Serial.println(sCRC32);
    if (CRC==CRC32) {
      found = true;
//      Serial.print("found ");
//      Serial.println(sCRC);
    }
  } while ((len > 0) && (found==false));

  if (found) {
    dataFile.seekSet(pos);
    dataFile.read(game_name, GAME_NAME_LEN);
    dataFile.read(game_brand, GAME_BRAND_LEN);
    dataFile.read(game_year, GAME_YEAR_LEN);
    dataFile.read(game_variant, GAME_VARIANT_LEN);
    dataFile.read(&game_pagging, sizeof(game_pagging));
//    Serial.print("NAME=");
//    Serial.println(game_name);
//    Serial.print("BRAND=");
//    Serial.println(game_brand);
//    Serial.print("YEAR=");
//    Serial.println(game_year);
//    Serial.print("VARIANT=");
//    Serial.println(game_variant);
//    Serial.print("PAGGING=");
//    Serial.println(game_pagging);
//    Serial.println("-----------------");

  }
    
  dataFile.close();
  CRCFile.close();
}

unsigned long int str2hex(char* s){
  unsigned long int value = 0;
  byte len = strlen(s);
  byte d;
  unsigned long int p = 1;
  for (int i=7; i>=0; i--){
    if (s[i]<'A') d = s[i] - '0';
    else d = s[i] - 'A' + 10;
//    Serial.print(s[i]);
//    Serial.print(":");
//    Serial.print(i);
//    Serial.print(":");
//    Serial.print(p);
//    Serial.print(":");
//    Serial.print(d);
//    Serial.print(":");
//    Serial.println(d*p);
    value += (unsigned long int) d*p;
    p*=16;
  }
//  Serial.print("--");
//  Serial.println(value);
  return value;
}

void rebuild_ini_file(void){

  unsigned long int CRC;
  unsigned long int pos;
  int len;
  char section[30];
  char sname[30];
  char svalue[100];
  char sCRC[10];
  bool found;
  
#ifdef SDFAT
  if (!CRCFile.open(&dirFile, "gamelist.idx", O_CREAT | O_RDWR)) {
    Serial.println("Error con el archivo gamelist.idx");
    return;
  }
  CRCFile.seekSet(0);

  if (!dataFile.open(&dirFile, "gamelist.dat", O_CREAT | O_RDWR)) {
    Serial.println("Error con el archivo gamelist.dat");
    return;
  }

  dataFile.seekSet(0);
  if (!iniFile.open(&dirFile, "gamelist.ini", O_READ)) {
    Serial.println("Error con el archivo gamelist.ini");
    return;
  }
#else
  CRCFile = SD.open(&dirFile, "gamelist.idx", FILE_WRITE)
  if (!CRCFile) {
    Serial.println("Error con el archivo gamelist.idx");
    return;
  }
  CRCFile.seekSet(0);

  dataFile = SD.open(&dirFile, "gamelist.dat", FILE_WRITE);
  if (!dataFile) {
    Serial.println("Error con el archivo gamelist.dat");
    return;
  }
  dataFile.seekSet(0);
  
  iniFile = SD.open(&dirFile, "gamelist.ini", FILE_READ);
  if (!iniFile) {
    Serial.println("Error con el archivo gamelist.ini");
    return;
  }
#endif
  iniFile.seekSet(0);
  //dataFile.timestamp(&iniFile);
  //CRCFile.timestamp(&iniFile);
//  sprintf(sCRC, "%08lX", CRC32);
  found = false;
  len = iniFile.fgets(str1, MAX_FILENAME_LEN, "\n");
  do {
    if (millis()%64 < 32) 
      sd_led_on();
    else
      sd_led_off();
    strcpy(game_name, "NO INFO");
    strcpy(game_brand,"NO INFO");
    strcpy(game_year,"NO INFO");
    strcpy(game_variant, "NO INFO");
    game_pagging = 0;
    game_CRC = 0;   
    do {
      found = parseSection(str1, section);
      if (found){
//        Serial.print("SECTION:");
//        Serial.println(section);
//        Serial.println(str1);
      } else {
//        Serial.print("------>");
//        Serial.println(str1);
        len = iniFile.fgets(str1, MAX_FILENAME_LEN, "\n");
      }
    } while ((len > 0) && (found==false));
    CRC = str2hex(section);
    if (found) {
      found = false;
      do {
        len = iniFile.fgets(str1, MAX_FILENAME_LEN, "\n");
//        Serial.print("STR:");
//        Serial.println(str1);
        found = parse_value(str1, sname, svalue); 
//        Serial.print("SNAME:");
//        Serial.println(sname);
        if (strcmp(sname,"NAME")==0) strcpy(game_name, svalue);
        if (strcmp(sname,"MANUF")==0) strcpy(game_brand, svalue);
        if (strcmp(sname,"YEAR")==0) strcpy(game_year, svalue);
        if (strcmp(sname,"VARIANT")==0) strcpy(game_variant, svalue);
        if (strcmp(sname,"PAGGING")==0) {
          game_pagging = string2pagging(svalue);
        }
      } while ((len>0) && (found==false));
      CRCFile.write(&CRC, sizeof(CRC));
      pos = dataFile.curPosition ();
      CRCFile.write(&pos, sizeof(pos));
//      Serial.println(CRC);
//      Serial.print("NAME=");
//      Serial.println(game_name);
//      Serial.print("BRAND=");
//      Serial.println(game_brand);
//      Serial.print("YEAR=");
//      Serial.println(game_year);
//      Serial.print("VARIANT=");
//      Serial.println(game_variant);
//      Serial.print("PAGGING=");
//      Serial.println(game_pagging);
//      Serial.println("-----------------");

      dataFile.write(game_name, GAME_NAME_LEN);
      dataFile.write(game_brand, GAME_BRAND_LEN);
      dataFile.write(game_year, GAME_YEAR_LEN);
      dataFile.write(game_variant, GAME_VARIANT_LEN);
      dataFile.write(game_pagging);
    }
  } while (len > 0);
//  Serial.println("FIN");
  iniFile.close();
  dataFile.close();
  CRCFile.close();
  sd_led_off();
}

void readDirectory(char* dir_name) {
  char* ext;
  SdFile cacheDir;
  if (!SDOK) {
    show_message(msgSDNOTOK);
    return;
  }

  openDirectory(&dirFile, dir_name);
  openDirectory(&cacheDir, dir_name);
  openCache_file(&cacheDir);
//  test_dir("/");


  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_6x13_mf); // choose a suitable font
  u8g2.drawStr(1,15, "Reading directory");
  u8g2.drawStr(1,35, dir_name);
  printVolt(0,63);
  u8g2.sendBuffer(); // transfer internal memory to the display  

  num_files = 0;
  num_files_nodir = 0;
  if (cache.isOpen()) Serial.println("Cache file opened");
  cache.seekSet(0);
  if (!dirFile.isRoot()){
    num_files++;
    cache.write("+..", MAX_FILENAME_LEN);
  }
  while (file.openNext(&dirFile, O_READ)) {
    if (millis()%64 < 32) 
      sd_led_on();
    else
      sd_led_off();
    file.getName(file_name, MAX_FILENAME_LEN);
    ext = get_filename_ext(file_name);
    // Skip directories and hidden files.
    upStr(ext);
    if (!file.isSubDir() && !file.isHidden() && strcmp(ext,"BIN")==0) {
      cache.write(file_name, MAX_FILENAME_LEN);
      num_files++;
      num_files_nodir++;
    } else if (file.isSubDir() && !file.isHidden()) {
      strcpy(str1, "+");
      strcat(str1, file_name);
      cache.write(str1, MAX_FILENAME_LEN);
      num_files++;      
    }
    file.close();
  }
  sd_led_off();
  Serial.println(cache.curPosition());
  cache.truncate(cache.curPosition());
  dirFile.close();
  cacheDir.close();

//  make_description_index();
  
  if (sorted)
    ordena_cache();

//  Serial.print(num_files);
//  Serial.println(" files readed.");
 
}

void read_1K_block(char* file_name, int filepos, int ram_addr, int blocksize){

    char s[19] = "0K..4K..8K.12K.16K";
    int fsize = file.fileSize() / 1024;
    file.seekSet(filepos);
    for (int j=0; j<1024; j+=blocksize){
      u8g2.clearBuffer();          // clear the internal memory
//      u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
      u8g2.setFont(u8g2_font_profont12_mf); // choose a suitable font
      sprintf_P(str1, PSTR("reading file: %dK"), fsize);
      u8g2.drawStr(0,15, str1);
      u8g2.drawStr(0,31,file_name);
      int addr_r = j+ram_addr; 
      int w = u8g2.getStrWidth(s);
      long int pr = w*((addr_r/1024)+1)/16;
      long int pf = w*((filepos/1024)+1)/16;
      u8g2.drawStr(10,47, s); 
//      u8g2.drawBox(10,49, pr,5);
      u8g2.drawBox(10,56, pf,5);
      sd_led_on();

      if (file.read(block, BLOCK_SIZE)>0) {
//        Serial.print("Block readed: ");
      } else {
        Serial.print("Block read error");
      }
//      Serial.print(j*blocksize+filepos);
//      Serial.print(", ");
//      Serial.println(addr_r);
      
      sd_led_off();
      int inicio = millis();
      sendblock(addr_r, BLOCK_SIZE);
//      Serial.println(millis()-inicio);
      ram_led_off();
      printVolt(0,63);
      u8g2.sendBuffer(); // transfer internal memory to the display         
    }
}

void read_file_to_ram(char* file_name, int pagging){

#ifdef SDFAT 
    openDirectory(&dirFile, dir_name);
    if (!file.open(&dirFile, file_name, O_READ)) {
      Serial.print("Error buscando el archivo ");
      Serial.println(file_name);
      file.close();
      return; 
    } else {
      Serial.print("File opened: ");
      Serial.println(file_name);      
    }
#else
    strcat(str1,dir_name,file_name);
    file = SD.open(&dirFile, str1, FILE_READ)
 
    if (!file) {
      Serial.print("Error buscando el archivo ");
      Serial.println(file_name);
      file.close();
      return; 
    } else {
      Serial.print("File opened: ");
      Serial.println(file_name);      
    }

#endif
  
    int fsize = file.fileSize();


#ifdef ATARI
    Serial.println("TARGET=ATARI");
    for (unsigned int i=0;i<(fsize/1024);i++){
      Serial.println(i*1024);
      read_1K_block(file_name, i*1024, 2048*0+1024*i, BLOCK_SIZE);
      read_1K_block(file_name, i*1024, 2048*1+1024*i, BLOCK_SIZE);
      read_1K_block(file_name, i*1024, 2048*2+1024*i, BLOCK_SIZE);
      read_1K_block(file_name, i*1024, 2048*3+1024*i, BLOCK_SIZE);
    }
//    for (unsigned int i=0;i<(fsize/1024);i++){
//      read_1K_block(file_name, i*1024, 2048+1024*i, BLOCK_SIZE);
//    }
//    for (unsigned int i=0;i<(fsize/1024);i++){
//      read_1K_block(file_name, i*1024, 3072+1024*i, BLOCK_SIZE);
//    }
//    for (unsigned int i=0;i<(fsize/1024);i++){
//      read_1K_block(file_name, i*1024, 4096-fsize+1024*i, BLOCK_SIZE);
//    }
#endif
#ifdef VIDEOPAC
    Serial.print("TARGET=VIDEOPAC PAG=");
    Serial.println(pagging);
    switch (pagging){
      case PAG_P10_P11:
      case PAG_SELECT_GAME:
        for (unsigned int i=0;i<(fsize/1024);i++){
          read_1K_block(file_name, i*1024, 8192-fsize+1024*i, BLOCK_SIZE);
        }
        break;
      case PAG_XROM:
        for (unsigned int i=0;i<(fsize/1024);i++){
          Serial.println(i);
          read_1K_block(file_name, i*1024, 1024*i, BLOCK_SIZE);
        }
        break;
      case PAG_VP_PLUS:
        if (fsize==16384){
          for (unsigned int i=0;i<16;i++){
            read_1K_block(file_name, i*1024, 1024*i, BLOCK_SIZE);
          }
        } else {
          for (unsigned int i=0;i<12;i++){
            read_1K_block(file_name, i*1024, 1024*i+4096, BLOCK_SIZE);
          }
        }
        break;
      case PAG_SOREN:
          for (int i=0;i<(fsize/3072);i++){
            read_1K_block(file_name, i*3072+0000, i*4096+1024, BLOCK_SIZE);
            read_1K_block(file_name, i*3072+1024, i*4096+2048, BLOCK_SIZE);
            read_1K_block(file_name, i*3072+2048, i*4096+3072, BLOCK_SIZE);
          }
      break;
    }
#endif

    file.close();
}

void get_filename_from_cache(int pos, char * file_name){
  int nfiles = 0;
          sprintf_P(str1,PSTR("%d"),pos);
          show_message(str1);
  openCache_file(&dirFile);
  cache.seekSet(0);

  do {
    int len = cache.read(file_name,MAX_FILENAME_LEN);
    if (len>0){
      if (file_name[0] != '+') {
        nfiles++;
//          sprintf(str1,"%d",pos);
//          show_message(str1);
      } 
    } //z else show_message("CACHE ERROR");
  } while (nfiles < pos);
//  Serial.print("NFILES=");
//  Serial.println(nfiles);
  cache.close();  
}

void generate_selectgame(char* dir, int startfile, bool rebuild){

  const int block_addr[] = 
  {
  0x1800, 0x1900, 0x1A00, 0x1B00, 0x1C00, 0x1D00, 0x1E00, 0x1F00,
  0x1000, 0x1100, 0x1200, 0x1300, 0x1400, 0x1500, 0x1600, 0x1700, 
  0x0800, 0x0900, 0x0A00, 0x0B00, 0x0C00, 0x0D00, 0x0E00, 0x0F00, 
  0x0000, 0x0100, 0x0200, 0x0300, 0x0400, 0x0500, 0x0600, 0x0700
  };
  
  SdFile source_file;
  SdFile target_file;
  SdFile sysDir_file;
  int i;
  int x;
  unsigned long int pos;
  bool eof = false;
  byte n_files=0;
  byte n=0;
  int error;

  boolean direct_to_memory;

  direct_to_memory = !rebuild;

  if ((rebuild==true) || !file_exists(dir, strCacheFName)){
    readDirectory(dir);
    dirFile.close();
  }


  if (!sysDir_file.open("/SYS", O_READ))
    Serial.println("open dir /SYS failed");
  else
    Serial.println("open dir /SYS successful");
  if (!source_file.open(&sysDir_file, "selectgame.bin", O_READ)) {
    Serial.println("Error openning /SYS/selectgame.bin");
  }

  if (!direct_to_memory) {
    /////////////////// copy file ////////////////////////////////
    openDirectory(&dirFile, dir_name);
    if (!target_file.open(&dirFile, "selectgame.bin", O_CREAT | O_RDWR)) {
      Serial.print("Error creating file ");
      Serial.print(dir);
      Serial.println("selectgame.bin");
    }
      
    if (rebuild==true) {
      source_file.seekSet(0);
      target_file.seekSet(0);
      for (i=0;i<32; i++){
        sd_led_on();
        if (source_file.read(block, BLOCK_SIZE)>0) {
    //      Serial.println("Block readed: ");
        } else {
          Serial.print("Block read error");
          Serial.println(i*BLOCK_SIZE);
        }
        sd_led_off();
//        sprintf(str1, "%04X ", i*BLOCK_SIZE);
//        Serial.println(str1);
    //    dump_block();
        error = target_file.write(block, BLOCK_SIZE);
        if (error < BLOCK_SIZE) {
          Serial.print("write error in target file :");
          Serial.print(error);
          Serial.print(" : ");
          Serial.println(i*BLOCK_SIZE);
        } // else Serial.println(i*BLOCK_SIZE);
      }
    }
  } 

  set_mode(MODE_SENDING_GAME, game_pagging);

  if (cache.isOpen())
    cache.close();

  openDirectory(&dirFile, dir_name);
  openCache_file(&dirFile);

  //////////////  MODIFY FILE WITH FILE NAMES ////////////////
  cache.seekSet(0);
  i=0;
  while ((i<startfile) /*|| (x<=0)*/){
    x = cache.read(file_name, MAX_FILENAME_LEN);
    Serial.print(i);
    Serial.print(F(":"));
    Serial.println(file_name);
    if ((x>0) && (file_name[i]!='+')) i++;
  if (millis()%64 < 32) 
    sd_led_on();
  else
    sd_led_off();
  }
  
  // customize file
  for (i=4;i<32;i++) {                         // read files (7K=28*256 bytes)
    sd_led_on();
    if ((block_addr[i] % 0x800) != 0){
      
      error = source_file.seekSet(block_addr[i]);
      if (error==0) {
        Serial.print(F("Seek error in source file :"));
        Serial.println(block_addr[i]);
      }
      if (!direct_to_memory) {
        error = target_file.seekSet(block_addr[i]);
        if (error==0) {
          Serial.print(F("Seek error in target file :"));
          Serial.println(block_addr[i]);
        }
      }  
//      Serial.print(F("BLOCK: "));
//      Serial.println(block_addr[i]);
      if (source_file.read(block, BLOCK_SIZE)>0) {
  //      Serial.print(block_addr[i]);
  //      Serial.println(F(" block readed: "));
      } else {
        Serial.print(block_addr[i]);
        Serial.println(F(" Block read error"));
      }
      sd_led_off();

//      Serial.print(F("-----------------"));
      n=0;
      eof = false;
      while ((n < 8) /*&& (eof==false)*/){
        if (!eof){
          x = cache.read(file_name, MAX_FILENAME_LEN);
          if (x<=0) eof = true;
        }
        if (eof) {
          file_name[0] = '\0';
        }
//        Serial.print(F("Cache="));
//        Serial.print(file_name);
//        Serial.print(F(": "));
//        Serial.println(x);
        if (file_name[0] != '+') {
//            Serial.println(file_name);
          pos = 0x80+n*16;
//            Serial.print(F("Offset: "));
//            Serial.println(pos);
          pos = block+pos;
          convert_ascii_file_to_VP(pos, file_name);
          n++; 
          if (!eof) n_files++;
        }
      }

      if (direct_to_memory) {
        sendblock(block_addr[i], BLOCK_SIZE);
      }
//      else {
//        error = target_file.write(block, BLOCK_SIZE);
//        if (error < BLOCK_SIZE) {
//          Serial.print(F("write error in target file :"));
//          Serial.print(error);
//          Serial.print(F(" : "));
//          Serial.println(block_addr[i]);
//        }
//      }
    }
  }
  source_file.close();
  if (direct_to_memory) {
    RAM_write(0x1aef, n_files);
  } else {
    target_file.seekSet(0x1aef);
    target_file.write(&n_files,1);
  //  Serial.println(n_files);
    target_file.close();
    sysDir_file.close();  
  }
  dirFile.close();  
  ram_led_off();
  sd_led_off();
}

void launch_game(char* file_name, int startfile, boolean rebuild){
  unsigned long int CRC32 = CalcCRC32(file_name);
  show_message(file_name);          
  get_game_data(CRC32);
    show_message("LAUNCH");          

  if (strcmp(file_name,"SELECTGAME.BIN")==0) {
    game_pagging = PAG_SELECT_GAME;
    unsigned long int inicio = millis();

    show_message("READING FILENAMES");

    if (rebuild){
     generate_selectgame(dir_name, startfile, rebuild);
    }
   openDirectory(&dirFile, dir_name);
  }
  set_mode(MODE_SENDING_GAME, game_pagging);
  if (rebuild || strcmp(file_name,"SELECTGAME.BIN")!=0)
    read_file_to_ram(file_name, game_pagging);
  if (strcmp(file_name,"SELECTGAME.BIN")==0){
    generate_selectgame(dir_name, startfile, false);
    Serial.println(F("Names updated"));
  }

    
  set_mode(MODE_PLAYING, 3);
  set_mode(MODE_PLAYING, game_pagging);
  show_ready_to_play();
  sonido_select_game();      
}

void run_game(char* fname){
  boolean finished = false;
  boolean rebuild = autorebuild;
  
  upStr(fname);
  int startfile = 0;
  do {
    launch_game(fname, startfile, rebuild);
    rebuild = false;
    if (strcmp(fname,"SELECTGAME.BIN")==0){
        
        int dato = 0;
        delay(500);
        while((digitalRead(butESC)==HIGH) && (dato!=254)){ // se envia un 254 para indicar que ya se está dentro del menú
          dato = PINA; 
          if (digitalRead(butENTER)==LOW) dato = 254;
          while((digitalRead(butESC)==LOW)||(digitalRead(butENTER)==LOW));
          show_ready_to_play();        
        }

        while (digitalRead(butENTER)==LOW);

      
        while((digitalRead(butESC)==HIGH) && ((dato<1) || (dato>230))){
          dato = PINA; 
          if (digitalRead(butLEFT)==LOW) dato =221;
          if (digitalRead(butRIGHT)==LOW) dato =220;
          if (digitalRead(butENTER)==LOW) dato =1;
//          sprintf(str1,"%d",dato);
//          show_message(str1);
          show_select_game(false);
          
         }


        if (digitalRead(butESC)==LOW) {
          while((digitalRead(butESC)==LOW)||(digitalRead(butENTER)==LOW));
          return;
        }

//        Serial.print(F("num_files:"));
//        Serial.println(num_files_nodir);
//        Serial.print(F("dato:"));
//        Serial.println(dato);
//        Serial.print(F("start:"));
//        Serial.println(startfile);
        if (dato == 221) {
          if (startfile > 0) startfile -= 200;
          else startfile = (num_files_nodir / 200)*200;
        }
        if (dato == 220) {
          if (startfile+200 < num_files_nodir) startfile += 200;
          else startfile = 0;
        }
//        Serial.print(F("start:"));
//        Serial.println(startfile);
        if (dato < 220) {
          openDirectory(&dirFile, dir_name);
          get_filename_from_cache(startfile+dato, file_name);  
          show_message(file_name);          
          finished = true;
          strcpy(file_loaded, file_name);
          launch_game(file_name, startfile, false);
        }
        else {
          strcpy(file_name, "SELECTGAME.BIN");
          finished = false;
        }
    } else finished = true;
  } while (!finished);
}

void dump_vp_dir(char* dir_name){
  int i=0;
  int n=0;
  char* ext;
  if (dirFile.isOpen())
    dirFile.close();
  openDirectory(&dirFile, dir_name);
  while (file.openNext(&dirFile, O_READ)){
    file.getName(file_name, MAX_FILENAME_LEN);
    // Skip directories and hidden files.
    ext = get_filename_ext(file_name);
    upStr(ext);
    if (!file.isSubDir() && !file.isHidden() && strcmp(ext,"BIN")==0) {
      i++;
      Serial.println(F(" "));
      Serial.print(F("\tdb 00Ch"));
       for (int j=0; j<15; j++){
        if (j==7) {
          Serial.println(F(" "));
          Serial.print(F("\tdb "));
        } else {
          Serial.print(F(", "));
        }
        if (j < strlen(file_name)) {
          n = ASCII_to_VP(file_name[j]);
          sprintf_P(str1, PSTR("%03Xh"), n); 
          Serial.print(str1);
        } else {
          Serial.print(F("00Ch"));
        }
      }
    }    
    if (file.isOpen()) file.close(); 
    if ((i % 8)==0) Serial.println(F(""));
  }
  dirFile.close();
}
