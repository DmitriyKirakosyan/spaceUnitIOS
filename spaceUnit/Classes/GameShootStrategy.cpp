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

using namespace cocos2d;

void GameShootStrategy::tick()
{
    _ship->tick();
    
    if (_ship->isReadyForShoot())
    {
        this->shootBullet();
    }
    
    if (_bullets != NULL)
    {
        CCObject* bullet;
        CCARRAY_FOREACH(_bullets, bullet)
        {
            ((Bullet*) bullet)->move();
        }
    }
    this->checkBulletsForRemove();
    this->checkBulletsHit();
    
    if (arc4random() % 30 == 23) { this->createEnemy(); }
    if (_enemies != NULL)
    {
        CCObject* item;
        CCARRAY_FOREACH(_enemies, item)
        {
            ((Enemy*) item)->simpleMove();
        }
    }
}

void GameShootStrategy::shootBullet()
{
    if (_bullets == NULL)
    {
        _bullets = new CCArray();
    }
    
    if (_shootingTouch == NULL) { CCLOGERROR("shooting touch not exist!! [GameShootStrategy::shootBullet]"); }
    
    CCPoint targetPoint = _shootingTouch->getLocationInView();
    targetPoint = CCDirector::sharedDirector()->convertToGL(targetPoint);
    
    CCPoint bulletPosition = _ship->getPosition();
    
    float dx = targetPoint.x - bulletPosition.x;
    float dy = targetPoint.y - bulletPosition.y;
    float h = sqrt(dx * dx + dy * dy);
    float vx = 0;
    float vy = 0;
    if (h != 0){
        vx = dx / h;
        vy = dy / h;
    }
    
    CCSprite* bullet = new Bullet(BULLET_SPEED, vx, vy);
    bullet->initWithFile("SimpleBulletView.png");
    bullet->setPosition(bulletPosition);
    bullet->autorelease();
    _bullets->addObject(bullet);
    _screenContainer->addChild(bullet);
}

void GameShootStrategy::checkBulletsForRemove()
{
    CCObject* item;
    CCPoint position;
    CCSize screenSize = CCDirector::sharedDirector()->getWinSize();
    CCARRAY_FOREACH(_bullets, item)
    {
        position = ((CCSprite*) item)->getPosition();
        if ((position.x < 0) ||
            (position.x > screenSize.width) ||
            (position.y < 0) ||
            (position.y > screenSize.height))
        {
            CCLog("remove bullet!");
            _bullets->removeObject(item);
            _screenContainer->removeChild((CCSprite*) item, false);
            break;
        }
    }
}

void GameShootStrategy::checkBulletsHit()
{
    CCArray* enemiesForExplosion = CCArray::create();
    CCArray* bulletsForRemove = CCArray::create();
    float distance;
    float enemyRadius;
    CCPoint enemyPosition;
    
    CCObject* bulletItem;
    CCARRAY_FOREACH(_bullets, bulletItem)
    {
        for (int i = 0; i < _enemies->count(); ++i) {
                enemyRadius = ((CCSprite*) _enemies->objectAtIndex(i))->getContentSize().height/2 *
                ((CCSprite*) _enemies->objectAtIndex(i))->getScale();
                enemyPosition = ((CCSprite*) _enemies->objectAtIndex(i))->getPosition();
                
                distance = ccpDistance(enemyPosition, ((CCSprite*) bulletItem)->getPosition());
                if (distance < enemyRadius)
                {
                    enemiesForExplosion->addObject(_enemies->objectAtIndex(i));
                    bulletsForRemove->addObject(bulletItem);
                }
        }
    }
    
    CCObject* item;
    CCARRAY_FOREACH(enemiesForExplosion, item)
    {
        GameStrategy::explodeEnemy((CCSprite*) item);
    }
    enemiesForExplosion->removeAllObjects();
    
    bulletItem = NULL;
    CCARRAY_FOREACH(bulletsForRemove, bulletItem)
    {
        _screenContainer->removeChild((CCSprite*) bulletItem, false);
        _bullets->removeObject(bulletItem);
    }
    bulletsForRemove->removeAllObjects();
}



void GameShootStrategy::createEnemy()
{
    if (_enemies == NULL)
    {
        _enemies = new CCArray();
    }
    Enemy* enemy = new Enemy(CCDirector::sharedDirector()->getWinSize(), true);
    enemy->setRandomBorderPosition();
    enemy->setRandomBehaviour();
    enemy->setRandomLook();
    _enemies->addObject(enemy);
    _screenContainer->addChild(enemy);
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
        _ship->setShooting(true);
    }
    else
    {
        _movingTouch = touch;
        _ship->setTargetPosition(location);
        _ship->setMoving(true);
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
        _ship->setShooting(false);
        _shootingTouch = NULL;
    }
    _ship->setMoving(_movingTouch != NULL);
}

void GameShootStrategy::touchesMoved(CCSet* touches, CCEvent* event)
{
    if (_movingTouch != NULL)
    {
        CCPoint location = _movingTouch->getLocationInView();
        location = CCDirector::sharedDirector()->convertToGL(location);
        _ship->setTargetPosition(location);
    }
}
