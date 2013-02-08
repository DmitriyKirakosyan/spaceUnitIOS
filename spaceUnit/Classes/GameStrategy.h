//
//  GameStrategy.h
//  spaceUnit
//
//  Created by Dmitriy on 1/3/13.
//
//

#ifndef spaceUnit_GameStrategy_h
#define spaceUnit_GameStrategy_h

#include "cocos2d.h"

class Ship;

class GameStrategy
{
public:
    GameStrategy(cocos2d::CCNode* screenContainer, Ship* ship):_ship(ship),_screenContainer(screenContainer) {
        _enemies = NULL;
        _movingTouch = NULL;
    };
    virtual void tick() = 0;
    
    virtual void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
    virtual void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
    virtual void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
    
protected:
    
    cocos2d::CCArray* _enemies;
    Ship* _ship;
    cocos2d::CCNode* _screenContainer;

    cocos2d::CCTouch* _movingTouch;
    
    virtual void explodeEnemy(cocos2d::CCSprite* enemy)
    {
        enemy->setOpacity(100);
        _enemies->removeObject(enemy);
    }

private:
    virtual void createEnemy() = 0;

};


#endif
