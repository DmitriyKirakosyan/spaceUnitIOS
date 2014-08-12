
#include "EnemyFactory.h"

#include "EBehaviourENUM.h"

#include "EnemyFollowBehaviour.h"
#include "EnemyActivateBehaviour.h"
#include "EnemyAlarmBehaviour.h"
#include "EnemyCrazyMineBehaviour.h"
#include "EnemyAlienBehaviour.h"

#include "AlarmBehaviourOptions.h"
#include "CrazyMineBehaviourOptions.h"
#include "ShootBehaviourOptions.h"

int EnemyFactory::_gameType;
Ship * EnemyFactory::_heroShip;
BehaviourOptionsData * EnemyFactory::_behaviourOptions;

void EnemyFactory::init(int gameType, Ship *heroShip, BehaviourOptionsData *behaviourOptions) {
    _gameType = gameType;
    _heroShip = heroShip;
    _behaviourOptions = behaviourOptions;
}

Enemy * EnemyFactory::createEnemy(int enemyType) {
    Enemy *result;
    result = createAsteroid();
    if (enemyType == ASTEROID) {
        result = createAsteroid();
    } else if (enemyType == MINE) {
        result = createMine();
    } else if (enemyType == CRAZY_MINE) {
        result = createCrazyMine();
    } else if (enemyType == ALIEN) {
        result = createAlien();
    } else {
        //throw new Error("unknown enemy : " + enemyType);
    }
    return result;
}

/**
 * He is same as Asteroid in Africa
 * @return
 */

Enemy * EnemyFactory::createAsteroid() {
    Enemy *result;
    
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    const char *imageFile = Assets::soImages[arc4random() % 2];
    result = new Enemy(winSize, ASTEROID, imageFile, true, TELEPORT);
    if (_gameType == RUN_GAME) {
        result->addBehaviour(new EnemyFollowBehaviour(result, _heroShip));
    }
    return result;
}

/**
 * Basic Mine. Alarm and follow hero
 * @return
 */
Enemy * EnemyFactory::createMine() {
    Enemy *result;
    
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    const char *passiveImage = Assets::minePassive;
    const char *activeImage = Assets::mineActive;
    result = new ActiveEnemy(winSize, MINE, passiveImage, activeImage, false, TELEPORT);
    AEnemyBehaviour * behavioursExecute[2];
    behavioursExecute[0] = new EnemyFollowBehaviour(result, _heroShip);
    behavioursExecute[1] = new EnemyActivateBehaviour(result);
     
    BehaviourOptions *options = new AlarmBehaviourOptions(result->getContentSize().width * 4, behavioursExecute, 2);
  
    result->addBehaviour(new EnemyAlarmBehaviour(result, _heroShip, options));
   return result;
}

/**
 * Crazy Mine. Alarm then turbo rotation and BOW with aftermath
 * @return
 */
Enemy * EnemyFactory::createCrazyMine() {
    Enemy *result;
    
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    const char *passiveImage = Assets::minePassive;
    const char *activeImage = Assets::mineActive;
    
    result = new ActiveEnemy(winSize, CRAZY_MINE, passiveImage, activeImage, false, TELEPORT);
    
    AEnemyBehaviour *behavioursExecute[2];
    BehaviourOptions *cmOptions = new CrazyMineBehaviourOptions(_behaviourOptions->blowMaker, _behaviourOptions->impactMaker);
     behavioursExecute[0] = new EnemyCrazyMineBehaviour(result, cmOptions);
     behavioursExecute[1] = new EnemyActivateBehaviour(result);
     
     BehaviourOptions *options = new AlarmBehaviourOptions(result->getContentSize().width * 4, behavioursExecute, 2);
     result->addBehaviour(new EnemyAlarmBehaviour(result, _heroShip, options));
    return result;
}

/**
 * Alien. Shooting to hero with some frequency
 * @return
 */
Enemy * EnemyFactory::createAlien() {
    Enemy *result;
    
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    const char *passiveImage = Assets::alienPassive;
    const char *activeImage = Assets::alienActive;
    
    result = new ActiveEnemy(winSize, ALIEN, passiveImage, activeImage, false, TELEPORT);
    BehaviourOptions *options = new ShootBehaviourOptions(6.0f, _heroShip, _behaviourOptions->shooter);
    result->addBehaviour(new EnemyAlienBehaviour(result, _heroShip, options));
    return result;
}