//
//  GameScene.h
//  spaceUnit
//
//  Created by Dmitriy on 12/31/12.
//
//

#ifndef __spaceUnit__GameScene__
#define __spaceUnit__GameScene__

#include "cocos2d.h"

class Ship;
class GameStrategy;

class GameScene : public cocos2d::CCScene
{
public:
    static const int SHOOT_GAME;
    static const int RUN_GAME;
    
    static const int MAX_TIME_ENEMY_RESPAWN;
    
    static GameScene* create(const int gameType);

};

class GameLayer : public cocos2d::CCLayerColor
{
public:
    
    GameLayer(const int gameType);
    
    virtual bool init();
    void createShip();
    
    virtual void update(float dt);
    
    void onCloseBtnClick(cocos2d::CCNode* node);
    
private:    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    
    int _gameType;
    
    Ship* _ship;
    
    GameStrategy* _gameStrategy;
    
};

#endif /* defined(__spaceUnit__GameScene__) */
