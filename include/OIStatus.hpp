#ifndef OISTATUS_H_
#define OISTATUS_H_

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
#endif //OISTATUS_H_
