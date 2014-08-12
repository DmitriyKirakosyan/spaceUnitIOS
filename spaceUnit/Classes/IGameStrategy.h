//
//  IGameStrategy.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_IGameStrategy_h
#define spaceUnit_IGameStrategy_h

#include "Score.h"
#include "Ability.h"
#include <list>

class IGameStrategy {
public:
	virtual void startGame();
	virtual void stopGame();
	virtual void pauseGame();
	virtual void resumeGame();
	virtual bool isPaused();
    
	virtual Ability getAbility();
	virtual void useAbility();
    
	virtual Score getScore();
    
	virtual void tick(float dt);
	virtual int getGameStatus();
    virtual std::list<cocos2d::CCSprite *> getDrawableObjects();
};

#endif
