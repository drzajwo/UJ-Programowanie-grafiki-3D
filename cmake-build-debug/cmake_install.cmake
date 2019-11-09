# Install script for directory: /Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw

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
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/libs/OGLAppFramework/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample0_EmptyScreen/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample1_Triangle/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample2_IB_VBO/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample3_VS_FS_Interpolation/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample4_UBO_Intensity/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample5_PVM/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample6_Piramidka/cmake_install.cmake")
  include("/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/src/OGLSample7_Backface_culling/cmake_install.cmake")

endif()

if(CMAKE_INSTALL_COMPONENT)
  set(CMAKE_INSTALL_MANIFEST "install_manifest_${CMAKE_INSTALL_COMPONENT}.txt")
else()
  set(CMAKE_INSTALL_MANIFEST "install_manifest.txt")
endif()

string(REPLACE ";" "\n" CMAKE_INSTALL_MANIFEST_CONTENT
       "${CMAKE_INSTALL_MANIFEST_FILES}")
file(WRITE "/Users/wojci/Desktop/doZgrania/Studia UJ/Grafika/cw/cmake-build-debug/${CMAKE_INSTALL_MANIFEST}"
     "${CMAKE_INSTALL_MANIFEST_CONTENT}")
