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
#include "Shooter.h"
#include "SimpleGun.h"


class GameShootStrategy : public GameStrategy
{
public:
    GameShootStrategy(cocos2d::CCNode* screenContainer, Ship* ship, int gameType):GameStrategy(screenContainer, ship, gameType) {
        _shootingTouch = NULL;

        _ability = Ability::create(MULTIGUN, ship, _impactController);
        _score = new Score(Score::getScoreTypeByGameType(SHOOT_GAME), 0);
        ship->setGun(new SimpleGun());
        _shooter = new Shooter(screenContainer);
        BehaviourOptionsData *bhOptions = new BehaviourOptionsData(_shooter, _blowController, ship, _impactController);
        EnemyFactory::init(SHOOT_GAME, ship, bhOptions);
		_availableEnemyTypes = EnemySetCollector::getEnemySet(SHOOT_GAME);
    };
    
    void tick(float dt);
    void useAbility();
    
    Ability * getAbility();
    Score * getScore();
    
    std::list<SpaceObject *> * getAllSpaceObjects();
    std::list<cocos2d::CCSprite *> * getDrawableObjects();
    
    
    void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    

private:
    
    cocos2d::CCTouch* _shootingTouch;
    IShooter *_shooter;
    Score *_score;
    
    const float BULLET_SPEED = 5;

    void createEnemy();
    
    void shootBullet();
    void checkBulletsForRemove();
    void checkBulletsHit();
    void checkHeroHit();
    
protected:
    void setEnemyParams(Enemy *enemy);
};

#endif /* defined(__spaceUnit__GameShootStrategy__) */
