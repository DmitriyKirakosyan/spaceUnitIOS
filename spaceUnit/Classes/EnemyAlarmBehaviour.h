//
//  EnemyAlarmBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyAlarmBehaviour_h
#define spaceUnit_EnemyAlarmBehaviour_h

#include "AEnemyBehaviourWithTarget.h"
#include "AlarmBehaviourOptions.h"

class EnemyAlarmBehaviour : public AEnemyBehaviourWithTarget {
private:
    AlarmBehaviourOptions *_options;

public:
    EnemyAlarmBehaviour (Enemy *enemy, SpaceObject *target, BehaviourOptions *options)
    : AEnemyBehaviourWithTarget::AEnemyBehaviourWithTarget(ALARM, enemy, target) {
        _options = (AlarmBehaviourOptions *)options;
    }
    
    void tick(float dt) {
        std::list<AEnemyBehaviour *>::iterator iter;
        if(ccpDistance(_enemy->getPosition(), _target->getPosition()) < _options->distance) {
            for(iter = _options->executeBehaviours.begin();
                iter != _options->executeBehaviours.end(); iter++) {
                AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
                if(!_enemy->hasBehaviour(behaviour->getName())) {
                    _enemy->addBehaviour(behaviour);
                }
            }
        } else {
            for(iter = _options->executeBehaviours.begin();
                iter != _options->executeBehaviours.end(); iter++) {
                AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
                if(_enemy->hasBehaviour(behaviour->getName())) {
                    _enemy->removeBehaviour(behaviour->getName());
                }
            }
        }
    }
};

#endif
