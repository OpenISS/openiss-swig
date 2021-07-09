# OpenISS SWIG Wrapper
[![DOI](https://zenodo.org/badge/181078419.svg)](https://zenodo.org/badge/latestdoi/181078419)

This project is used to generate wrappers for common classes and data structures of the [OpenISS](https://github.com/OpenISS/OpenISS) project to support bindings for Java (and other languages) based of the OpenISS C++ framework. It is used as an example for a JNI library in [Processing](https://processing.org) for Java-based projects like ISSv2, known as OIGesture JNI Library in OpenISS's examples directory.

This repo is currently based on [Jashanjot Singh](https://github.com/jashanj0tsingh)'s [master's thesis](https://spectrum.library.concordia.ca/986429/) that currently covers only the OpenISS Gesture Recognition specialization framework and wrappers for NiTE2 and [Nuitrack](https://github.com/3DiVi/nuitrack-sdk) middleware.


## Building

### Requirements

- [SWIG](http://swig.org/) >= 4.0
- [CMake](https://cmake.org/) >= 3.12.2
- JDK8+

The middleware also needs to be present if used:

- OpenNI2
- NiTE2
- Nuitrack

Otherwise, the particular modules can be commented out.

The project was built and tested on Ubuntu 18+ and macOS 10.11+.

### Overview

This repository contains SWIG interface files for **OpenISS Getsure Framework** related classes, a maintainable way to let SWIG generate wrapper classes for OpenISS gesture library in a target language. 

**Currently, wrappers can be generated for Java only.**

1. `mkdir build && cd build`
2. `cmake .. -DOIGESTURE_SWIG_JNI:BOOL=ON -DBUILD_SHARED_LIBS=ON`
3. `make -j4`
4. `cp liboigesturecxx.so swig/`
5. `ln -s lib{OpenNI2/NiTE2/Nuitrack/Middleware} swig/` (optional)
6. `cmake .. -DOIGESTURE_SWIG_TEST_JAR=ON`
7. `make -j4`

### References

- [Jashanjot Singh](https://github.com/jashanj0tsingh), [*Universal Gesture Tracking Framework in OpenISS and ROS and its Applications*](https://spectrum.library.concordia.ca/986429/), Master's thesis, January 2020, Concordia University, Montreal
