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

using namespace cocos2d;

void GameShootStrategy::tick()
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
            ((Enemy*) item)->simpleMove();
        }
    }
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