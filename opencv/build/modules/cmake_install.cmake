# Install script for directory: C:/git/miwoosae-c/opencv/sources/modules

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "C:/git/miwoosae-c/opencv/build/install")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Release")
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

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/licenses" TYPE FILE RENAME "ade-LICENSE" FILES "C:/git/miwoosae-c/opencv/build/3rdparty/ade/ade-0.1.1d/LICENSE")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/licenses" TYPE FILE RENAME "ffmpeg-license.txt" FILES "C:/git/miwoosae-c/opencv/sources/3rdparty/ffmpeg/license.txt")
endif()

if("x${CMAKE_INSTALL_COMPONENT}x" STREQUAL "xlicensesx" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/etc/licenses" TYPE FILE RENAME "ffmpeg-readme.txt" FILES "C:/git/miwoosae-c/opencv/sources/3rdparty/ffmpeg/readme.txt")
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/calib3d/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/core/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/dnn/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/features2d/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/flann/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/gapi/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/highgui/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/imgcodecs/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/imgproc/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/java/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/js/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/ml/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/objdetect/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/photo/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/python/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/stitching/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/ts/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/video/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/videoio/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/.firstpass/world/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/java_bindings_generator/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/world/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/python_bindings_generator/cmake_install.cmake")
  include("C:/git/miwoosae-c/opencv/build/modules/ts/cmake_install.cmake")

endif()

