# Install script for directory: C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client/out/install/x64-Debug")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
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

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client/out/build/x64-Debug/lib/GameInterface/cmake_install.cmake")
  include("C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client/out/build/x64-Debug/lib/SDL2EasyGUI/cmake_install.cmake")
  include("C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client/out/build/x64-Debug/lib/Tetris/cmake_install.cmake")
  include("C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client/out/build/x64-Debug/Tetris/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "C:/Users/goodd/OneDrive/문서/Visual Studio 2019/SDL2_Tetris_Client/out/build/x64-Debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
