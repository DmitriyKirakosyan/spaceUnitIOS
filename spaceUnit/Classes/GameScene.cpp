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
#include "GameStatus.h"
#include "GameStrategyFactory.h"
#include "cocos2d.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

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
        CCSize winSize = CCDirector::sharedDirector()->getWinSize();
        
        CCSprite *backSprite = CCSprite::create("firstscreen_back.png");
        backSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
        backSprite->setScale(1.3f);
        this->addChild(backSprite);

        this->createShip();
        _gameStrategy = GameStrategyFactory::createStrategy(this, _ship, _gameType);
        
        _abilityButton = new AbilityButton(_gameStrategy->_ability);
        _abilityButton->setPosition(ccp(winSize.width - 50, 50));
        this->addChild(_abilityButton);
        
        _scoreView = new ScoreView();
        _scoreView->setPosition(ccp(winSize.width / 2, winSize.height - 5 - _scoreView->getContentSize().height / 2));
        this->addChild(_scoreView, 1);
        
        _pauseButton = new Button(Assets::pauseUp, Assets::pauseDown);
        _pauseButton->setAnchorPoint(ccp(1, 1));
        _pauseButton->setPosition(ccp(winSize.width - 15, winSize.height - 15));
        this->addChild(_pauseButton);
        
        _quitItem = CCMenuItemImage::create(
                                            "quitBtn_Up.png",
                                            "quitBtn_Down.png",
                                            this,
                                            menu_selector(GameLayer::onCloseBtnClick) );
        _quitItem->setPosition( ccp(winSize.width / 2, winSize.height / 2));
        _quitItem->setOpacity(0);
        CCMenu* pMenu = CCMenu::create(_quitItem, NULL);
        pMenu->setPosition( CCPointZero );
        this->addChild(pMenu, 1);

        
        this->setTouchEnabled(true);
        
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("gameplay.mp3", true);
        
        this->schedule(schedule_selector(GameLayer::update));
        return true;
    }
    return false;
}

void GameLayer::createShip()
{
    if (_ship != NULL) { CCLOGERROR("ship already exists!"); }
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _ship = new Ship();
    _ship->setGeneralSpeed(SpeedCollector::getHeroSpeed(_gameType));
    _ship->setPosition(ccp(winSize.width/2, winSize.height/2));
    this->addChild(_ship);
    
}

void GameLayer::update(float dt)
{
    if(!_gameStrategy->isPaused()) {
        _gameStrategy->tick(dt);
    }
    
    if(_gameStrategy->getGameStatus() == GAME_OVER) {
        drawGameOver();
    }
    if(_gameStrategy->isPaused()) _quitItem->setOpacity(255);
    else _quitItem->setOpacity(0);
    
    if (_abilityButton != NULL) {
        if (!_gameStrategy->isPaused()) {
            _abilityButton->tick(dt);
        }
    }
    
}


void GameLayer::drawGameOver() {
    
    CCNode *node = this->getChildByTag(5);
    if(node != NULL) return;
    
    Score *score = _gameStrategy->getScore();
    char scoreStr[20], s[50];
    score->getPrintableScore(scoreStr);
    if(score->type == Score::SECONDS) {
        sprintf(s, "GAME OVER\nseconds : %s", scoreStr);
    } else {
        sprintf(s, "GAME OVER\nkills : %s", scoreStr);
    }
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    cocos2d::CCLabelTTF *label = cocos2d::CCLabelTTF::create("Score:", "Calibri", 40, CCSizeMake(450, 300), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
    label->setColor(cocos2d::ccc3(255, 0, 0));
    label->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    label->setString(s);
    this->addChild(label, 5, 5);
}

void GameLayer::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    if(_gameStrategy->getGameStatus() == GAME_OVER) {
        CCScene* mainScene = Main::scene();
        CCDirector::sharedDirector()->replaceScene(mainScene);
        return;
    }
    
    CCTouch *touch = (CCTouch*) touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if(_pauseButton->getPosition().x >= location.x &&
       _pauseButton->getPosition().x - _pauseButton->getContentSize().width <= location.x &&
       _pauseButton->getPosition().y >= location.y &&
       _pauseButton->getPosition().y - _pauseButton->getContentSize().height <= location.y) {
        if(_gameStrategy->getGameStatus() == PAUSE) {
            _gameStrategy->resumeGame();
            _pauseButton->setNormalMode();
        } else if(_gameStrategy->getGameStatus() == IN_PROCESS) {
            _gameStrategy->pauseGame();
            _pauseButton->setClickedMode();
        }
        return;
    }
    
    if(_gameStrategy->isPaused()) return;
    if(_abilityButton->getPosition().x + _abilityButton->_panelSprite->getContentSize().width / 2 >= location.x &&
       _abilityButton->getPosition().x - _abilityButton->_panelSprite->getContentSize().width / 2 <= location.x &&
       _abilityButton->getPosition().y + _abilityButton->_panelSprite->getContentSize().height / 2 >= location.y &&
       _abilityButton->getPosition().y - _abilityButton->_panelSprite->getContentSize().height / 2 <= location.y) {
        if(_abilityButton->isReady()) {
            _gameStrategy->useAbility();
            return;
        }
    }
        
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
    if(!_gameStrategy->isPaused()) return;
    CCScene* mainScene = Main::scene();
    CCDirector::sharedDirector()->replaceScene(mainScene);
}

