//
//  SimpleGun.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_SimpleGun_h
#define spaceUnit_SimpleGun_h

#include "AGun.h"

class SimpleGun : public AGun {
    
public:
    SimpleGun(float reloadTime) : AGun(reloadTime) {
	}
    
	SimpleGun() : AGun(0.5f) {
	}
    
	
	void shoot(IShooter *shooter, SpaceObject *owner, cocos2d::CCPoint target) {
        AGun::shoot(shooter, owner, target);
		shooter->shoot(owner, target, Shooter::HERO_BULLET);
	}
    
};


#endif
