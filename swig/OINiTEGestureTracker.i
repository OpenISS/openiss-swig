%module oigesture
%include "std_vector.i"

%template(GesturesVector) std::vector<openiss::OIGestureData>;
%template(HandsVector) std::vector<openiss::OIHandData>;

%{
#include "OINiTEGestureTracker.hpp"	
using namespace openiss;
%}

%include "OINiTEGestureTracker.hpp"	