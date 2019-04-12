//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OINITEGESTURETRACKER_H_
#define OINITEGESTURETRACKER_H_

#include <NiTE.h>
#include <iostream>
#include "OIGestureTracker.hpp"

namespace openiss
{
    class OINiTEGestureTracker : public OIGestureTracker
    {
    public:
        OINiTEGestureTracker();

        ~OINiTEGestureTracker() override;

        int init() override;

        int update() override;

        int stop() override;

        int startGestureDetection() override;

        int stopGestureDetection() override;

    private:
        nite::Status m_eStatus;
        nite::HandTracker m_oHandTracker;
        nite::HandTrackerFrameRef m_oHandTrackerFrame;
        nite::Point3f m_GesturePosition;
        openni::VideoFrameRef m_DepthFrame;
    };
}
#endif //OINITEGESTURETRACKER_H_
