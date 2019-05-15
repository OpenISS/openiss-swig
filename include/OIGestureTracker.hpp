#ifndef OIGESTURETRACKER_H_
#define OIGESTURETRACKER_H_

#include <vector>
#include "OIStatus.hpp"
#include "OIGFrame.hpp"
#include "OIGestureData.hpp"
#include "OIHandData.hpp"

namespace openiss
{
    class OIGestureTracker
    {
    public:
        virtual ~OIGestureTracker() = default;

// Initialize/Stop devices and API components.
        virtual OIStatusType init() = 0;
// Gather most recent past data from sensor frame.
        virtual OIStatusType update() = 0;
// Release memory, resources.
        virtual OIStatusType stop() = 0;

// Start/Stop gesture detection and get a collection of gestures available.
        virtual OIStatusType startGestureDetection() = 0;
        virtual OIStatusType stopGestureDetection() = 0;
        virtual std::vector<OIGestureData> getGestures() = 0;

// Start/Stop hand tracking and get a collection of hands available.
        virtual OIStatusType startHandTracking() = 0;
        virtual OIStatusType stopHandTracking() = 0;
        virtual std::vector<OIHandData> getHands() = 0;

//      Real coordinates to Projective coordinates.
        virtual void convertHandCoordinatesToDepth(float p_x, float p_y, float p_z, float* p_OutX, float* p_OutY) = 0;
        virtual void convertDepthCoordinatesToHand(int p_x, int p_y, int p_z, float* p_OutX, float* p_OutY) = 0;

//      TODO: Needs to be refactored up in the hierarchy.
        virtual GFrame* getDepthFrame() = 0;
    };
}

#endif //OIGESTURETRACKER_H_
