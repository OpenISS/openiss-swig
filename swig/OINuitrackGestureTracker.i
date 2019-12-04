%module oigesture
%include "typemaps.i"

%apply float *OUTPUT { float *p_OutX };
%apply float *OUTPUT { float *p_OutY };
void openiss::convertHandCoordinatesToDepth(float p_x, float p_y, float p_z, float* p_OutX, float* p_OutY) override;

%{
#include "OINuitrackGestureTracker.hpp"	
using namespace openiss;
%}

%include "OINuitrackGestureTracker.hpp"	