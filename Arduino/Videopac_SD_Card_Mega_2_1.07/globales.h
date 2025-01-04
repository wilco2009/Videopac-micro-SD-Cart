#define SDFAT
#ifdef SH1106
U8G2_SH1106_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);
char disp[]="SH1106";
#endif
#ifdef SSD1306
U8G2_SSD1306_128X64_NONAME_F_HW_I2C u8g2(U8G2_R2, /* reset=*/ U8X8_PIN_NONE);
char disp[]="SSD1306";
#endif

char str_GAMEOVER[] = "GAME OVER";

#define BLOCK_SIZE 256

#define PAG_P10_P11       0
#define PAG_VP_PLUS       1
#define PAG_SOREN         2
#define PAG_SELECT_GAME   3
#define PAG_TEST          4
#define PAG_XROM          5
#define MODE_PLAYING      0
#define MODE_SENDING_GAME 1

#define DIR_TO_BUS LOW
#define DIR_TO_CART HIGH
#define DISABLE_BUFFER HIGH 
#define ENABLE_BUFFER LOW 
#define MAX_FILENAME_LEN 100
#define MAX_DIRNAME_LEN 100
#define MAX_DEPTH 5
#define MAXDIR 200

#define GAME_NAME_LEN 101
#define GAME_BRAND_LEN 101
#define GAME_YEAR_LEN 21
#define GAME_VARIANT_LEN 51


  const int SPEAKER_PIN = 9;
  const int VOICE_PIN = 46;
  const int WR        = 3;
  const int OE        = 4;

  const int butUP     = 5;
  const int butDOWN   = 6;
  const int butLEFT   = 7;
  const int butRIGHT  = 8;
  const int butENTER  = 2;
  const int butESC    = 10;
  const int THEVOICE_SELECT_PIN = 11;


  const int PAGEMODE0 = 37;
  const int PAGEMODE1 = 36;
  const int PAGEMODE2 = 35;

  const int LED_SD    = 48;
  const int LED_RAM   = 49;
  

  const int pMISO      = 50;
  const int pMOSI      = 51;
  const int pSCK       = 52;
  const int pSPICS     = 53;

// byte pagging = PAG_P10_P11;

//TMRpcm tmrpcm;   // create an object for use in this sketch

boolean showVolt = false;

byte TheVoice = 0;

boolean resetting = false;

boolean SDOK = false;

boolean sorted = true;

boolean autorebuild = true;

boolean minigame_sound = true;

byte remotepgm = 0;
unsigned int cont;
unsigned int direccion = 0;
byte block[BLOCK_SIZE+1];
char str1[MAX_FILENAME_LEN];
char str2[MAX_FILENAME_LEN];
//char str3[MAX_FILENAME_LEN];
char file_name[MAX_FILENAME_LEN] = "vp_01.bin";
char file_loaded[MAX_FILENAME_LEN] = "";
char autoload_file[MAX_FILENAME_LEN] = "SELECTGAME.BIN";
char dir_name[MAXDIR] = "/";
char initial_dir[MAXDIR] = "/";
char strVER[]="1.07";
char strCacheFName[] = "$$$$$$$$.$$$";

char msgSDNOTOK[] = "uSD card not found";

bool to_show_logo = true;

char game_name[GAME_NAME_LEN] = "";
char game_brand[GAME_BRAND_LEN] = "";
char game_year[GAME_YEAR_LEN] = "";
char game_variant[GAME_VARIANT_LEN] = "";
byte game_pagging = 0;
int game_size = 0;
int game_BANK = 0;

unsigned long int bauds[] = {9600, 19200, 38400, 57600, 115200};

boolean show_descrition = true;
unsigned long int game_CRC = 0;
byte baudrate = 0;
int RAM_pos = 0;
byte RAM_delay;

int ch_ini;
static long int ti;

#ifdef SDFAT
SdFat sd;
SdFile file;
SdFile cache;
SdFile dirFile;


SdFile iniFile;
SdFile CRCFile;
SdFile dataFile;
SdFile descindex;
#else
File file;
File cache;
File dirFile;


File iniFile;
File CRCFile;
File dataFile;
File descindex;
#endif

int num_files = 0;
int num_files_nodir = 0;
long int inicio = 0;

//TMRpcm audio;   // create an object for use in this sketch
