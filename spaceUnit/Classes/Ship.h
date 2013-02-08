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
    Ship(cocos2d::CCSize screenSize, int reloadTime);
    
    void tick();
    
    inline cocos2d::CCPoint getTargetPosition() { return _targetPosition; }
    inline void setTargetPosition(cocos2d::CCPoint value) { _targetPosition = value; }
    inline void setTargetForShooting(cocos2d::CCPoint value) { _targetForShooting = value; }
    
    inline bool isMoving() { return _moving; }
    inline void setMoving(bool value) { _moving = value; }
    
    inline bool isShooting() { return _shooting; }
    inline void setShooting(bool value) { _shooting = value; }
    
    inline bool isReadyForShoot() { return _readyForShoot; }
    
private:
	cocos2d::CCPoint _targetPosition;
    cocos2d::CCPoint _targetForShooting;
    bool _moving;
    bool _shooting;
    
    int _reloadTime;
    int _currentReloadTime;
    bool _readyForShoot;

};

#endif /* defined(__spaceUnit__Ship__) */
