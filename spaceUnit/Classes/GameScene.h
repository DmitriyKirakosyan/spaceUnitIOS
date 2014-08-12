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
#include "ScoreView.h"
#include "Button.h"
#include "AbilityButton.h"

class Ship;
class GameStrategy;

class GameScene : public cocos2d::CCScene
{
public:    
    static GameScene* create(const int gameType);

};

class GameLayer : public cocos2d::CCLayerColor
{
public:
    
    GameLayer(const int gameType);
    
    virtual bool init();
    void createShip();
    ScoreView *getScoreView() {return _scoreView; }
    
    virtual void update(float dt);
    
    void onCloseBtnClick(cocos2d::CCNode* node);
    void menuCloseCallback(CCNode* node);
    void drawGameOver();
    
private:    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

    
    int _gameType;
    
    Ship* _ship;
    ScoreView *_scoreView;
    GameStrategy* _gameStrategy;
    Button *_pauseButton;
    CCMenuItemImage *_quitItem;
    AbilityButton *_abilityButton;
};

#endif /* defined(__spaceUnit__GameScene__) */
