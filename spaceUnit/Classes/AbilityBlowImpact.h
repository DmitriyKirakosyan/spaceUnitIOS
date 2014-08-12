//
//  AbilityBlowImpact.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_AbilityBlowImpact_h
#define spaceUnit_AbilityBlowImpact_h

class AbilityBlowImpact : public BlowImpact {
public:
    AbilityBlowImpact(float x, float y, IBlowMaker *blowMaker, cocos2d::CCNode *parentNode)
    : BlowImpact(x, y, blowMaker, parentNode) {
	}
    
	
	void execute(SpaceObject *object) {
        
		if (typeid(*object) !=  typeid(Ship)) {
            BlowImpact::execute(object);
		}
	}
    
};

#endif
