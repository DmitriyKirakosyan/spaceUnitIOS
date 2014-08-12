//
//  AEnemyBehaviourWithTarget.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_AEnemyBehaviourWithTarget_h
#define spaceUnit_AEnemyBehaviourWithTarget_h

#include "AEnemyBehaviour.h"
#include "SpaceObject.h"

class AEnemyBehaviourWithTarget : public AEnemyBehaviour {
protected:
    SpaceObject *_target;
    
public:
    AEnemyBehaviourWithTarget(int name, Enemy *enemy, SpaceObject *target, BehaviourOptions *options)
    : AEnemyBehaviour(name, enemy, options) {
        _target = target;
    }
    
    AEnemyBehaviourWithTarget(int name, Enemy *enemy, SpaceObject *target)
    :AEnemyBehaviour(name, enemy, NULL) {
        _target = target;
    }
};


#endif
