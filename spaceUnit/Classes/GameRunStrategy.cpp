//
//  GameRunStrategy.cpp
//  spaceUnit
//
//  Created by Dmitriy on 1/3/13.
//
//

#include "GameRunStrategy.h"
#include "GameStrategy.h"
#include "Enemy.h"
#include "Ship.h"
#include "RotationSpeedCollector.h"
#include "SpeedCollector.h"
#include "GameScene.h"

using namespace cocos2d;

void GameRunStrategy::tick(float dt)
{
    if(this->getGameStatus() == IN_PROCESS) {
        _score->score += dt * 1000;
        char s[20];
        _score->getPrintableScore(s);
        ((GameLayer *)_screenContainer)->getScoreView()->setScore(s);
    }
    GameStrategy::tick(dt);
    _ability->tick(dt);
    _ship->tick(dt);
    
    if (_enemies != NULL)
    {
        this->checkEnemyHits();
        this->checkHeroHit();
    }
}

void GameRunStrategy::setEnemyParams(Enemy *enemy) {
    enemy->setRandomBorderPosition();
    enemy->setRotationSpeed(RotationSpeedCollector::getEnemyRotation());
    enemy->setGeneralSpeed(SpeedCollector::getEnemySpeed(enemy->getEnemyType(), RUN_GAME));
    enemy->setTarget(_ship);
}

void GameRunStrategy::checkHeroHit() {
    Enemy *enemyToExplode = NULL;
    for (int i = 0; i < _enemies->count(); ++i) {
        SpaceObject *object = (SpaceObject *)_enemies->objectAtIndex(i);
        if (checkObjectsHit(object, _ship))
        {
            enemyToExplode = (Enemy*)_enemies->objectAtIndex(i);
            gameOver();
            break;
        }
    }
    
    if(enemyToExplode != NULL) {
       explodeEnemy(enemyToExplode);
       explodeHero();
    }
}

Score * GameRunStrategy::getScore() {
    return _score;
}


void GameRunStrategy::checkEnemyHits()
{
    CCArray* enemiesForExplosion = CCArray::create();

    for (int i = 0; i < ((int)_enemies->count() - 1); ++i) {
        for (int j = i + 1; j < _enemies->count(); ++j) {
            SpaceObject *object1 = (SpaceObject *)_enemies->objectAtIndex(i);
            SpaceObject *object2 = (SpaceObject *)_enemies->objectAtIndex(j);
            
            if (checkObjectsHit(object1, object2)) {
                enemiesForExplosion->addObject(object1);
                enemiesForExplosion->addObject(object2);
            }
        }
    }
    
    CCObject* enemy;
    CCARRAY_FOREACH(enemiesForExplosion, enemy)
    {
        explodeEnemy((Enemy *)enemy);
    }
}


void GameRunStrategy::touchesBegan(CCSet* touches, CCEvent* event)
{
    if (_movingTouch) { _prevMovingTouch = _movingTouch; }
    _movingTouch = (CCTouch*) touches->anyObject();
    CCPoint location = _movingTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _ship->setTargetPosition(location);
    _ship->moveTo(location.x, location.y);
    _ship->rotateTo(location.x, location.y);
}

void GameRunStrategy::touchesEnded(CCSet* touches, CCEvent* event)
{
    CCTouch* touch;
    for (CCSetIterator iterator = touches->begin(); iterator != touches->end(); iterator++) {
        touch = (CCTouch*) *iterator;
        if (touch == _prevMovingTouch) { _prevMovingTouch = NULL; }
        if (touch == _movingTouch)
        {
            _movingTouch = _prevMovingTouch;
        }
    }
    //_ship->setMoving(_movingTouch != NULL);
}

void GameRunStrategy::useAbility() {
    if (!_ability->isReady()) {
        //throw new Error("ability not ready for use");
    }
    _ability->activate();
}

void GameRunStrategy::touchesMoved(CCSet* touches, CCEvent* event)
{
    if(_movingTouch == NULL) return;
    CCPoint location = _movingTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _ship->setTargetPosition(location);
    _ship->moveTo(location.x, location.y);
    _ship->rotateTo(location.x, location.y);
}




