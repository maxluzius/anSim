set folder=BUILD_VisualStudio12

@setlocal enableextensions enabledelayedexpansion
@echo off
cd ../framework
for /D %%A IN (BV* CG*) DO (
	setlocal enabledelayedexpansion
	cd %%A
	mkdir !folder!
	cd !folder!
	cmake -G"Visual Studio 11" ../src/

	if "!errorlevel!"=="1" cd.. &echo Ein CMake Fehler ist aufgetreten. %%A/!folder! wurde nicht erzeugt.
	endlocal
)
pause
exit