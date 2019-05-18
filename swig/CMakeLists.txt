find_package(SWIG 4.0 REQUIRED)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)
include(UseSWIG)

SET(CMAKE_SKIP_RPATH NO)
SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
SET(CMAKE_SHARED_LINKER_FLAGS "-fPIC")

if(APPLE)
    SET(CMAKE_INSTALL_RPATH "/$ORIGIN/./osx")
endif(APPLE)

list(APPEND swig_inc_dirs
        ${JNI_INCLUDE_DIRS}
        ${CMAKE_CURRENT_SOURCE_DIR}/../include)

set_source_files_properties(oigesture.i
    PROPERTIES
        CPLUSPLUS ON
        INCLUDE_DIRECTORIES "${swig_inc_dirs}")

set(CMAKE_SWIG_FLAGS -package com.oigesture)

swig_add_library(oigesture
    TYPE SHARED
    LANGUAGE java
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/swig/com/oigesture
    SOURCES oigesture.i)

target_include_directories(oigesture PRIVATE ${swig_inc_dirs})

target_link_libraries(oigesture PRIVATE oigesturecxx)
target_link_libraries(oigesture PRIVATE $ENV{OPENNI2_REDIST}/libOpenNI2.dylib)
target_link_libraries(oigesture PRIVATE $ENV{NITE2_REDIST64}/libNiTE2.dylib)

target_compile_options(oigesture PRIVATE -Wall)

add_jar(
    oigestureJNI
    SOURCES
    ${CMAKE_BINARY_DIR}/swig/com/oigesture/oigestureJNI.java
    ${CMAKE_BINARY_DIR}/swig/com/oigesture/oigesture.java
)
add_dependencies(oigestureJNI oigesture)

# Build a testing jar which invokes the jni lib to verify it
add_jar(
    LibTesterMain
    SOURCES main.java
    ENTRY_POINT main
)
add_dependencies(LibTesterMain oigestureJNI)

add_custom_command(
    TARGET LibTesterMain
    POST_BUILD
    COMMAND ${Java_JAVA_EXECUTABLE} -Djava.library.path=.:${CMAKE_BINARY_DIR} -jar LibTesterMain.jar "JNI jar call success"
)

# install(FILES ${CMAKE_BINARY_DIR}/swig/oigestureJNI.jar DESTINATION bin)
# install(TARGETS oigesture DESTINATION lib)