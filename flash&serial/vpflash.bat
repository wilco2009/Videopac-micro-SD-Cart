@echo off
if [%1]==[] goto printhelp 
avrdude.exe -Cavrdude.conf -v -patmega2560 -cwiring -b115200 -D -Uflash:w:%2%:i -P%1%
GOTO END
:printhelp
echo:
echo ****** Flashing firmware to the "videopac uSD CART" ******
echo usage: VPFLASH [COMPORT] ^<file^>
echo:
:END