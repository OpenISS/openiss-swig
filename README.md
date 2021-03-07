# OIGesture JNI Library using SWIG >= 4.0 and CMake >= 3.12.2
## Using SWIG 4.0 or higher, this repository contains interface files for OpenISS Getsure Framework related classes, a maintainable way to let SWIG generate wrapper classes for OpenISS gesture library in a target language. 

### Currently, wrappers can be generated for Java only.

1. `mkdir build && cd build`
2. `cmake .. -DOIGESTURE_SWIG_JNI:BOOL=ON -DBUILD_SHARED_LIBS=ON`
3. `make -j4`
4. `cp liboigesturecxx.so swig/`
5. `ln -s lib{OpenNI2/NiTE2/Nuitrack/Middleware} swig/` (optional)
6. `cmake .. -DOIGESTURE_SWIG_TEST_JAR=ON`
7. `make -j4`
