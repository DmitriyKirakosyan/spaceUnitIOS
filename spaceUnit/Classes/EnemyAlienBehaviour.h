//
//  EnemyAlienBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyAlienBehaviour_h
#define spaceUnit_EnemyAlienBehaviour_h

#include "EBehaviourENUM.h"
#include "EnemyShootBehaviour.h"

class EnemyAlienBehaviour : public EnemyShootBehaviour {
public:
	EnemyAlienBehaviour(Enemy *enemy, SpaceObject *target, BehaviourOptions *options)
    : EnemyShootBehaviour(ALIEN, enemy, target, options) {
		if (enemy->getEnemyType() != ALIEN) {
			//throw new Error("enemy need to be ALIEN");
		}
	}
    

	void tick(float dt) {
        EnemyShootBehaviour::tick(dt);
		//TODO Game Balance here
		ActiveEnemy *activeEnemy = (ActiveEnemy *) _enemy;
		if (_stateTime / _options->frequency  > 0.8f) {
			if (!activeEnemy->isActiveMode()) activeEnemy->changeToActiveMode();
		} else {
			if (activeEnemy->isActiveMode()) activeEnemy->changeToPassiveMode();
		}
	}
};

#endif
