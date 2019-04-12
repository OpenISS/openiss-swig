//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OIGESTURETYPE_H_
#define OIGESTURETYPE_H_

namespace openiss
{
    enum OIGestureType
    {
        // Default Initialized
        GESTURE_ALL,

        // NiTE2 Gesture Types
        GESTURE_WAVE,
        GESTURE_CLICK,
        GESTURE_HAND_RAISE,

        // Nuitrack Gesture Types
        GESTURE_SWIPE_LEFT,
        GESTURE_SWIPE_RIGHT,
        GESTURE_SWIPE_UP,
        GESTURE_SWIPE_DOWN,
        GESTURE_PUSH,
        GESTURE_WAVING
    };
}
#endif //OIGESTURETYPE_H_