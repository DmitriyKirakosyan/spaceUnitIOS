//
//  Ship.h
//  spaceUnit
//
//  Created by Dmitriy on 1/2/13.
//
//

#ifndef __spaceUnit__Ship__
#define __spaceUnit__Ship__

#include "MovingSpaceObject.h"

class Ship : public MovingSpaceObject
{
public:
    
    Ship(cocos2d::CCSize screenSize):MovingSpaceObject(screenSize, false)
    {
        _targetPosition = cocos2d::CCPointZero;
        _moving = false;
        this->initWithFile("ShipView.png");
        this->setScale(1.0f);
    }
    
    inline cocos2d::CCPoint getTargetPosition() { return _targetPosition; }
    inline void setTargetPosition(cocos2d::CCPoint value) { _targetPosition = value; }
    
    inline bool isMoving() { return _moving; }
    inline void setMoving(bool value) { _moving = value; }
    
private:
	cocos2d::CCPoint _targetPosition;
    bool _moving;


};

#endif /* defined(__spaceUnit__Ship__) */
