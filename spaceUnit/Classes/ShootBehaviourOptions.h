//
//  Header.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_ShootBehaviourOptions_h
#define spaceUnit_ShootBehaviourOptions_h

#include "BehaviourOptions.h"


class ShootBehaviourOptions : public  BehaviourOptions {
public:
    float frequency;
    SpaceObject *targetToShoot;
    IShooter *shooter;
    
    ShootBehaviourOptions(float frequency, SpaceObject *targetToShoot, IShooter *shooter) {
        this->frequency = frequency;
        this->targetToShoot = targetToShoot;
        this->shooter = shooter;
    }
};

#endif
