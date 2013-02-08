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

using namespace cocos2d;

void GameRunStrategy::tick()
{
    if (_ship->isMoving())
    {
        _ship->moveTo(_ship->getTargetPosition().x, _ship->getTargetPosition().y);
        _ship->rotateTo(_ship->getTargetPosition().x, _ship->getTargetPosition().y);
    }
    
    if (arc4random() % 30 == 23) { this->createEnemy(); }
    if (_enemies != NULL)
    {
        CCObject* item;
        CCARRAY_FOREACH(_enemies, item)
        {
            ((Enemy*) item)->moveTo(_ship->getPosition().x, _ship->getPosition().y);
        }
    }
    if (_enemies != NULL)
    {
        this->checkEnemyHits();
    }    
}

void GameRunStrategy::createEnemy()
{
    if (_enemies == NULL)
    {
        _enemies = new CCArray();
    }
    Enemy* enemy = new Enemy(CCDirector::sharedDirector()->getWinSize());
    enemy->setRandomBorderPosition();
    enemy->setRandomGeneralSpeed();
    enemy->setRandomLook();
    _enemies->addObject(enemy);
    _screenContainer->addChild(enemy);
}



void GameRunStrategy::checkEnemyHits()
{
    CCArray* enemiesForExplosion = CCArray::create();
    float distance;
    float radius1, radius2;
    CCPoint position1, position2;
    for (int i = 0; i < ((int)_enemies->count() - 1); ++i) {
        for (int j = i + 1; j < _enemies->count(); ++j) {
            radius1 = ((CCSprite*) _enemies->objectAtIndex(i))->getContentSize().height/2 *
            ((CCSprite*) _enemies->objectAtIndex(i))->getScale();
            radius2 = ((CCSprite*) _enemies->objectAtIndex(j))->getContentSize().height/2 *
            ((CCSprite*) _enemies->objectAtIndex(j))->getScale();
            position1 = ((CCSprite*) _enemies->objectAtIndex(i))->getPosition();
            position2 = ((CCSprite*) _enemies->objectAtIndex(j))->getPosition();
            
            distance = ccpDistance(position1, position2);
            if (distance < radius1 + radius2)
            {
                
                enemiesForExplosion->addObject((CCSprite*) _enemies->objectAtIndex(i));
                enemiesForExplosion->addObject((CCSprite*) _enemies->objectAtIndex(j));
            }
        }
    }
    
    CCObject* item;
    CCARRAY_FOREACH(enemiesForExplosion, item)
    {
        GameStrategy::explodeEnemy((CCSprite*) item);
    }
}


void GameRunStrategy::touchesBegan(CCSet* touches, CCEvent* event)
{
    if (_movingTouch) { _prevMovingTouch = _movingTouch; }
    _movingTouch = (CCTouch*) touches->anyObject();
    CCPoint location = _movingTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _ship->setTargetPosition(location);
    _ship->setMoving(true);
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
    _ship->setMoving(_movingTouch != NULL);
}

void GameRunStrategy::touchesMoved(CCSet* touches, CCEvent* event)
{
    CCPoint location = _movingTouch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    _ship->setTargetPosition(location);
}




