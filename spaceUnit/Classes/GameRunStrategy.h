//
//  GameRunStrategy.h
//  spaceUnit
//
//  Created by Dmitriy on 1/3/13.
//
//

#ifndef __spaceUnit__GameRunStrategy__
#define __spaceUnit__GameRunStrategy__

#include "GameStrategy.h"

class Ship;
class CCNode;

class GameRunStrategy : public GameStrategy
{
public:
    GameRunStrategy(cocos2d::CCNode* screenContainer, Ship* ship):GameStrategy(screenContainer, ship) {
        _prevMovingTouch = NULL;
    };
    
    void tick();

    void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
private:

    cocos2d::CCTouch* _prevMovingTouch;

    void createEnemy();
    void checkEnemyHits();

};

#endif /* defined(__spaceUnit__GameRunStrategy__) */
