set folder=BUILD_Eclipse

@setlocal enableextensions enabledelayedexpansion
@echo off
cd ../framework
for /D %%A IN (BV* CG*) DO (
	setlocal enabledelayedexpansion
	cd %%A
	mkdir !folder!
	cd !folder!
	cmake -G"Eclipse CDT4 - MinGW Makefiles" ../src/
	cmake -G"Eclipse CDT4 - MinGW Makefiles" ../src/

	if "!errorlevel!"=="1" cd.. &echo Ein CMake Fehler ist aufgetreten. %%A/!folder! wurde nicht erzeugt.
	endlocal
)
pause
exit