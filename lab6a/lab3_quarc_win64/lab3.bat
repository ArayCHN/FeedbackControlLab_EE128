@call "C:\Users\ee128-aai\AppData\Roaming\MathWorks\MATLAB\R2013b\mexopts.bat"
@echo on
call "c:\Program Files\Microsoft SDKs\Windows\v7.1\Bin\SetEnv.cmd" /x64 /Release 2>1 > nul:
set MATLAB=C:\PROGRA~1\MATLAB\R2013b
nmake -f lab3.mk  MAT_FILE=0 SHOW_TIMES=0 DEBUG=0 DEBUG_HEAP=0 OPTS="-DON_TARGET_WAIT_FOR_START=0"
