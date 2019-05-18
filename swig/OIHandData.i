%module oigesture

%ignore openiss::OIHandData::setHandPosition(float p_fx, float p_fy, float p_fz);
%ignore openiss::OIHandData::setHandState(OIHandState p_sHandState);
%ignore openiss::OIHandData::setHandID (int p_HandID);

%{
#include "OIHandData.hpp"	
using namespace openiss;
%}

%include "OIHandData.hpp"