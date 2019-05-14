//
// Created by jash on 15/04/19.
//

#include "OIGestureData.hpp"

using namespace openiss;

/**/
OIGestureData::OIGestureData() : m_eGestureType { OIGestureType::GESTURE_ALL },
                                 m_iGestureState{ OIGestureState::GESTURE_IS_ABSENT } {}
/**/
OIGestureData::~OIGestureData() = default;
/**/
void OIGestureData::setGesturePosition(float p_fx, float p_fy, float p_fz)
{
    this->m_sGesturePosition.x = p_fx;
    this->m_sGesturePosition.y = p_fy;
    this->m_sGesturePosition.z = p_fz;
}
/**/
void OIGestureData::setGestureType(const OIGestureType p_eGestureType)
{
    this->m_eGestureType = p_eGestureType;
}
/**/
const OIGestureType &OIGestureData::getGestureType()
{
    return this->m_eGestureType;
}
/**/
const Point3f &OIGestureData::getGesturePosition()
{
    return this->m_sGesturePosition;
}
/**/
void OIGestureData::setGestureState(OIGestureState p_eGestureState)
{
    this->m_iGestureState = p_eGestureState;
}
/**/
bool OIGestureData::isGestureComplete() const { return this->m_iGestureState == OIGestureState::GESTURE_IS_COMPLETE; }

// E.O.F