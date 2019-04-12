//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OIGFRAME_H_
#define OIGFRAME_H_

#include <iostream>
#include <cstring>
#include <stdint.h>

namespace openiss 
{
//
    struct GFrame
    {
    public:
        GFrame() = default;
        ~GFrame() = default;

        int m_height {0};
        int m_width {0};
        const uint16_t* m_DepthData{nullptr};
    };

    typedef struct Point3f
    {
        float x{0};
        float y{0};
        float z{0};
    } Point3f;

    typedef struct
    {
        /* Red value of this pixel. */
        uint8_t r;
        /* Green value of this pixel. */
        uint8_t g;
        /* Blue value of this pixel. */
        uint8_t b;
    } OIRGBPixel;

    typedef uint16_t                OIDepthPixel;
}

#endif //OIGFRAME_H_
