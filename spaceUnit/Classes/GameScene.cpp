//
//  GameScene.cpp
//  spaceUnit
//
//  Created by Dmitriy on 12/31/12.
//
//

#include "GameScene.h"
#include "MainScene.h"
#include "Enemy.h"
#include "Ship.h"
#include "GameRunStrategy.h"
#include "GameShootStrategy.h"

using namespace cocos2d;

const int GameScene::SHOOT_GAME = 0;
const int GameScene::RUN_GAME = 1;
const int GameScene::MAX_TIME_ENEMY_RESPAWN = 3;

GameScene* GameScene::create(const int gameType)
{
    GameScene* result = new GameScene();
    if (result->init())
    {
        GameLayer* layer = new GameLayer(gameType);
        layer->autorelease();
        result->addChild(layer);
        return result;
    }
    delete result;
    return NULL;
}

GameLayer::GameLayer(const int gameType):_gameType(gameType)
{
    this->init();
}

bool GameLayer::init()
{
    if (CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
    {
        
        this->createShip();
        if (_gameType == GameScene::RUN_GAME)
        {
            _gameStrategy = new GameRunStrategy(this, _ship);
        }
        else
        {
            _gameStrategy = new GameShootStrategy(this, _ship);
        }
        
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                                              "CloseNormal.png",
                                                              "CloseSelected.png",
                                                              this,
                                                              menu_selector(GameLayer::onCloseBtnClick) );
        pCloseItem->setPosition( ccp(20, winSize.height - 20) );
        CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu);
        
        this->setTouchEnabled(true);
        
        this->schedule(schedule_selector(GameLayer::update));
        return true;
    }
    return false;
}

void GameLayer::createShip()
{
    if (_ship != NULL) { CCLOGERROR("ship already exists!"); }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _ship = new Ship(winSize, 10);
    _ship->setGeneralSpeed(2);
    _ship->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(_ship);
}

void GameLayer::update(float dt)
{
    _gameStrategy->tick();
}

void GameLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    _gameStrategy->touchesBegan(touches, event);
}

void GameLayer::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    _gameStrategy->touchesEnded(touches, event);
}

void GameLayer::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    _gameStrategy->touchesMoved(touches, event);
}

void GameLayer::onCloseBtnClick(CCNode* node)
{
    CCScene* mainScene = Main::scene();
    CCDirector::sharedDirector()->replaceScene(mainScene);
}