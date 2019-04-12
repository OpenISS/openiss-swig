//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OIHAND_H_
#define OIHAND_H_

#include "OIGFrame.hpp"
#include "OIGestureType.hpp"
#include "OIState.hpp"


namespace openiss {
    // OIGestureData represents a gesture with required data.
    class OIGestureData {

    public:
        OIGestureData();
        ~OIGestureData();

        const Point3f &getGesturePosition();
        const OIGestureType &getGestureType();

        bool isGestureComplete() const;

        void setGesturePosition(float p_fx, float p_fy, float p_fz);
        void setGestureType(OIGestureType p_eGestureType);
        void setGestureState(OIGestureState p_eGestureState);

    private:
        OIGestureType m_eGestureType;
        Point3f m_sGesturePosition;
        OIGestureState m_iGestureState;
    };
}

#endif //OIHAND_H_
