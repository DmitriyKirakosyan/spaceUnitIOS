//
//  Header.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_BlowAbility_h
#define spaceUnit_BlowAbility_h

#include "Ability.h"
class BlowAbility : public Ability {
private:
    IImpactMaker *_imapctMaker;
	Ship *_heroShip;
    
public:
	BlowAbility(Ship *heroShip, IImpactMaker *impactMaker) : Ability(BLOW, 10) {
		_heroShip = heroShip;
		_imapctMaker = impactMaker;
	}
    
	// Override
	void activate() {
        Ability::activate();
        _imapctMaker->createAbilityBlow(_heroShip->getPosition().x,
                                        _heroShip->getPosition().y);
    }
};

#endif
