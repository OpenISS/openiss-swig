//
// Created by jashanjotsingh on 12/04/19.
//

#ifndef OISTATE_H_
#define OISTATE_H_

namespace openiss
{

    enum class OIGestureState
    {
        GESTURE_IS_ABSENT       ,
        GESTURE_IS_COMPLETE     ,
        GESTURE_IS_IN_PROGRESS  ,
    };

    enum class OIHandState
    {
        HAND_IS_ABSENT          ,
        HAND_IS_NEW             ,
        HAND_IS_LOST            ,
        HAND_IS_TRACKING        ,
        HAND_IS_TOUCHING_FOV    ,
    };
}
#endif //OISTATE_H_
