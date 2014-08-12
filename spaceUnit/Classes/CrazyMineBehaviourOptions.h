//
//  CrazyMineBehaviourOptions.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_CrazyMineBehaviourOptions_h
#define spaceUnit_CrazyMineBehaviourOptions_h

#include "BehaviourOptions.h"

class CrazyMineBehaviourOptions : public BehaviourOptions {
public:
    IBlowMaker *blowMaker;
    IImpactMaker *impactMaker;
    
    CrazyMineBehaviourOptions(IBlowMaker *blowMaker, IImpactMaker *impactMaker) {
        this->blowMaker = blowMaker;
        this->impactMaker = impactMaker;
    }
};
#endif
