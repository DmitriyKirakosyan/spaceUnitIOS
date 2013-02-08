//
//  GameShootStrategy.h
//  spaceUnit
//
//  Created by Dmitriy on 1/9/13.
//
//

#ifndef __spaceUnit__GameShootStrategy__
#define __spaceUnit__GameShootStrategy__

#include "GameStrategy.h"

class GameShootStrategy : public GameStrategy
{
public:
    GameShootStrategy(cocos2d::CCNode* screenContainer, Ship* ship):GameStrategy(screenContainer, ship) {
        _shootingTouch = NULL;
        _bullets = NULL;
    };
    
    void tick();
    void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    

private:
    
    cocos2d::CCTouch* _shootingTouch;
    cocos2d::CCArray* _bullets;
    
    const float BULLET_SPEED = 5;

    void createEnemy();
    
    void shootBullet();
    void checkBulletsForRemove();
    void checkBulletsHit();
};

#endif /* defined(__spaceUnit__GameShootStrategy__) */
