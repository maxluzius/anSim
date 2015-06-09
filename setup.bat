@ECHO OFF

IF NOT EXIST %CD%/dependencies_win32 GOTO choose

SET currentPath=%CD%
CD dependencies_win32
CALL SetEnvironment.bat
CD %currentPath%/scripts

:choose
CLS
ECHO Choose your IDE:
ECHO (1) VisualStudio2010
ECHO (2) VisualStudio2012
ECHO (3) VisualStudio2013
ECHO (4) Eclipse CDT mit MinGW
ECHO (5) Sublime Text 2 mit MinGW
ECHO ----------------------
CHOICE /n /c "12345" /M ":"
IF ERRORLEVEL 5 START cmd /K CALL SublimeText2.bat &EXIT
IF ERRORLEVEL 4 START cmd /K CALL Eclipse.bat &EXIT
IF ERRORLEVEL 3 START cmd /K CALL VisualStudio2013.bat &EXIT
IF ERRORLEVEL 2 START cmd /K CALL VisualStudio2012.bat &EXIT
IF ERRORLEVEL 1 START cmd /K CALL VisualStudio2010.bat &EXIT
