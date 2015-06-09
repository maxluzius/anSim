set folder=BUILD_VisualStudio13

@setlocal enableextensions enabledelayedexpansion
@echo off
cd ../framework
for /D %%A IN (BV* CG*) DO (
	setlocal enabledelayedexpansion
	cd %%A
	mkdir !folder!
	cd !folder!
	cmake -G"Visual Studio 12" ../src/

	if "!errorlevel!"=="1" cd.. &echo Ein CMake Fehler ist aufgetreten. %%A/!folder! wurde nicht erzeugt.
	endlocal
)
pause
exit