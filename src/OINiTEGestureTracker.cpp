#include "OINiTEGestureTracker.hpp"

using namespace openiss;

OINiTEGestureTracker::OINiTEGestureTracker()
{
    m_eStatus = m_oHandTracker.create();
    m_oHandTracker.setSmoothingFactor(0.1);
}

// Destructor
OINiTEGestureTracker::~OINiTEGestureTracker()
{
    m_oHandTrackerFrame.release();
    m_oHandTracker.destroy();
}

// Initialize
int OINiTEGestureTracker::init()
{
    nite::NiTE::initialize();
    std::cout << "Initialization complete..." << std::endl;
    return 0;
}

// Stop
int OINiTEGestureTracker::stop()
{
    std::cout << "Shutdown complete..." << std::endl;
    nite::NiTE::shutdown();
    return 0;
}

int OINiTEGestureTracker::update()
{
//    Debug only
   m_oHandTracker.readFrame(&m_oHandTrackerFrame);
   if(!m_oHandTrackerFrame.isValid()) { return -1; }

//    Underlying OpenNI VideoFrameRef
   m_DepthFrame = m_oHandTrackerFrame.getDepthFrame();
   if(!m_DepthFrame.isValid()) { return -1; }

   return 0;
}

// Start gesture detection.
int OINiTEGestureTracker::startGestureDetection()
{
    m_oHandTracker.startGestureDetection(nite::GESTURE_CLICK);
    m_oHandTracker.startGestureDetection(nite::GESTURE_WAVE);
//    m_oHandTracker.startGestureDetection(nite::GESTURE_HAND_RAISE);
    std::cout << "Started gesture detection..." << std::endl;
    return 0;
}

// Stop gesture detection.
int OINiTEGestureTracker::stopGestureDetection()
{
    m_oHandTracker.stopGestureDetection(nite::GESTURE_CLICK);
    m_oHandTracker.stopGestureDetection(nite::GESTURE_WAVE);
//    m_oHandTracker.stopGestureDetection(nite::GESTURE_HAND_RAISE);
    std::cout << "Stopped gesture detection..." << std::endl;
    return 0;
}

//
std::vector<OIGestureData> OINiTEGestureTracker::getGestures()
{
    return m_eGestureData;
}

// E.O.F