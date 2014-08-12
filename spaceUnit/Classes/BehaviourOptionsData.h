//
//  BehaviourOptionsData.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_BehaviourOptionsData_h
#define spaceUnit_BehaviourOptionsData_h

#include "IShooter.h"
#include "IBlowMaker.h"
#include "IImpactMaker.h"


class BehaviourOptionsData {
public:
     IShooter *shooter;
     IBlowMaker *blowMaker;
     Ship *heroShip;
     IImpactMaker *impactMaker;
     
     
     BehaviourOptionsData(IShooter *shooter, IBlowMaker *blowMaker, Ship *heroShip, IImpactMaker *impactMaker) {
     this->shooter = shooter;
     this->blowMaker = blowMaker;
     this->heroShip = heroShip;
     this->impactMaker = impactMaker;
     }
};
#endif
