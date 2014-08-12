//
//  IImpactMaker.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_IImpactMaker_h
#define spaceUnit_IImpactMaker_h

class IImpactMaker {
public:
	virtual void createBlow(float x, float y) = 0;
	virtual void createAbilityBlow(float x, float y) = 0;
};

#endif
