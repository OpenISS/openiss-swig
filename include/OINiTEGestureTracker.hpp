//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OINITEGESTURETRACKER_H_
#define OINITEGESTURETRACKER_H_

#include <NiTE.h>
#include <iostream>
#include "OIGestureTracker.hpp"
#include "OIHand.hpp"

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

        std::vector<OIGestureData> getGestures() override;
    private:
        nite::Status m_eStatus;
        nite::HandTracker m_oHandTracker;
        nite::HandTrackerFrameRef m_oHandTrackerFrame;
        nite::Point3f m_GesturePosition;
        openni::VideoFrameRef m_DepthFrame;

        OIGestureData m_eGesture;
        std::vector<OIGestureData> m_eGestureData;
        /* Provides Callback functionality. */
        class FrameListener : public nite::HandTracker::NewFrameListener
        {
        public:
            explicit FrameListener(OINiTEGestureTracker* p_OINiTEGestureTracker)
            {
                this->m_OINiTEGestureTracker = p_OINiTEGestureTracker;
            }
            ~FrameListener()
            {
                delete m_OINiTEGestureTracker;
            }
            GFrame m_GFrame;
            void onNewFrame(nite::HandTracker &p_HandTracker) override;
        private:
            OINiTEGestureTracker* m_OINiTEGestureTracker;
        };
        /* --- */
        FrameListener* m_listener;
    };
}
#endif //OINITEGESTURETRACKER_H_
