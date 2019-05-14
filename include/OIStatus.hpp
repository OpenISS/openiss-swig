//
// Created by jash on 15/04/19.
//

#ifndef RT_SKEL_ROS_GESTURE_OISTATUS_HPP
#define RT_SKEL_ROS_GESTURE_OISTATUS_HPP

namespace openiss
{
    /**/
    enum class OIStatusType
    {
        STATUS_DEFAULT,
        STATUS_OK,
        STATUS_TRACKER_NOT_INITIALIZED,
        STATUS_FAIL
    };
    /**/
    struct OIStatus
    {
    public:
        OIStatusType getStatus()
        {
            return m_status;
        }

        void setStatus(OIStatusType p_status)
        {
            m_status = p_status;
        }
    /**/
    private:
        OIStatusType m_status { OIStatusType::STATUS_DEFAULT };
    };
}
#endif //RT_SKEL_ROS_GESTURE_OISTATUS_HPP
