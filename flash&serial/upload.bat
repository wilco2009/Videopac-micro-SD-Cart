@echo off

if [%1]==[] goto printhelp 

set baudrate=%3
set port=%2
set pagging=%4
REM default baudrate
if [%3]==[] set baudrate=19200
REM default COMPORT
if [%2]==[] set port=COM5
REM default PAGINATION
if [%4]==[] set pagging=P10/P11

REM MODE %port% %baudrate%,N,8,1,P 
MODE %port% BAUD=%baudrate% PARITY=e DATA=8 STOP=1 to=off odsr=off octs=off dtr=off rts=off idsr=off 
@echo SIZE=%~z1 > %port%
@echo NAME=%1 > %port%
@echo PAGGING=%pagging% > %port%

timeout /T 2

copy /b %1 %port%:
GOTO END

:printhelp
echo:
echo ****** Upload a file to the "videopac uSD CART" ******
echo usage: upload.bat ^<file.bin^> [COMPORT] [BAUDRATE] [PAGGING]
echo:
echo valid values for COMPORT = 9600,19200(default),38400,56700,115200
echo valid values for PAGGING = P10/P11, VPPLUS, SOREN, XROM
echo:

:END