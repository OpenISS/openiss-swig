%module oigesture

%include "enumtypesafe.swg"
%javaconst(1);

%{
#include "OIState.hpp"	
using namespace openiss;
%}

%include "OIState.hpp"