//
//  EnemyShootBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyShootBehaviour_h
#define spaceUnit_EnemyShootBehaviour_h

#include "AEnemyBehaviourWithTarget.h"
#include "ShootBehaviourOptions.h"
#include "Shooter.h"

class EnemyShootBehaviour : public AEnemyBehaviourWithTarget {

protected:
    ShootBehaviourOptions *_options;
    
	float _stateTime;
    
public:
    EnemyShootBehaviour(int name, Enemy *enemy, SpaceObject *target, BehaviourOptions *options)
    : AEnemyBehaviourWithTarget(name, enemy, target) {
        
		if (typeid(*options) != typeid(ShootBehaviourOptions)) {
			//throw new Error("options need to be ShootBehaviourOptions here");
		}
        
		_options = (ShootBehaviourOptions *) options;
	}
    
	EnemyShootBehaviour(Enemy *enemy, SpaceObject *target, BehaviourOptions *options)
    : AEnemyBehaviourWithTarget(SHOOT, enemy, target) {
        if (typeid(*options) != typeid(ShootBehaviourOptions)) {
			//throw new Error("options need to be ShootBehaviourOptions here");
		}
        
		_options = (ShootBehaviourOptions *) options;
	}
    
	
	void start() {
        AEnemyBehaviourWithTarget::start();
		_stateTime = 0;
	}
    
	
	void stop() {
        AEnemyBehaviourWithTarget::stop();
		_stateTime = 0;
	}
    
	
	void tick(float delta) {
		_stateTime += delta;
		if (_stateTime >= _options->frequency) {
            _options->targetToShoot->getPosition();
			_options->shooter->shoot(_enemy, _options->targetToShoot->getPosition(), Shooter::ENEMY_BULLET);
			_stateTime = (int)_stateTime % (int)_options->frequency;
		}
	}
};


#endif
