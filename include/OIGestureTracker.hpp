//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OIGESTURETRACKER_H_
#define OIGESTURETRACKER_H_

#include <vector>
#include "OIGFrame.hpp"

namespace openiss
{
    class OIGestureTracker
    {
    public:
        virtual ~OIGestureTracker() = default;

// Initialize/Stop devices and API components.
        virtual int init() = 0;
        virtual int update() = 0;
        virtual int stop() = 0;

// Start/Stop gesture detection and get a collection of gestures available.
        virtual int startGestureDetection() = 0;
        virtual int stopGestureDetection() = 0;
    };
}

#endif //OIGESTURETRACKER_H_
