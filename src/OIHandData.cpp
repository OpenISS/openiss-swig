#include "OIHandData.hpp"

using namespace openiss;

/**/
OIHandData::OIHandData() : m_iHandId {0},
                           m_iHandState{OIHandState::HAND_IS_ABSENT},
                           m_sHandPosition{} {}
/**/
OIHandData::~OIHandData() =  default;
/**/
const int& OIHandData::getHandID()
{
    return this->m_iHandId;
}
/**/
void OIHandData::setHandPosition(float p_fx, float p_fy, float p_fz)
{
    this->m_sHandPosition.x = p_fx;
    this->m_sHandPosition.y = p_fy;
    this->m_sHandPosition.z = p_fz;
}
/**/
const Point3f& OIHandData::getHandPosition()
{
    return this->m_sHandPosition;
}
/**/
void OIHandData::setHandState(OIHandState p_eHandState)
{
    this->m_iHandState = p_eHandState;
}
/**/
void OIHandData::setHandID(const int p_HandID)
{
    this->m_iHandId = p_HandID;
}
/**/
bool OIHandData::isHandLost() const { return this->m_iHandState == OIHandState::HAND_IS_LOST; }
/**/
bool OIHandData::isHandNew() const { return this->m_iHandState == OIHandState::HAND_IS_NEW; }
/**/
bool OIHandData::isHandTracked() const { return this->m_iHandState == OIHandState::HAND_IS_TRACKING; }
/**/
bool OIHandData::isHandTouchingFOV() const { return this->m_iHandState == OIHandState::HAND_IS_TOUCHING_FOV; }

// E.O.F