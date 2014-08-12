//
//  IShooter.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_IShooter_h
#define spaceUnit_IShooter_h

#include "cocos2d.h"
#include "SpaceObject.h"
#include <vector>

class IShooter {
public:
	virtual void tick(float dt) = 0;
	virtual void shoot(cocos2d::CCPoint from, cocos2d::CCPoint to, int bulletType) = 0;
	virtual void shoot(SpaceObject *owner, cocos2d::CCPoint from, cocos2d::CCPoint to, int bulletType) = 0;
	virtual void shoot(SpaceObject *owner, cocos2d::CCPoint to, int bulletType) = 0;
    
    //std::vector<Bullet *> * getBullets();
};

#endif
