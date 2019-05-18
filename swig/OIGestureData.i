%module oigesture

%ignore openiss::OIGestureData::getGesturePosition();
%ignore openiss::OIGestureData::setGesturePosition(float p_fx, float p_fy, float p_fz);
%ignore openiss::OIGestureData::setGestureType(OIGestureType p_eGestureType);
%ignore openiss::OIGestureData::setGestureState(OIGestureState p_eGestureState);

%{
#include "OIGestureData.hpp"	
using namespace openiss;
%}

%include "OIGestureData.hpp"