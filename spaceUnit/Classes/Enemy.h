//
//  Enemy.h
//  spaceUnit
//
//  Created by Dmitriy on 12/29/12.
//
//

#ifndef __spaceUnit__Enemy__
#define __spaceUnit__Enemy__

#include "MovingSpaceObject.h"

class Enemy : public MovingSpaceObject
{
public:
    Enemy(cocos2d::CCSize screenSize, bool teleportOnBorder = false);
    void simpleMove();
    
    void setRandomBehaviour();
    void setRandomBorderPosition();
    void setRandomLook();
    
    inline void setSpeedX(float value) { _speedX = value; }
    inline void setSpeedY(float value) { _speedY = value; }
    inline void setSpeedRotate(float value) { _speedRotate = value; }
    
    static inline int getSizeImgArray() { return 4; }
    
private:
    
    void checkBoarderTeleport();
    
    float _speedX;
    float _speedY;
    float _speedRotate;
    bool _teleportOnBoarder;

};

#endif /* defined(__spaceUnit__Enemy__) */

