# oigesture-java

mkdir build && cd build
cmake .. -DOIGESTURE_SWIG_JNI:BOOL=ON -DBUILD_SHARED_LIBS=ON
make -j4
cp liboigesturecxx.so swig/
Optional: ln -s lib{OpenNI2/NiTE2/Nuitrack/Middleware} swig/
cmake .. -DOIGESTURE_SWIG_TEST_JAR
make -j4
