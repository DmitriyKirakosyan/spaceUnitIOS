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
    GameShootStrategy(cocos2d::CCNode* screenContainer, Ship* ship):GameStrategy(screenContainer, ship) {};
    
    void tick();

private:
    void createEnemy();
};

#endif /* defined(__spaceUnit__GameShootStrategy__) */
