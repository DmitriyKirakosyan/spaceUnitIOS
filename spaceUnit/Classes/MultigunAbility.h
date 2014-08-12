//
//  MultigunAbility.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_MultigunAbility_h
#define spaceUnit_MultigunAbility_h

#include "Ability.h"
#include "AbilityENUM.h"
#include "AGun.h"
#include "MultiGun.h"
#include "HeroSkin.h"
#include "MultigunHeroSkin.h"

class MultigunAbility : public Ability {
    
private:
    Ship *_heroShip;
	AGun *_heroGun;
	float ABIL_TIME;
	float _abilTimeLeft;
	bool _isActive;
    HeroSkin *_heroSkin;
    
    
    
public:
	MultigunAbility(Ship *heroShip) : Ability(MULTIGUN, 20) {
        ABIL_TIME = 5;
		_heroShip = heroShip;
		_isActive = false;
	}
    
	
	void tick(float delta) {
        Ability::tick(delta);
		if (_isActive) {
			_abilTimeLeft-= delta;
			if (_abilTimeLeft <= 0) {
				this->deactivate();
			}
			else if (_heroShip->getGun() != NULL) {
				if (_heroShip->getGun()->isReloading()) {
					_heroShip->setRotationSpeed(4);
				} else {
					_heroShip->setRotationSpeed(0);
				}
			}
		}
	}
    
	
	void deactivate() {
		if (!_isActive) return;
		_isActive = false;
		_heroShip->setGun(_heroGun);
		_heroShip->setRotationSpeed(0);
		_heroShip->setSkin(_heroSkin);
	}
    
    
	void activate() {
        Ability::activate();
		_isActive = true;
		_abilTimeLeft = ABIL_TIME;
		_heroGun = _heroShip->getGun();
        _heroSkin = _heroShip->getSkin();
		_heroShip->setGun(new MultiGun());
        _heroShip->setSkin(new MultigunHeroSkin(_heroShip));
	}
};


#endif
