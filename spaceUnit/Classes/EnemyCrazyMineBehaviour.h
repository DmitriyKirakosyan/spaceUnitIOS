//
//  EnemyCrazyMineBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyCrazyMineBehaviour_h
#define spaceUnit_EnemyCrazyMineBehaviour_h

#include "AEnemyBehaviour.h"
#include "RotationSpeedCollector.h"
#include "CrazyMineBehaviourOptions.h"

class EnemyCrazyMineBehaviour : public AEnemyBehaviour {
private:
    const float BOOM_TIME = 3;
    float _enemyRotation;
	float _timeState;
	IBlowMaker *_blowMaker;
	IImpactMaker *_impactMaker;
    
public:
    EnemyCrazyMineBehaviour(Enemy *enemy, BehaviourOptions *options)
    : AEnemyBehaviour(CRAZYB_MINE, enemy){
		
		_enemyRotation = enemy->getRotationSpeed();
        
		if (typeid(*options) != typeid(CrazyMineBehaviourOptions)) {
			//throw new Error("invalid options");
		}
		CrazyMineBehaviourOptions *cmOptions = (CrazyMineBehaviourOptions *) options;
		_blowMaker = cmOptions->blowMaker;
		_impactMaker = cmOptions->impactMaker;
	}
    
	
	void start() {
		_enemy->setRotationSpeed(RotationSpeedCollector::getRotationTurboSpeed());
		_enemy->stopMoving();
		_timeState = 0;
	}
    
	
	void stop() {
		_enemy->resumeMoving();
		_enemy->setRotationSpeed(_enemyRotation);
	}
    
	
	void tick(float delta) {
		_timeState += delta;
		if (_timeState > BOOM_TIME) {
			_enemy->explode(_blowMaker);
			_impactMaker->createBlow(_enemy->getPosition().x, _enemy->getPosition().y);
			_enemy->setDead();
			CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bam6.mp3");
			//AppVibrator.getInstance().vibrate(300);
		}
	}
};


#endif
