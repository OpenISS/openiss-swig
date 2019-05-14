//
// Created by jash on 25/01/19.
//

#ifndef RT_SKEL_ROS_GESTURE_OIGESTUREDICTIONARY_H
#define RT_SKEL_ROS_GESTURE_OIGESTUREDICTIONARY_H

namespace openiss
{
    enum class OIGestureType
    {
        /* Default Initialized */
        GESTURE_ALL,

        /* NiTE2 Gesture Types */
        GESTURE_WAVE,
        GESTURE_CLICK,
        GESTURE_HAND_RAISE,

        /* Nuitrack Gesture Types */
        GESTURE_SWIPE_LEFT,
        GESTURE_SWIPE_RIGHT,
        GESTURE_SWIPE_UP,
        GESTURE_SWIPE_DOWN,
        GESTURE_PUSH,
        GESTURE_WAVING
    };
}

#endif //RT_SKEL_ROS_GESTURE_OIGESTUREDICTIONARY_H
