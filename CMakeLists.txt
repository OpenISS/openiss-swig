cmake_minimum_required(VERSION 3.12.2)
project(oigesture VERSION 0.1.0)

option(OIGESTURE_SWIG_JNI "Build a swig generated JNI library" OFF)

add_library(oigesture
        src/OIHand.cpp
        src/OINiTEGestureTracker.cpp
        )

target_include_directories(oigesture PUBLIC include)
target_include_directories(oigesture PUBLIC $ENV{NITE2_INCLUDE})
target_include_directories(oigesture PUBLIC $ENV{OPENNI2_INCLUDE})

message(">>>" $ENV{OPENNI2_REDIST})

target_link_libraries(oigesture $ENV{OPENNI2_REDIST}/libOpenNI2.so)
target_link_libraries(oigesture $ENV{NITE2_REDIST64}/libNiTE2.so)

target_compile_options(oigesture PRIVATE -Wall -Wextra -pedantic -fPIC)

target_compile_features(oigesture PUBLIC cxx_std_17)
set_property(TARGET oigesture PROPERTY CXX_EXTENSIONS OFF)

if(OIGESTURE_SWIG_JNI)
    add_subdirectory(swig)
endif()

install(TARGETS oigesture DESTINATION lib)
install(FILES include/OIGestureTracker.hpp DESTINATION include)
