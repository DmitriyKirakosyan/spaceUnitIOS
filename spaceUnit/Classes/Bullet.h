//
//  Bullet.h
//  spaceUnit
//
//  Created by Dmitriy on 2/8/13.
//
//

#ifndef spaceUnit_Bullet_h
#define spaceUnit_Bullet_h

#include "cocos2d.h"
#include "MovingSpaceObject.h"

class Bullet : public MovingSpaceObject
{
private:
    const char *_file;
    SpaceObject *_owner;
    
public:
    Bullet(const char *file, SpaceObject *owner)
    : MovingSpaceObject(cocos2d::CCDirector::sharedDirector()->getWinSize(), file, false, NONE)
    {
        _file = file;
        _owner = owner;
    }
    
    Bullet(const char *file)
    : MovingSpaceObject(cocos2d::CCDirector::sharedDirector()->getWinSize(), file, false, NONE) {
        _file = file;
        _owner = NULL;
    }
    
    SpaceObject *getOwner() { return _owner;}
};

#endif
