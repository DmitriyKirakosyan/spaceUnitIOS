//
//  Ability.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_Ability_h
#define spaceUnit_Ability_h

#include "AbilityENUM.h"
#include "Ship.h"
#include "IImpactMaker.h"

class Ability {
    
private:
    int _abilityType;
	float _cooldown;
	float _timeLeft;
	bool _ready;
    
public:
    static Ability * create(int ability, Ship *heroShip, IImpactMaker *impactMaker);
	static Ability * create(int ability, Ship *heroShip);
    
    
	Ability(int abilityType, float cooldown) {
		_cooldown = cooldown;
		_abilityType = abilityType;
		_timeLeft = _cooldown;
        _ready = false;
	}
    
	int getType() { return _abilityType; }
    
	bool isReady() { return _ready; }
    
	float timeToReady() { return _timeLeft; }
    
	float getCooldown() { return _cooldown; }
    
	virtual void activate() {
		if (!_ready) {
            //throw new Error("cant activate ability. dont ready");
        }
		_ready = false;
		_timeLeft = _cooldown;
	}
    
	void deactivate() {
        
	}
    
	virtual void tick(float dt) {
		if (!_ready) {
			_timeLeft -= dt;
			if (_timeLeft <= 0) {
				_ready = true;
				_timeLeft = 0;
			}
		}
	}
};

#endif
