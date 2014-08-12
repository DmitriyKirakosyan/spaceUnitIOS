//
//  HeroSkin.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_HeroSkin_h
#define spaceUnit_HeroSkin_h

#include "AnimatedSprite.h"
#include "cocos2d.h"
#include "SpaceObject.h"

class HeroSkin {
protected:
    SpaceObject *_owner;
public:
    HeroSkin(SpaceObject *owner) {
        _owner = owner;
    }
    
	virtual void tick(float delta, bool moving) = 0;
    
	virtual bool rotatable() = 0;
};

#endif
