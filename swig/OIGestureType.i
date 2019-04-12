%module oigesture

%include "enumtypesafe.swg"
%javaconst(1);

%{
#include "OIGestureType.hpp"	
using namespace openiss;
%}

%include "OIGestureType.hpp"