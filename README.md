# Videopac µSD cart 
**©2020 Alejandro Valero (Wilco2009)**

![image](https://user-images.githubusercontent.com/43153593/207426524-b051f296-accb-4a30-91ae-f734bdb56f42.png)


Special thanks to Rene Van Den Enden

## INTRODUCTION
The Videopac µSD cart is a revolutionary cartridge allows the loading of Videopac/Magnavox Oddysey2 ROMs from a micro-SD card directly to the console.

![image](https://user-images.githubusercontent.com/43153593/207427077-ade1714f-a37d-4c53-aec0-f6d34b44e27c.png)

Features:
-	Supports the Magnavox Oddysey2, Philips Videopac G7000, Videopac+ G7400, JOPAC and all compatible consoles
-	File selection with OLED display and/or ‘on screen’ game selector
- Supports the following ROM types:
   -	Standard P10/P11 games: 2K, 4K and 8K
   -	XROM games: Game 31 (Musician) & Game 40 (4 In Row)
   -	Videopac+ games: Game 55+ (12K), 58+, 59+ and 60+ (16K)
   -	Soren Gust format: 12K
-	Serial transfer from PC for developers
-	Hexadecimal memory monitor for debugging
-	USB upgradable firmware


## PREREQUISITES
The following items are required for a working system with the Videopac µSD cart:
1.	A Magnavox Oddysey2, Philips Videopac G7000, Videopac+ G7400, JOPAC etc. console
2.	The Videopac µSD cart itself
3.	A micro-SD card (not supplied)
4.	A copy of the “SD.ZIP” file containing the files for the Videopac µSD cart
 
## LAYOUT
The **Videopac µSD cart** connectors and elements are listed below:

![image](https://user-images.githubusercontent.com/43153593/207427712-bd08fb42-4608-484e-a6f4-2da41bfe6c46.png)

## PREPARING THE SD CARD
The **Videopac µSD cart** supports any micro-SD card capacity formatted as FAT16 or FAT32.

The card must fully support the SPI communication protocol – there is a lot of variance in SD cards so for best results please use ‘known brand’ cards and if one card doesn’t work as expected then try another.

Preparing the SD card for the **Videopac µSD cart** is simple:

-	Card must be formatted in FAT16 or FAT32 format
-	The "GAMELIST.INI" file (see below) must be in the root directory of the card
-	A directory called “SYS” must be in the root directory
-	The master skeleton copy of the on-screen game selector ROM "SELECTGAME.BIN" must be in the “SYS” directory

A ZIP file “SD.ZIP” is supplied with the minimum structure required on the card which can be unzipped directly to the root of a freshly formatted SD card.

**Note:** Do not copy any other "SELECTGAME.BIN" into “SYS” other than the master one supplied.

## COPYING ROM FILES
When copying ROM files onto the Videopac µSD cart be aware that the on-screen game selector cannot currently navigate directories. Directories can be used for holding ROM files but will need to be selected using the OLED display and buttons before the game selector runs.

It is recommended that you place all ROM files in the root directory of the card for ease of use of the game selector.

**Note:** This restriction does not apply when directly selecting games using the OLED display and buttons.

## GAMELIST.INI
This file is supplied with the Videopac µSD cart and already contains entries for all the known games for the Videopac/Magnavox Odyssey2 platform, but is editable to make changes or add new entries if required.

The file is laid out in typical Windows INI file format where section names in square brackets correspond to the CRC32  value of a game file and beneath them the characteristics of the game.

An example for a complete game would be the following:

>[4EDA4917]
>
>NAME=01 Speedway! / Spin-Out! / Crypto-Logic!

>YEAR=1978
>
>MANUF=North American Philips Consumer Electronics Corp.
>
>VARIANT=Euro
>
>PAGGING=P10/P11

These values are read and used by the OLED display to show which game is running, the value "PAGGING" is used internally by the Videopac µSD cart to know how to manage the game's memory paging mode and can be set for P10/P11, VPPLUS, SOREN or XROM.

## SELECTGAME.BIN
This is the code for the on-screen file selector menu, use the joystick up and down and fire to select the file to load and once loaded, press ”RESET” key on the console to start.

**Note:** You cannot navigate directories at the current time.

Due to the way the console interacts with the **Videopac µSD cart**, a copy of the skeleton selection code from the “SYS” directory must be copied into the current directory and populated with the files it needs to show in this location, this is done when activating the “VPMENU” option.

The menu allows a maximum of 200 files at any one time, if there are more than this then moving left or right with the joystick will select the next group of 200 files.

When changing file group to get the next set of 200 files a new copy of “SELECTGAME.BIN” containing these files must be loaded, this is then activated by pressing the ”RESET” key on the console again.

Once a game is loaded pressing ”RESET” key on the console will restart the game, to return back to the menu, select “VPMENU” on the **Videopac µSD cart** and the menu will reload.

## MAIN MENU

Once the console is started with the **Videopac µSD cart** inserted it will boot and the OLED display will show the main menu options, use Direction buttons/Enter to select:

**OPTIONS:** “LOAD”, “VPMENU”, “CONFIG”, “RECEIVE”, “ABOUT” and “GAME”

### LOAD

This allows the selection of a .BIN file from the contents on the card to load into the **Videopac µSD cart*’s RAM memory using the buttons and the OLED display.
To select the file:

>-	“UP” & “DOWN” go back and forward one file
>-	“LEFT” & “RIGHT” go back and forward 20 files
>-	“ENTER” load the selected file into the memory or enter a sub directory
>-	“ESC” to go to the “FILE” sub-menu

Once the file is loaded into RAM memory with “ENTER”, press the "RESET" key on the console and follow the instructions for the corresponding game.

Pressing the “ESC” button on an item opens the "FILE" sub-menu which will gives access to the following options:

OPTIONS: “INFO”, “MONITOR” and “EXIT”

>-	INFO: Shows the information for the file and the corresponding metadata from “GAMESLIST.INI” if the CRC32 is known
>-	MONITOR: Displays the contents of the RAM memory in hexadecimal

>**Note:** Examining the RAM contents will decouple it from the running host console and will most likely not return without crashing.  When returning from this mode simply press "RESET" on the console to restore the game
>•	EXIT: Return to main menu
 
### VPMENU
Selecting this option will quit the current game and build the on-screen file selector code by making a copy of the skeleton “SELECTGAME.BIN” file in the current directory (as defined in the “LOAD” menu using the buttons and the OLED display) and populating it with the filenames from the current directory. Press the “RESET” button on the console to show the selection menu.

### CONFIG
OPTIONS: “SETDIR”, “AUTLOAD”, “LOGO”, “REBUILD”, “BAUD”, SORTED”
-	SETDIR: Assign the current directory as the directory from where the “SELECTGAME.BIN” will be read if “AUTOLOAD” is set (usually the root)
-	AUTOLOAD: Enables / disables automatic loading of the “SELECTGAME.BIN” file at start-up from the location defined by “SETDIR”
-	LOGO: Activates / deactivates the logo display during start-up
-	REBUILD: The "GAMELIST.INI" file and each directories file information are compiled and cached as binary index files to speed up file access and game information. This means that after changing the "GAMELIST.INI" file or add/removing files the indexes must be rebuilt:
   -	REBUILD GAMELIST: Generates game index file from the “GAMELIST.INI” file 
   -	REBUILD DIRECTORY: Generates file index files of the ROMs contained in the current directory
   -	WHEN: Choose when to perform rebuilding of the file indexes:
       - “ALWAYS”: The directory index is regenerated each time a directory is accessed with no need to regenerate the indexes each time a new ROM is added, but it will take longer to navigate and select a game
       - “MANUALLY”: The directory index files are not regenerated automatically and require manual rebuilding upon changes
- 	BAUD: Allows selection of the transmission speed of the serial port, valid values are: 
   -	9600 bps
   -	19200 bps
   -	38400 bps
   -	57600 bps
   -	115200 bps
-	SORTED: Select “YES” so that the files will appear sorted in alphabetical order
 
### RECEIVE
This is mainly aimed at developers and allows the connection of a PC to the **Videopac µSD cart** through an RS-232 serial connection (such as that supplied by a USB Serial Adaptor or Dongle) to load a program file directly into the RAM of the **Videopac µSD cart**.
  
![image](https://user-images.githubusercontent.com/43153593/207432807-1500daa1-0411-480a-bd38-15cb1c2ce04d.png) ![image](https://user-images.githubusercontent.com/43153593/207432829-7ec16a2d-d86c-4087-afc1-e087fea5bbd4.png)


The **Videopac µSD cart** serial connector header has the following pinout:

![image](https://user-images.githubusercontent.com/43153593/207432896-32e6836a-c897-49a2-ab2c-568569a70b08.png)

-	3 TX (Connect to the RX pin)
-	2 RX (Connect to the TX pin)
-	1 GND (Connect to the GND pin)


From the **Videopac µSD cart** side, select the desired data transmission speed (“BAUD”) in the “CONFIG” menu and select the “RECEIVE” option, transmission of the file from the PC can then begin.
From the PC side use the “UPLOAD.BAT file”, supplied in the “FLASH&SERIAL.ZIP” file that comes with the **Videopac µSD cart** to transfer the file.
The syntax for “UPLOAD.BAT” file is as follows:

> upload.bat <file.bin> [COMPORT] [BAUDRATE] [PAGGING]
> Where:
> -	COMPORT = COMport
> -	BAUDRATE = 9600, 19200(default), 38400, 56700, 115200
> -	PAGGING = P10/P11, VPPLUS, SOREN, XROM
For example, to load the file "VP01.BIN" at 115200 baud through the COM7 port, select the "RECEIVE" option on the **Videopac µSD cart** and then execute the following command on the PC:
> UPLOAD VP01.BIN COM7 115200 P10/P11
Once completed the transferred program can be executed by pressing “RESET” on the console in the usual way.

### ABOUT
Displays details about the **Videopac µSD cart** and the current version.
 
### GAME
This “easter egg” option allows you to play Videopac games using the OLED Display and direction buttons directly on the **Videopac µSD cart**, firmware V1.04 includes “Race” and “Pong.
To play, remove the **Videopac µSD cart** from the unit and attach the Arduino micro-USB port to a power source to before selecting this option followed by the required game.

When in-game pressing “ESC” will bring up a menu allowing sound to be disabled or the current game to quit and return to start.

To exit game you must remove power from the Arduino micro-USB port.
**Note:** Using the digital direction buttons will result in very different gameplay from using the analogue joysticks – good luck!

## UPDATING THE FIRMWARE
Updating the **Videopac µSD cart** with a new firmware version is as simple as connecting it with a micro-USB cable to a PC and executing a simple command.

Remove the **Videopac µSD cart** from the console and connect the Arduino micro-USB port to the PC, the Arduino driver should install and appear as a new CH340 COM port in the system.

The number of the COM port needs to be known and this can be determined by looking in the "Bluetooth and other devices" window of the Control Panel similar to this:

![image](https://user-images.githubusercontent.com/43153593/207433054-27801c1f-54f3-4e7f-bf15-e983d7ad009a.png)

If there are problems finding the correct number of the port then there is a utility called "LISTCOM.EXE" supplied in the ZIP file that will list all the COM ports available on the PC, test each of these to find the correct port.

Once the port is known proceed to run the flashing utility “VPFLASH.BAT” supplied in the “FLASH&SERIAL.ZIP” ZIP file, having already copied the required ".HEX" firmware file to the same directory as the utility.

Depending on the OLED type on your **Videopac µSD cart** you will need to select the firmware for either the “blue screen” SH1106” or the “white screen” SSD1306.
The syntax of the utility is as follows:

> VPFLASH \[COMPORT\] \<file\>

For example, to load the file "update.HEX" through the COM7 port, execute the following command on the PC:

> VPFLASH COM7 update.HEX

**Note:** DO NOT INTERRUPT THE FLASHING PROCEDURE - Wait for the flashing operation to finish, after which the **Videopac µSD cart** will automatically reset.

## RESTORING FACTORY SETTINGS
To restore the **Videopac µSD cart**’s factory settings, hold both “ENTER”+”ESC” buttons while booting. This option can be used to restore defaults or after installing firmware for the first time.

## BOOTING WITHOUT DISPLAY
If you have any kind of problem with the OLED display it is still possible to use the **Videopac µSD cart** as long as there is a copy of "SELECTGAME.BIN" in the root folder.

By holding the buttons “ESC” + “LEFT” while booting, the **Videopac µSD cart** will automatically go into “VPMENU” mode allowing on-screen game selection with the joystick.

## DIAGNOSTICS
The **Videopac µSD cart** provides a diagnostic utility to output to a serial console in case of any issues.
To access diagnostics, disconnect the **Videopac µSD cart** from the console and connect to a computer with the USB cable from the Arduino micro-USB port.
Open a serial terminal  to the CH340 COM port described above with settings 9600bps, 8bits, no parity, 1 stop bit (9600/8/none/1).
Press “ENTER” + “LEFT” during start-up to access the diagnostic utility via the serial terminal.

## PROGRAMING THE CPLD
Updating the CPLD programming should not normally be required, but it may be necessary to update if a bug is found or some new functionality related to communication with the console is required.
Programming the CPLD requires a XILINX programming cable connected to the JTAG port header of the **Videopac µSD cart**.
It is beyond the scope of this manual to explain updating the CPLD via JTAG, but in the event of a CPLD release further guidance will be given with the update.

