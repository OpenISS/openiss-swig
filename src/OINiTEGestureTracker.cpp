//
// Created by jash on 25/01/19.
//

#include "OINiTEGestureTracker.hpp"

using namespace openiss;

/* Helper functions */
OIGestureType convertNiTEGestureType(nite::GestureType p_eGestureType);
OIGestureState convertNiTEGestureState(nite::GestureData p_sGestureData);
OIHandState convertNiTEHandState(nite::HandData p_sHandData);
void printNiTEGesturesToString(nite::GestureType p_eGestureType);
void printPoint3f(float p_x, float p_y, float p_z);
/**/

/* Constructor */
OINiTEGestureTracker::OINiTEGestureTracker()
{
    m_eNiTEStatus = m_oHandTracker.create();
    if(m_eNiTEStatus == nite::STATUS_OK)
    {
        m_eStatus.setStatus(OIStatusType::STATUS_OK);
    } else
    {
        m_eStatus.setStatus(OIStatusType::STATUS_TRACKER_NOT_INITIALIZED);
    }
    m_oHandTracker.setSmoothingFactor(0.1);
    m_listener = new FrameListener(this);
    if(m_listener)
        m_oHandTracker.addNewFrameListener(m_listener);
    else
        std::cerr << "Failed to add a frame listener!" << std::endl;
}

/* Destructor */
OINiTEGestureTracker::~OINiTEGestureTracker()
{
    m_oHandTrackerFrame.release();
    m_oHandTracker.removeNewFrameListener(m_listener);
    delete m_listener;
    m_oHandTracker.destroy();
}

/* Initialize Tracker */
OIStatusType OINiTEGestureTracker::init()
{
    nite::NiTE::initialize();
    std::cout << "Initialization complete..." << std::endl;
    return m_eStatus.getStatus();
}

/* Stop Tracker */
OIStatusType OINiTEGestureTracker::stop()
{
    nite::NiTE::shutdown();
    return m_eStatus.getStatus();
}

/* Update Tracker data */
OIStatusType OINiTEGestureTracker::update()
{
    return m_eStatus.getStatus();
}

/* Start gesture detection. */
OIStatusType OINiTEGestureTracker::startGestureDetection()
{
    m_oHandTracker.startGestureDetection(nite::GESTURE_CLICK);
    m_oHandTracker.startGestureDetection(nite::GESTURE_WAVE);
//    m_oHandTracker.startGestureDetection(nite::GESTURE_HAND_RAISE);
    std::cout << "Started gesture detection..." << std::endl;
    return m_eStatus.getStatus();
}

/* Stop gesture detection. */
OIStatusType OINiTEGestureTracker::stopGestureDetection()
{
    m_oHandTracker.stopGestureDetection(nite::GESTURE_CLICK);
    m_oHandTracker.stopGestureDetection(nite::GESTURE_WAVE);
//    m_oHandTracker.stopGestureDetection(nite::GESTURE_HAND_RAISE);
    std::cout << "Stopped gesture detection..." << std::endl;
    return m_eStatus.getStatus();
}

/* Start Hand Tracking. */
OIStatusType OINiTEGestureTracker::startHandTracking()
{
    std::cout << "Please perform a gesture to start hand tracking..." << std::endl;
    nite::HandId l_iHandID;
    m_oHandTracker.startHandTracking(m_GesturePosition, &l_iHandID);
    std::cout << "Hand tracking started..." << std::endl;
    return m_eStatus.getStatus();
}

/* Stop Hand Tracking. */
OIStatusType OINiTEGestureTracker::stopHandTracking()
{
    m_oHandTracker.stopHandTracking(m_iHandID);
    std::cout << "Hand tracking stopped..." << std::endl;
    return m_eStatus.getStatus();
}

/* Return available gestures. */
std::vector<OIGestureData> OINiTEGestureTracker::getGestures()
{
    return m_eGestureData;
}

/* Return available hands. */
std::vector<OIHandData> OINiTEGestureTracker::getHands()
{
    return m_eHandData;
}

/* Return most recent frame. */
GFrame* OINiTEGestureTracker::getDepthFrame()
{
    return &m_listener->m_GFrame;
}

/* Real coordinates to Projective Coordinates*/
void OINiTEGestureTracker::convertHandCoordinatesToDepth(float p_x, float p_y, float p_z, float *p_OutX, float *p_OutY)
{
    m_oHandTracker.convertHandCoordinatesToDepth(p_x, p_y, p_z, p_OutX, p_OutY);
}

/* Projective coordinates to Real Coordinates*/
void OINiTEGestureTracker::convertDepthCoordinatesToHand(int p_x, int p_y, int p_z, float *p_OutX, float *p_OutY)
{
    m_oHandTracker.convertDepthCoordinatesToHand(p_x, p_y, p_z, p_OutX, p_OutY);
}

/* Callback function. Here the adaption of data takes place. */
void OINiTEGestureTracker::FrameListener::onNewFrame(nite::HandTracker &p_HandTracker)
{
    m_OINiTEGestureTracker->m_oHandTracker.readFrame(&m_OINiTEGestureTracker->m_oHandTrackerFrame);
    if(!m_OINiTEGestureTracker->m_oHandTrackerFrame.isValid()) { return; }

/*    Underlying OpenNI VideoFrameRef Depth Frame */
    m_OINiTEGestureTracker->m_DepthFrame = m_OINiTEGestureTracker->m_oHandTrackerFrame.getDepthFrame();
    if(!m_OINiTEGestureTracker->m_DepthFrame.isValid()) { return; }
/**/
    const nite::Array<nite::GestureData> &l_aGestures = m_OINiTEGestureTracker->m_oHandTrackerFrame.getGestures();
/**/
    m_OINiTEGestureTracker->m_eGestureData.clear();
    for (int i = 0; i < l_aGestures.getSize(); ++i)
    {
        if (l_aGestures[i].isComplete())
        {
            m_OINiTEGestureTracker->m_GesturePosition = l_aGestures[i].getCurrentPosition();
            /* Debug only */
            printNiTEGesturesToString(l_aGestures[i].getType());
            /* Start Hand Tracking */
            nite::HandId l_iHandID;
            p_HandTracker.startHandTracking(l_aGestures[i].getCurrentPosition(), &l_iHandID);
            /* Adapt data */
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

/**/
    const nite::Array<nite::HandData> &l_aHands = m_OINiTEGestureTracker->m_oHandTrackerFrame.getHands();
/**/
    m_OINiTEGestureTracker->m_eHandData.clear();
    for (int i = 0; i < l_aHands.getSize(); ++i)
    {
        /* Adapt data */
        m_OINiTEGestureTracker->m_eHand.setHandPosition
                (
                        l_aHands[i].getPosition().x,
                        l_aHands[i].getPosition().y,
                        l_aHands[i].getPosition().z
                );
        m_OINiTEGestureTracker->m_eHand.setHandState(convertNiTEHandState(l_aHands[i]));
        m_OINiTEGestureTracker->m_eHand.setHandID(l_aHands[i].getId());
        m_OINiTEGestureTracker->m_eHandData.push_back(m_OINiTEGestureTracker->m_eHand);
        if(l_aHands[i].isTracking())
        {
            std::cout << "Tracking Hand with id : " << l_aHands[i].getId() << std::endl;
            std::cout << "Hand Coordinates : "; 
            printPoint3f( l_aHands[i].getPosition().x,
                          l_aHands[i].getPosition().y,
                          l_aHands[i].getPosition().z );
        }
    }
    m_GFrame.setHeight(m_OINiTEGestureTracker->m_DepthFrame.getVideoMode().getResolutionY());
    m_GFrame.setWidth(m_OINiTEGestureTracker->m_DepthFrame.getVideoMode().getResolutionX());
    m_GFrame.setDepthData(static_cast<const u_int16_t*>(m_OINiTEGestureTracker->m_DepthFrame.getData()));
}

/**********************************************************************************************************************/

/* Helper Functions definitions. */
void printNiTEGesturesToString(nite::GestureType p_eGestureType)
{
    switch (p_eGestureType) {
        case nite::GESTURE_WAVE:
            std::cout << "GESTURE_WAVE Detected!" << std::endl;
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
/**/
void printPoint3f(float p_x, float p_y, float p_z)
{
    printf("%f, %f, %f \n", p_x, p_y, p_z);
}
/**/
OIGestureType convertNiTEGestureType(nite::GestureType p_eGestureType)
{
    switch (p_eGestureType) {
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
/**/
OIGestureState convertNiTEGestureState(nite::GestureData p_sGestureData)
{
    if (p_sGestureData.isComplete()) {
        return OIGestureState::GESTURE_IS_COMPLETE;
    } else if (p_sGestureData.isInProgress()) {
        return OIGestureState::GESTURE_IS_IN_PROGRESS;
    } else
        return OIGestureState::GESTURE_IS_ABSENT;
}
/**/
OIHandState convertNiTEHandState(nite::HandData p_sHandData)
{
    if (p_sHandData.isLost()) {
        return OIHandState::HAND_IS_LOST;
    } else if (p_sHandData.isNew()) {
        return OIHandState::HAND_IS_NEW;
    } else if (p_sHandData.isTracking()) {
        return OIHandState::HAND_IS_TRACKING;
    } else if (p_sHandData.isTouchingFov()) {
        return OIHandState::HAND_IS_TOUCHING_FOV;
    } else
        std::cerr << "HAND_IS_ABSENT" << std::endl;
    return OIHandState::HAND_IS_ABSENT;
}
// E.O.F