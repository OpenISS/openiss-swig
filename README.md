# oigesture-java

1. `mkdir build && cd build`
2. `cmake .. -DOIGESTURE_SWIG_JNI:BOOL=ON -DBUILD_SHARED_LIBS=ON`
3. `make -j4`
4. `cp liboigesturecxx.so swig/`
5. `ln -s lib{OpenNI2/NiTE2/Nuitrack/Middleware} swig/` (optional)
6. `cmake .. -DOIGESTURE_SWIG_TEST_JAR`
7. `make -j4`
