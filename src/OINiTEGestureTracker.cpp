#include "OINiTEGestureTracker.hpp"

using namespace openiss;

/* Forward declarations for some helper functions. */
OIGestureType convertNiTEGestureType(nite::GestureType p_eGestureType);
OIGestureState convertNiTEGestureState(nite::GestureData p_sGestureData);
OIHandState convertNiTEHandState(nite::HandData p_sHandData);
void printNiTEGesturesToString(nite::GestureType p_eGestureType);

OINiTEGestureTracker::OINiTEGestureTracker()
{
    m_eStatus = m_oHandTracker.create();
    m_oHandTracker.setSmoothingFactor(0.1);
    m_listener = new FrameListener(this);
    if(m_listener)
        m_oHandTracker.addNewFrameListener(m_listener);
    else
        std::cerr << "Failed to add a frame listener!" << std::endl;
}

// Destructor
OINiTEGestureTracker::~OINiTEGestureTracker()
{
    m_oHandTrackerFrame.release();
    m_oHandTracker.removeNewFrameListener(m_listener);
    delete m_listener;
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

// Callback function.
void OINiTEGestureTracker::FrameListener::onNewFrame(nite::HandTracker &p_HandTracker)
{
    m_OINiTEGestureTracker->m_oHandTracker.readFrame(&m_OINiTEGestureTracker->m_oHandTrackerFrame);
    if(!m_OINiTEGestureTracker->m_oHandTrackerFrame.isValid()) { return; }

//    Underlying OpenNI VideoFrameRef
    m_OINiTEGestureTracker->m_DepthFrame = m_OINiTEGestureTracker->m_oHandTrackerFrame.getDepthFrame();
    if(!m_OINiTEGestureTracker->m_DepthFrame.isValid()) { return; }
//
    const nite::Array<nite::GestureData> &l_aGestures = m_OINiTEGestureTracker->m_oHandTrackerFrame.getGestures();
//
    m_OINiTEGestureTracker->m_eGestureData.clear();
    for (int i = 0; i < l_aGestures.getSize(); ++i)
    {
        if (l_aGestures[i].isComplete())
        {
            m_OINiTEGestureTracker->m_GesturePosition = l_aGestures[i].getCurrentPosition();
            // Debug only
            printNiTEGesturesToString(l_aGestures[i].getType());
            // Start Tracking
            nite::HandId l_iHandID;
            p_HandTracker.startHandTracking(l_aGestures[i].getCurrentPosition(), &l_iHandID);
            // Adapt data
            m_OINiTEGestureTracker->m_eGesture.setGesturePosition
                    (
                            l_aGestures[i].getCurrentPosition().x,
                            l_aGestures[i].getCurrentPosition().y,
                            l_aGestures[i].getCurrentPosition().z
                    );
            m_OINiTEGestureTracker->m_eGesture.setGestureType(convertNiTEGestureType(l_aGestures[i].getType()));
            m_OINiTEGestureTracker->m_eGesture.setGestureState(convertNiTEGestureState(l_aGestures[i]));
            m_OINiTEGestureTracker->m_eGestureData.push_back(m_OINiTEGestureTracker->m_eGesture);
        }
    }
}

/* Helper functions */
void printNiTEGesturesToString(nite::GestureType p_eGestureType)
{
    switch (p_eGestureType) 
    {
        case nite::GESTURE_WAVE:
            break;
        case nite::GESTURE_CLICK:
            std::cout << "GESTURE_CLICK Detected!" << std::endl;
            break;
        case nite::GESTURE_HAND_RAISE:
            break;
        default:
            std::cerr << "INVALID GESTURE TYPE" << std::endl;
    }
}

void printPoint3f(float p_x, float p_y, float p_z)
{
    printf("%f, %f, %f \n", p_x, p_y, p_z);
}

OIGestureType convertNiTEGestureType(nite::GestureType p_eGestureType)
{
    switch (p_eGestureType) 
    {
        case nite::GESTURE_WAVE:
            return OIGestureType::GESTURE_WAVE;
        case nite::GESTURE_CLICK:
            return OIGestureType::GESTURE_CLICK;
        case nite::GESTURE_HAND_RAISE:
            return OIGestureType::GESTURE_HAND_RAISE;
        default:
            std::cerr << "INVALID GESTURE TYPE" << std::endl;
    }
}

OIGestureState convertNiTEGestureState(nite::GestureData p_sGestureData)
{
    if (p_sGestureData.isComplete()) 
    {
        return OIGestureState::GESTURE_IS_COMPLETE;
    } else if (p_sGestureData.isInProgress()) 
    {
        return OIGestureState::GESTURE_IS_IN_PROGRESS;
    } else
        return OIGestureState::GESTURE_IS_ABSENT;
}

// E.O.F