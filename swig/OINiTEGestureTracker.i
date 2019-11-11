%module oigesture
%include "typemaps.i"
%include "std_vector.i"

%template(GesturesVector) std::vector<openiss::OIGestureData>;
%template(HandsVector) std::vector<openiss::OIHandData>;

%apply float *OUTPUT { float *p_OutX };
%apply float *OUTPUT { float *p_OutY };
void openiss::convertHandCoordinatesToDepth(float p_x, float p_y, float p_z, float* p_OutX, float* p_OutY) override;

%{
#include "OINiTEGestureTracker.hpp"	
using namespace openiss;
%}

%include "OINiTEGestureTracker.hpp"	