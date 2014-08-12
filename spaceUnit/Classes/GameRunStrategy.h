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

class GameRunStrategy : public GameStrategy
{
private:
    Score *_score;
    
public:
    GameRunStrategy(cocos2d::CCNode* screenContainer, Ship* ship, int gameType):GameStrategy(screenContainer, ship, gameType) {
        _prevMovingTouch = NULL;
        
        _ability = Ability::create(BLOW, ship, _impactController);
        _score = new Score(Score::getScoreTypeByGameType(RUN_GAME), 0);
        
        BehaviourOptionsData *bhOptions = new BehaviourOptionsData(NULL, _blowController, ship, _impactController);
        EnemyFactory::init(RUN_GAME, _ship, bhOptions);
        _availableEnemyTypes = EnemySetCollector::getEnemySet(RUN_GAME);
    };
    
    void tick(float dt);
    Score * getScore();
    void useAbility();

    void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
protected:
    void setEnemyParams(Enemy *enemy);

private:

    cocos2d::CCTouch* _prevMovingTouch;
    
    void createEnemy();
    void checkEnemyHits();
    void checkHeroHit();

};

#endif /* defined(__spaceUnit__GameRunStrategy__) */
