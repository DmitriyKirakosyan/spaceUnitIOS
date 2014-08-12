//
//  IBlowMaker.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_IBlowMaker_h
#define spaceUnit_IBlowMaker_h

//#include "SpaceObject.h"
class SpaceObject;
class IBlowMaker {
public:
	virtual void makeBlow(SpaceObject *object) = 0;
};

#endif
