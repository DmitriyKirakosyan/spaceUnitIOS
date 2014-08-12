//
//  EnemyActivateBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyActivateBehaviour_h
#define spaceUnit_EnemyActivateBehaviour_h

#include "AEnemyBehaviour.h"
#include "cocos2d.h"
#include "EBehaviourENUM.h"

class EnemyActivateBehaviour : public AEnemyBehaviour {
private:
    cocos2d::CCSprite *_newLook;
    
public:
    EnemyActivateBehaviour (Enemy *enemy) : AEnemyBehaviour (ACTIVATE, enemy) {
        
        if (typeid(*_enemy) != typeid(ActiveEnemy)) {
			//throw new Error("enemy need to be ActiveEnemy here!");
		}
    }
    
    void tick(float delta) {}
    
    void start() {
        AEnemyBehaviour::start();
		ActiveEnemy *enemy = (ActiveEnemy *)_enemy;
		enemy->changeToActiveMode();
	}
    
    void stop() {
        AEnemyBehaviour::stop();
		ActiveEnemy *enemy = (ActiveEnemy *)_enemy;
		enemy->changeToPassiveMode();
	}

};

#endif
