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
    GameRunStrategy(cocos2d::CCNode* screenContainer, Ship* ship):GameStrategy(screenContainer, ship) {};
    
    void tick();
    
    
private:

    void createEnemy();
    void checkEnemyHits();
    void explodeEnemy(cocos2d::CCSprite* enemy);

};

#endif /* defined(__spaceUnit__GameRunStrategy__) */
