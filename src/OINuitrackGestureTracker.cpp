#include "OINuitrackGestureTracker.hpp"

using namespace openiss;

/* Helper functions */
OIGestureType convertNuiTrackGestureType( tdv::nuitrack::GestureType p_eGestureType );

/* Constructor */
OINuitrackGestureTracker::OINuitrackGestureTracker() = default;

/* Destructor */
OINuitrackGestureTracker::~OINuitrackGestureTracker() = default;

/* Initialize Tracker */
OIStatusType OINuitrackGestureTracker::init()
{
  tdv::nuitrack::Nuitrack::init();
  m_eStatus.setStatus(OIStatusType::STATUS_OK);
//
  m_DepthSensor = tdv::nuitrack::DepthSensor::create();
  m_gestureRecognizer = tdv::nuitrack::GestureRecognizer::create();
  m_HandTracker = tdv::nuitrack::HandTracker::create();
  m_UserTracker = tdv::nuitrack::UserTracker::create();
//
  m_DepthSensor->connectOnNewFrame(std::bind(&OINuitrackGestureTracker::onNewDepthFrame, this, std::placeholders::_1));
  m_gestureRecognizer->connectOnNewGestures(std::bind( &OINuitrackGestureTracker::onNewGestures, this, std::placeholders::_1 ));
  m_gestureRecognizer->connectOnUserStateChange(std::bind( &OINuitrackGestureTracker::onUserStateChange, this, std::placeholders::_1 ));
  m_HandTracker->connectOnUpdate( std::bind(&OINuitrackGestureTracker::onHandUpdate, this, std::placeholders::_1 ));
  m_UserTracker->connectOnUpdate( std::bind(&OINuitrackGestureTracker::onUserUpdate, this, std::placeholders::_1) );
  m_UserTracker->connectOnNewUser( std::bind(&OINuitrackGestureTracker::onNewUser, this, std::placeholders::_1) );
  m_UserTracker->connectOnLostUser( std::bind(&OINuitrackGestureTracker::onLostUser, this, std::placeholders::_1) );
//
  m_DepthSensor->setMirror(false);
  tdv::nuitrack::Nuitrack::run();
  return m_eStatus.getStatus();
}

/* Update Tracker data */
OIStatusType OINuitrackGestureTracker::update()
{
  tdv::nuitrack::Nuitrack::update();
  return m_eStatus.getStatus();
}

/* Stop Tracker */
OIStatusType OINuitrackGestureTracker::stop()
{
  m_gestureRecognizer->destroyGestureRecognizer();
  return m_eStatus.getStatus();
}

/* Start gesture detection. */
OIStatusType OINuitrackGestureTracker::startGestureDetection()
{
  return m_eStatus.getStatus();
}

/* Stop gesture detection. */
OIStatusType OINuitrackGestureTracker::stopGestureDetection()
{
  stop();
  return m_eStatus.getStatus();
}

/* Start Hand Tracking. */
OIStatusType OINuitrackGestureTracker::startHandTracking()
{
  return m_eStatus.getStatus();
}

/* Stop Hand Tracking. */
OIStatusType OINuitrackGestureTracker::stopHandTracking()
{
  return m_eStatus.getStatus();

}

/* Return available gestures. */
std::vector<OIGestureData> OINuitrackGestureTracker::getGestures()
{
  return m_eGestureData;
}

/* Return available hands. */
std::vector<OIHandData> OINuitrackGestureTracker::getHands()
{
  return m_eHandData;
}

/* Return most recent frame. */
OIDepthFrame* OINuitrackGestureTracker::getDepthFrame()
{
  return &m_DepthFrame;
}

/* Real coordinates to Projective Coordinates*/
void OINuitrackGestureTracker::convertHandCoordinatesToDepth(float p_x, float p_y, float p_z, float *p_OutX, float *p_OutY)
{
  m_projectiveCoordinates = m_DepthSensor->convertRealToProjCoords(-p_x, p_y, p_z); // <- p_x coordinate manually negated here!
  *p_OutX = m_projectiveCoordinates.x;
  *p_OutY = m_projectiveCoordinates.y;
}

/* Projective coordinates to Real Coordinates*/
void OINuitrackGestureTracker::convertDepthCoordinatesToHand(int p_x, int p_y, int p_z, float *p_OutX, float *p_OutY)
{
  // TODO: Test these values and p_x probably needs to be negated here as well!
  tdv::nuitrack::Vector3 l_projectiveCoordinates;
  l_projectiveCoordinates.x = (float) p_x;
  l_projectiveCoordinates.y = (float) p_y;
  l_projectiveCoordinates.z = (float) p_z;
  m_realCoordinates = m_DepthSensor->convertProjToRealCoords(l_projectiveCoordinates);
  *p_OutX = m_realCoordinates.x;
  *p_OutY = m_realCoordinates.y;
}

void OINuitrackGestureTracker::onNewDepthFrame(tdv::nuitrack::DepthFrame::Ptr p_Frame)
{
  m_outputMode = m_DepthSensor->getOutputMode();
  m_DepthFrame.setHeight(m_outputMode.yres);
  m_DepthFrame.setWidth(m_outputMode.xres);
  m_DepthFrame.setDepthData(p_Frame->getData());
}

void OINuitrackGestureTracker::onNewGestures( const tdv::nuitrack::GestureData::Ptr p_gestureData)
{
  this->m_eGestureData.clear();
  std::vector<tdv::nuitrack::Gesture> gestures = p_gestureData->getGestures();
  for (const auto &gesture : gestures)
  {
    m_eGesture.setGestureType(convertNuiTrackGestureType(gesture.type));
    this->m_eGestureData.push_back(m_eGesture);
  }
}

void OINuitrackGestureTracker::onHandUpdate(tdv::nuitrack::HandTrackerData::Ptr p_handData)
{
  this->m_eHandData.clear();
  std::vector<tdv::nuitrack::UserHands> hands = p_handData->getUsersHands();

  for (const auto &hand :  hands)
  {
    ++m_handID;
    m_eLeftHand.setHandPosition
        (
            hand.leftHand->xReal,
            hand.leftHand->yReal,
            hand.leftHand->zReal
        );
    m_eLeftHand.setHandID(m_handID);

    ++m_handID;
    m_eRightHand.setHandPosition
        (
            hand.rightHand->xReal,
            hand.rightHand->yReal,
            hand.rightHand->zReal
        );
    m_eRightHand.setHandID(m_handID);
    this->m_eHandData.push_back(m_eRightHand);
    this->m_eHandData.push_back(m_eLeftHand);
  }
  m_handID = 0;
}

void OINuitrackGestureTracker::onUserUpdate(tdv::nuitrack::UserFrame::Ptr p_userFrameData)
{
  auto users = p_userFrameData->getUsers();
  for (auto user : users)
  {
    //
  }
}

/* User Module being used here to set Hand states which by default are not given by NuiTrack
 * But are desirable for extra control over application layer.*/
void OINuitrackGestureTracker::onUserStateChange(tdv::nuitrack::UserStateData::Ptr p_userStateData)
{
  auto userStates = p_userStateData->getUserStates();
  for(auto userState : userStates)
  {
    if(userState.state == tdv::nuitrack::UserStateType::USER_ACTIVE)
    {
      m_eRightHand.setHandState(OIHandState::HAND_IS_TRACKING);
      m_eLeftHand.setHandState(OIHandState::HAND_IS_TRACKING);
    }
  }
}

void OINuitrackGestureTracker::onNewUser(int p_userID)
{
  std::cout << "New User in Frame!!" << std::endl;
  m_eRightHand.setHandState(OIHandState::HAND_IS_NEW);
  m_eLeftHand.setHandState(OIHandState::HAND_IS_NEW);
}

void OINuitrackGestureTracker::onLostUser(int p_userID)
{
  m_eRightHand.setHandState(OIHandState::HAND_IS_LOST);
  m_eLeftHand.setHandState(OIHandState::HAND_IS_LOST);
  std::cout << "Lost User in Frame!!" << std::endl;
}

/**/
OIGestureType convertNuiTrackGestureType(tdv::nuitrack::GestureType p_eGestureType)
{
  switch (p_eGestureType)
  {
    case tdv::nuitrack::GestureType::GESTURE_PUSH:
      std::cout << "NuiTrack: GESTURE_PUSH" << std::endl;
      return OIGestureType::GESTURE_PUSH;

    case tdv::nuitrack::GestureType::GESTURE_SWIPE_DOWN:
      std::cout << "NuiTrack: GESTURE_SWIPE_DOWN" << std::endl;
      return OIGestureType::GESTURE_SWIPE_DOWN;

    case tdv::nuitrack::GestureType::GESTURE_SWIPE_UP:
      std::cout << "NuiTrack: GESTURE_SWIPE_UP" << std::endl;
      return OIGestureType::GESTURE_SWIPE_UP;

    case tdv::nuitrack::GestureType::GESTURE_SWIPE_LEFT:
      std::cout << "NuiTrack: GESTURE_SWIPE_LEFT" << std::endl;
      return OIGestureType::GESTURE_SWIPE_LEFT;

    case tdv::nuitrack::GestureType::GESTURE_SWIPE_RIGHT:
      std::cout << "NuiTrack: GESTURE_SWIPE_RIGHT" << std::endl;
      return OIGestureType::GESTURE_SWIPE_RIGHT;

    case tdv::nuitrack::GestureType::GESTURE_WAVING:
      std::cout << "NuiTrack: GESTURE_WAVING" << std::endl;
      return OIGestureType::GESTURE_WAVING;
    default:
      throw std::runtime_error("No such gesture type!");
  }
}

// E.O.F