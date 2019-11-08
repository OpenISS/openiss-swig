find_package(SWIG 4.0 REQUIRED)
find_package(Java REQUIRED)
find_package(JNI REQUIRED)
include(UseJava)
include(UseSWIG)

if(APPLE)
    SET(CMAKE_SKIP_RPATH NO)
    SET(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE)
    SET(CMAKE_INSTALL_RPATH_USE_LINK_PATH FALSE)
    SET(CMAKE_SHARED_LINKER_FLAGS "-fPIC")
    SET(CMAKE_INSTALL_RPATH "/$ORIGIN/./osx")
endif(APPLE)

list(APPEND swig_inc_dirs
        ${JNI_INCLUDE_DIRS}
        ${PROJECT_SOURCE_DIR}/include)

set_source_files_properties(oigesture.i
    PROPERTIES
        CPLUSPLUS ON
        INCLUDE_DIRECTORIES "${swig_inc_dirs}")

set(CMAKE_SWIG_FLAGS -package openiss.oigesture)

swig_add_library(oigesture
    TYPE SHARED
    LANGUAGE java
    OUTPUT_DIR ${CMAKE_BINARY_DIR}/swig/openiss/oigesture
    SOURCES oigesture.i)

target_include_directories(oigesture PRIVATE ${swig_inc_dirs})
target_include_directories(oigesture PUBLIC $ENV{NITE2_INCLUDE})
target_include_directories(oigesture PUBLIC $ENV{OPENNI2_INCLUDE})

target_link_libraries(oigesture PUBLIC oigesturecxx)
if(APPLE)
    target_link_libraries(oigesture PRIVATE $ENV{OPENNI2_REDIST}/libOpenNI2.dylib)
    target_link_libraries(oigesture PRIVATE $ENV{NITE2_REDIST64}/libNiTE2.dylib)
elseif(UNIX)
    target_link_libraries(oigesture PRIVATE $ENV{OPENNI2_REDIST}/libOpenNI2.so)
    target_link_libraries(oigesture PRIVATE $ENV{NITE2_REDIST64}/libNiTE2.so)
endif(APPLE)

target_compile_options(oigesture PRIVATE -Wall)

add_jar(
    oigestureJNI
    SOURCES
    ${CMAKE_BINARY_DIR}/swig/openiss/oigesture/oigestureJNI.java
    ${CMAKE_BINARY_DIR}/swig/openiss/oigesture/oigesture.java
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