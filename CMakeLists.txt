cmake_minimum_required(VERSION 3.12.2)
project(oigesture VERSION 0.1.0)

option(OIGESTURE_SWIG_JNI "Build a swig generated JNI library" OFF)

SET(CMAKE_SKIP_RPATH NO)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
SET(CMAKE_SHARED_LINKER_FLAGS "-fPIC")

if(APPLE)
    SET(CMAKE_INSTALL_RPATH "/$ORIGIN/./osx")
endif(APPLE)

add_library(oigesturecxx
		SHARED
        src/OIHand.cpp
        src/OINiTEGestureTracker.cpp
        )

target_include_directories(oigesturecxx PUBLIC include)
target_include_directories(oigesturecxx PUBLIC $ENV{NITE2_INCLUDE})
target_include_directories(oigesturecxx PUBLIC $ENV{OPENNI2_INCLUDE})

target_link_libraries(oigesturecxx $ENV{OPENNI2_REDIST}/libOpenNI2.dylib)
target_link_libraries(oigesturecxx $ENV{NITE2_REDIST64}/libNiTE2.dylib)

target_compile_options(oigesturecxx PRIVATE -Wall)

target_compile_features(oigesturecxx PUBLIC cxx_std_17)
set_property(TARGET oigesturecxx PROPERTY CXX_EXTENSIONS OFF)

if(OIGESTURE_SWIG_JNI)
    add_subdirectory(swig)
endif()

install(TARGETS oigesturecxx DESTINATION lib)
install(FILES include/OIGestureTracker.hpp DESTINATION include)
