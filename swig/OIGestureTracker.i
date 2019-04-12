%module oigesture

%{
#include "OIGestureTracker.hpp"	
using namespace openiss;
%}

%include "OIGestureTracker.hpp"

%pragma(java) jniclasscode=%{
  static {
    try {
        System.loadLibrary("oigesture");
    } catch (UnsatisfiedLinkError e) {
      System.err.println("Native code library failed to load!. \n" + e);
      System.exit(1);
    }
  }
%}
