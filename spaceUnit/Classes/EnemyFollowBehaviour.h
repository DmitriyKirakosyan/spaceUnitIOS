//
//  EnemyFollowBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyFollowBehaviour_h
#define spaceUnit_EnemyFollowBehaviour_h

#include "AEnemyBehaviourWithTarget.h"

class EnemyFollowBehaviour : public AEnemyBehaviourWithTarget {
public:
    EnemyFollowBehaviour(Enemy *enemy, SpaceObject *target) : AEnemyBehaviourWithTarget(FOLLOW, enemy, target){
    }
    
	
	void tick(float delta) {
		_enemy->moveTo(_target->getPosition().x, _target->getPosition().y);
	}
};



#endif
