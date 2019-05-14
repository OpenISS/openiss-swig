//
// Created by jash on 29/03/19.
//

#ifndef RT_SKEL_ROS_GESTURE_OIGFRAME_H
#define RT_SKEL_ROS_GESTURE_OIGFRAME_H

#include <iostream>
#include <cstring>
#include <stdint.h>

namespace openiss {
/**/
    struct GFrame
    {
    public:
        GFrame() = default;
        ~GFrame() = default;
        /**/
        void setHeight(const int& p_height)
        {
            this->m_height = p_height;
        }
        void setWidth(const int& p_width)
        {
            this->m_width = p_width;
        }
        void setDepthData( const uint16_t* p_depthData)
        {
            this->m_DepthData = p_depthData;
        }
        /**/
        const uint16_t* getDepthData()
        {
            return this->m_DepthData;
        }
        int getHeight()
        {
            return this->m_height;
        }
        int getWidth()
        {
            return this->m_width;
        }
    /**/
    private:
        int m_height {0};
        int m_width {0};
        const uint16_t* m_DepthData{nullptr};
    };
    /**/
    typedef struct Point3f
    {
        float x{0};
        float y{0};
        float z{0};
    } Point3f;
    /**/
    typedef uint16_t                OIDepthPixel;
}

#endif //RT_SKEL_ROS_GESTURE_OIGFRAME_H
