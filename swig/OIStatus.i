%module oigesture

%ignore openiss::OIStatus::setStatus(OIStatusType p_status);

%{
#include "OIStatus.hpp"	
using namespace openiss;
%}

%include "OIStatus.hpp"