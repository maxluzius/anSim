#!/bin/sh

BaseDir=CVK_AnSim

#export OpenGL_ROOT="$PWD/dependencies_osx/OpenGL"
#export GLM_ROOT="$PWD/dependencies_osx/glm"
#export GLFW3_ROOT="$PWD/dependencies_osx/glfw"
#export ASSIMP_ROOT="$PWD/dependencies_osx/assimp"
export CVK_DEPENDENCIES_OSX="$PWD/dependencies_osx"


sys=`uname -s`
if [ x$sys != xDarwin ] ; then
  echo " "
  echo "This script is for Mac OS X systems only (v10.7 or newer)"
  echo " "
  exit 2
fi

setupdirOK=1
[ -d framework ] || setupdirOK=0
[ -d scripts ] || setupdirOK=0
[ -f README_MacOSX.txt ] || setupdirOK=0

if [ x$setupdirOK = x0 ] ; then
  echo " "
  echo "This script ($0) must be called in the '$BaseDir' directory"
  echo "you checked out from the SVN repository."
  echo " "
  exit 1
fi

! command -v cmake > /dev/null && echo "Bitte erst 'cmake' installieren !!" && exit 1

echo " "
echo "Please choose your IDE:"
echo " "
echo " (1)  Eclipse with CDT"
echo " (2)  XCode"
echo " (3)  UNIX command line (make)"
echo " "

Gen=""
while [ x"$Gen" = x"" ]
  do
 printf "your choice (1-3): "
 read val
 case "$val" in
  1)
	Folder=BUILD_Eclipse; Gen="Eclipse CDT4 - Unix Makefiles"
	;;
  2)
	Folder=BUILD_Xcode; Gen="Xcode"
	;;
  3)
	Folder=BUILD_CLI; Gen="Unix Makefiles"
	;;
  *)
	echo "Wrong entry - please chose a number between 1 and 3"
	;;
 esac
done
# vorerst nur für Eclipse:

echo "Your choice: $Gen"

cd framework
fwdir=`pwd`
for A in BV* CG*
  do
    [ -d "$A" ] || continue;
    cd $A
    mkdir $Folder
    cd $Folder
    cmake -G"$Gen" ../src/
    status=$?
    cd $fwdir
  done

echo "Setup erfolgreich vorgenommen."
exit 0
