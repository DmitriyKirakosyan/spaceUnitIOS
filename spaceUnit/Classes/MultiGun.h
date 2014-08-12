//
//  MultiGun.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_MultiGun_h
#define spaceUnit_MultiGun_h

#include "AGun.h"
#include "Shooter.h"

class Ship;

class MultiGun : public AGun {
private:
    const int GUNS_NUM = 5;
    const float PI = 3.141592;

public:
    MultiGun() :AGun(0.2f) {}
    
	void shoot(IShooter *shooter, SpaceObject *owner, cocos2d::CCPoint target) {
        AGun::shoot(shooter, owner, target);
		double step = PI * 2 / GUNS_NUM;
		float targetX, targetY;
		float fromX, fromY;
		float cos_val, sin_val;
		double ownerAngle = owner->getRotation() / 180 * PI;
        
		for (double angle = 0; angle < 2* PI; angle += step) {
			cos_val = (float)cos(angle + ownerAngle);
			sin_val = (float)sin(angle + ownerAngle);
			targetX = owner->getPosition().x + cos_val * 100;
			targetY = owner->getPosition().y + sin_val * 100;
			fromX = owner->getPosition().x + cos_val * owner->getContentSize().width / 2;
			fromY = owner->getPosition().y + sin_val * owner->getContentSize().height / 2;
			shooter->shoot(owner, ccp(fromX, fromY), ccp(targetX, targetY), Shooter::HERO_BULLET);
		}
       
	}
};


#endif
