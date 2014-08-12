//
//  GameShootStrategy.cpp
//  spaceUnit
//
//  Created by Dmitriy on 1/9/13.
//
//

#include "GameShootStrategy.h"
#include "Ship.h"
#include "Enemy.h"
#include "Bullet.h"
#include "SpeedCollector.h"
#include "RotationSpeedCollector.h"
#include "GameScene.h"

using namespace cocos2d;

void GameShootStrategy::tick(float dt)
{
    GameStrategy::tick(dt);
    _ability->tick(dt);
    _ship->tick(dt);
    
    if (!_ship->isDead() && _shootingTouch != NULL)
    {
        this->shootBullet();
    }
    
    _shooter->tick(dt);
    
    if(((Shooter *)_shooter)->getBullets() != NULL) {
        checkBulletsForRemove();
        checkBulletsHit();
    }
    checkHeroHit();
}

Ability *GameShootStrategy::getAbility()
{
    return _ability;
}

void GameShootStrategy::useAbility() {
    if (!_ability->isReady()) {
       // throw new Error("ability not ready to activate");
    }
    _ability->activate();
}


std::list<SpaceObject *> * GameShootStrategy::getAllSpaceObjects() {
    std::list<SpaceObject *> *result = GameStrategy::getAllSpaceObjects();
    std::list<Bullet *> *bullets = ((Shooter *)_shooter)->getBullets();
    if (bullets != NULL) {
        std::list<Bullet *>::iterator iter;
        for(iter = bullets->begin(); iter != bullets->end(); iter++) {
            SpaceObject *object = (SpaceObject *)(*iter);
            result->push_back(object);
        }
    }
    return result;
}

std::list<cocos2d::CCSprite *> * GameShootStrategy::getDrawableObjects() {
    std::list<cocos2d::CCSprite *> * result = GameStrategy::getDrawableObjects();
    /*if (_shooter.getBullets() != null) {
        for (Bullet bullet : _shooter.getBullets()) {
            result.add(bullet.getImage());
        }
    }*/
    return result;
}

void GameShootStrategy::setEnemyParams(Enemy *enemy)
{
    cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
    
    enemy->setRandomBorderPosition();
    enemy->setGeneralSpeed(SpeedCollector::getEnemySpeed(enemy->getEnemyType(), RUN_GAME));
    enemy->setRotationSpeed(RotationSpeedCollector::getEnemyRotation());
    enemy->moveTo(arc4random() % (int)winSize.width, arc4random() % (int)winSize.height);
    enemy->setTarget(_ship);
}

void GameShootStrategy::shootBullet()
{
    if (_shootingTouch == NULL) { CCLOGERROR("shooting touch not exist!! [GameShootStrategy::shootBullet]"); }
    
    CCPoint targetPoint = _shootingTouch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL(targetPoint);
    
    _ship->shoot(_shooter, targetPoint.x, targetPoint.y);
}

void GameShootStrategy::checkBulletsForRemove()
{
    CCPoint position;
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    std::list<Bullet *> *_bullets = ((Shooter *)_shooter)->getBullets();
    std::list<Bullet *>::iterator iter;
    for(iter = _bullets->begin(); iter != _bullets->end(); iter++)
    {
        Bullet *bullet = (Bullet *)(*iter);
        position = bullet->getPosition();
        if ((position.x < 0) ||
            (position.x > screenSize.width) ||
            (position.y < 0) ||
            (position.y > screenSize.height))
        {
            CCLog("remove bullet!");
            bullet->setDead();
            _screenContainer->removeChild(bullet, false);
        }
    }
}

void GameShootStrategy::checkBulletsHit()
{
    if(_enemies == NULL) return;
    
    CCArray* enemiesForExplosion = CCArray::create();
    CCArray* bulletsForRemove = CCArray::create();
    
    std::list<Bullet *> *_bullets = ((Shooter *)_shooter)->getBullets();
    std::list<Bullet *>::iterator iter;
    for(iter = _bullets->begin(); iter != _bullets->end(); iter++)
    {
        Bullet *bullet = (Bullet *)(*iter);
        for (int i = 0; i < _enemies->count(); ++i) {
            if(bullet->getOwner() == _enemies->objectAtIndex(i)) continue;
            
            if (checkObjectsHit(bullet, (SpaceObject *)_enemies->objectAtIndex(i)))
            {
                enemiesForExplosion->addObject(_enemies->objectAtIndex(i));
                bulletsForRemove->addObject(bullet);
                if(bullet->getOwner() == _ship && getGameStatus() != GAME_OVER) {
                    _score->score++;
                    char s[20];
                    _score->getPrintableScore(s);
                    ((GameLayer *)_screenContainer)->getScoreView()->setScore(s);
                }
            }
        }
    }
    
    CCObject* item;
    CCARRAY_FOREACH(enemiesForExplosion, item)
    {
        explodeEnemy((Enemy *)item);
    }
    enemiesForExplosion->removeAllObjects();
    
    CCObject *bullet = NULL;
    CCARRAY_FOREACH(bulletsForRemove, bullet)
    {
        _screenContainer->removeChild((CCSprite*) bullet, false);
        _bullets->remove((Bullet *)bullet);
    }
    bulletsForRemove->removeAllObjects();
}

Score * GameShootStrategy::getScore() {
    return _score;
}

void GameShootStrategy::checkHeroHit() {
    Enemy *enemyToExplode = NULL;
    for (int i = 0; i < _enemies->count(); i++) {
        if (checkObjectsHit(_ship, (Enemy *)_enemies->objectAtIndex(i))) {
            enemyToExplode = (Enemy *)_enemies->objectAtIndex(i);
            gameOver();
            break;
        }
    }
    if (enemyToExplode != NULL) {
        explodeEnemy(enemyToExplode);
        explodeHero();
    } else {
        if (((Shooter *)_shooter)->getBullets() != NULL) {
            std::list<Bullet *> * bullets = ((Shooter *)_shooter)->getBullets();
            std::list<Bullet *>::iterator iter;
            for (iter = bullets->begin(); iter != bullets->end(); iter++) {
                Bullet *bullet = (Bullet *)(*iter);
                if (bullet->getOwner() != _ship && checkObjectsHit(_ship, bullet)) {
                    explodeHero();
                    bullet->setDead();
                    gameOver();
                }
            }
        }
    }
}

void GameShootStrategy::touchesBegan(CCSet* touches, CCEvent* event)
{
    CCTouch* touch = (CCTouch*) touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if (_movingTouch)
    {
        _shootingTouch = touch;
        _ship->setTargetForShooting(location);
        //_ship->setShooting(true);
    }
    else
    {
        _movingTouch = touch;
        _ship->setTargetPosition(location);
        _ship->moveTo(location.x, location.y);
        if(_ship->getSkin()->rotatable())
            _ship->rotateTo(location.x, location.y);
    }
}

void GameShootStrategy::touchesEnded(CCSet* touches, CCEvent* event)
{
    CCTouch* touch;
    for (CCSetIterator iterator = touches->begin(); iterator != touches->end(); iterator++) {
        touch = (CCTouch*) *iterator;

        if (touch == _movingTouch)
        {
            _movingTouch = _shootingTouch;
        }
        _shootingTouch = NULL;
    }
    //_ship->setMovin(_movingTouch != NULL);
}

void GameShootStrategy::touchesMoved(CCSet* touches, CCEvent* event)
{
    if (_movingTouch != NULL)
    {
        CCPoint location = _movingTouch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        _ship->setTargetPosition(location);
        _ship->moveTo(location.x, location.y);
        if(_ship->getSkin()->rotatable())
            _ship->rotateTo(location.x, location.y);
    }
}
