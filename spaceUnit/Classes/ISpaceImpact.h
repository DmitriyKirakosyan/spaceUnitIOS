//
//  ISpaceImpact.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_ISpaceImpact_h
#define spaceUnit_ISpaceImpact_h

#include "SpaceObject.h"

class ISpaceImpact {
public:
	virtual void tick(float dt) = 0;
    
	/**
	 * @return Can be null
	 */
	//virtual const char * getImage() = 0;
    
	virtual void start() = 0;
	virtual void stop() = 0;
	virtual bool isComplete() = 0;
    
	virtual void execute(SpaceObject *object) = 0;
};

#endif
