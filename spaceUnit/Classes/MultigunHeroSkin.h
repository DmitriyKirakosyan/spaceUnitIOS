//
//  MultigunHeroSkin.h
//  spaceUnit
//
//  Created by PC on 8/12/14.
//
//

#ifndef spaceUnit_MultigunHeroSkin_h
#define spaceUnit_MultigunHeroSkin_h

#include "Assets.h"
#include "SpaceObject.h"
#include "HeroSkin.h"

class MultigunHeroSkin : public HeroSkin {
public:
    MultigunHeroSkin(SpaceObject *owner) : HeroSkin(owner) {
		owner->initWithFile(Assets::superShip);
	}
    
	
	bool rotatable() { return false; }
    
	
	void tick(float delta, bool moving) {
		//this.setRegion(moving ? Assets.mineActive : Assets.minePassive);
	}
};


#endif
