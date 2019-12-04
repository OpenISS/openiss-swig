#ifndef OIHANDDATA_H_
#define OIHANDDATA_H_

#include "OIDepthFrame.hpp"
#include "OIState.hpp"

namespace openiss
{
    /* OIHandData represents a user's hand with required data. */
    class OIHandData {
    public:
        OIHandData();
        ~OIHandData();
        /**/
        const int& getHandID();
        const Point3f& getHandPosition();
        /**/
        bool isHandLost() const;
        bool isHandNew() const;
        bool isHandTracked() const;
        bool isHandTouchingFOV() const;
        /**/
        void setHandPosition(float p_fx, float p_fy, float p_fz);
        void setHandState(OIHandState p_sHandState);
        void setHandID (int p_HandID);
    /**/
    private:
        int m_iHandId;
        OIHandState m_iHandState;
        Point3f m_sHandPosition;
    };
}
#endif //OIHANDDATA_H_