//
// Created by jash on 15/04/19.
//

#ifndef RT_SKEL_ROS_GESTURE_OIGESTUREDATA_HPP
#define RT_SKEL_ROS_GESTURE_OIGESTUREDATA_HPP

#include "OIGFrame.hpp"
#include "OIState.hpp"
#include "OIGestureType.hpp"

namespace openiss
{
/* class OIGestureData represents a real-world gesture with relevant gesture data. */
    class OIGestureData
    {
    public:
        OIGestureData();
        ~OIGestureData();
        /**/
        const Point3f &getGesturePosition();
        const OIGestureType &getGestureType();
        /**/
        bool isGestureComplete() const;
        void setGesturePosition(float p_fx, float p_fy, float p_fz);
        void setGestureType(OIGestureType p_eGestureType);
        void setGestureState(OIGestureState p_eGestureState);
    /**/
    private:
        OIGestureType m_eGestureType;
        Point3f m_sGesturePosition;
        OIGestureState m_iGestureState;
    };
}
#endif //RT_SKEL_ROS_GESTURE_OIGESTUREDATA_HPP
