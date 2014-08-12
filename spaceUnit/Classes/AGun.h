//
//  AGun.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_AGun_h
#define spaceUnit_AGun_h

#include "IShooter.h"

class AGun {
private:
    float _reloadTime;
	float _reloadTimeLeft;
	bool _readyForShoot;
    
public:
    AGun(float reloadTime) {
		_reloadTime = reloadTime;
		_reloadTimeLeft = 0;
		_readyForShoot = false;
	}
    
	bool isReloading() { return _reloadTimeLeft > 0; }
    
	virtual void tick(float delta) {
		_reloadTimeLeft-= delta;
        
		if (_reloadTimeLeft <= 0)
		{
			_readyForShoot = true;
			_reloadTimeLeft = 0;
		}
	}
    
	virtual void shoot(IShooter *shooter, SpaceObject *owner, cocos2d::CCPoint target) {
		_readyForShoot = false;
		_reloadTimeLeft = _reloadTime;
	}
    
	bool isReadyForShoot() { return _readyForShoot; }
    
};


#endif
