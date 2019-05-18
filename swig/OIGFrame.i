%module oigesture
%include "stdint.i"

%ignore openiss::GFrame::setWidth(const int& p_width);
%ignore openiss::GFrame::setHeight(const int& p_height);
%ignore openiss::GFrame::setDepthData(const uint16_t* p_depthData);

%typemap(jni) unsigned short* "jshortArray"
%typemap(jtype) unsigned short* "short[]"
%typemap(jstype) unsigned short* "short[]"
%typemap(javaout) unsigned short* {
   return $jnicall;
}
%typemap(out) unsigned short*
{
   long lSize = (arg1)->getWidth() * (arg1)->getHeight();
   
   if ((arg1)->getDepthData() != nullptr)
   {
      // create a new short[] object in Java
      jshortArray data = JCALL1(NewShortArray, jenv, lSize);
      if (data == nullptr)
      {
         jclass excep = jenv->FindClass("java/lang/NullPointerException");
         if (excep)
            jenv->ThrowNew(excep, "SIGSEV null pointer exception!");
         $result = 0;
         return $result;
      }
      // copy pixels from the image buffer
      JCALL4(SetShortArrayRegion, jenv, data, 0, lSize, (jshort*)result);
      $result = data;
   }
   else
   {
      $result = 0;
   }
}

%{
#include "OIGFrame.hpp"	
using namespace openiss;
%}

%include "OIGFrame.hpp"