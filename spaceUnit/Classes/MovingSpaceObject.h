//
//  MovingSpaceObject.h
//  spaceUnit
//
//  Created by Dmitriy on 1/2/13.
//
//

#ifndef __spaceUnit__MovingSpaceObject__
#define __spaceUnit__MovingSpaceObject__

#include "SpaceObject.h"

class MovingSpaceObject : public SpaceObject
{
public:
    MovingSpaceObject(cocos2d::CCSize screenSize, bool randomScale):SpaceObject(screenSize, randomScale)
    {
        _generalSpeed = 0;
    }
    
    void moveTo(float targetX, float targetY);
    void rotateTo(float targetX, float targetY);
    void setRandomGeneralSpeed();
    void setGeneralSpeed(float value);


private:
    float _generalSpeed;

    
};

#endif /* defined(__spaceUnit__MovingSpaceObject__) */
