# Install script for directory: /Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/libraries/CVK_2/cmake_install.cmake")
  include("/Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/libraries/CVK_AnSim/cmake_install.cmake")
  include("/Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/executables/assignment/cmake_install.cmake")
  include("/Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/shaders/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/max/Desktop/Dev/assignment/CVK_AnSim/framework/CG_AnSim_demos/BUILD_Eclipse/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
