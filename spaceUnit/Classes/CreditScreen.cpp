//
//  CreditScreen.cpp
//  spaceUnit
//
//  Created by PC on 8/13/14.
//
//

#include "CreditScreen.h"
#include "AsteroidsBehavior.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* CreditScreen::scene()
{
    CCScene *scene = CCScene::create();
    
    CreditScreen *layer = CreditScreen::create();
    scene->addChild(layer);
    return scene;
}

// on "init" you need to initialize your instance
bool CreditScreen::init()
{
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }
    
    initMenuItems();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    _speed = 0;
    _posTitle = ccp(0, winSize.height / 2);
    
    this->setTouchEnabled(true);
    
    this->schedule(schedule_selector(CreditScreen::update));
    
    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainmenu.mp3", true);
    return true;
}

void CreditScreen::initMenuItems() {
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _title = CCSprite::create("spaceunit.png");
    _title->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    this->addChild(_title, 2);
    
    _startX = winSize.width / 2;
    _startY = winSize.height / 2;
    
    _credits = CCSprite::create("credits.png");
    _credits->setAnchorPoint(ccp(0.5f, 1.0f));
    _credits->setPosition(ccp(winSize.width / 2, 0));
    this->addChild(_credits, 2);
    
    _asterBehavior = new AsteroidsBehavior(10);
    std::list<MovingSpaceObject *> *spaceObjcets = _asterBehavior->getSpaceObjects();
    std::list<MovingSpaceObject *>::iterator iter;
    for(iter = spaceObjcets->begin(); iter != spaceObjcets->end(); iter++) {
        MovingSpaceObject *spaceObject = (MovingSpaceObject *)(*iter);
        int zOrder = arc4random() % 2;
        if(zOrder == 0)
            this->addChild(spaceObject, 1);
        else
            this->addChild(spaceObject, 3);
    }
    
    _backBtn = CCMenuItemImage::create("backBtn_Up.png", "backBtn_Down.png", this, menu_selector(CreditScreen::menuBackCallback));
    _backBtn->setAnchorPoint(ccp(0, 0));
    _backBtn->setPosition(ccp(5, 5));
    
    //_continueBtn = CCMenuItemImage::create("continueBtn_Up.png", "continueBtn_Down.png", this, menu_selector(CreditScreen::menuContinueCallClick));
    //_continueBtn->setPosition( ccp(winSize.width / 2 , _credits->getPosition().y - _credits->getContentSize().height - 100));
    
    CCMenu* pMenu = CCMenu::create(_backBtn/*, _continueBtn*/, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 4);
    //_meteorBehavior = new AsteroidsBehavior(10);
    
    START_POS_Y = winSize.height / 2;
    FINAL_POS_Y = _credits->getContentSize().height + 200;
}

void CreditScreen::update(float dt)
{
    _asterBehavior->tick(dt);
    _title->setPosition(ccp(_title->getPosition().x, _posTitle.y));
    updatePositions(dt);
}

void CreditScreen::updatePositions(float dt) {
    if (_isPan) { return; }
    
    if (_speed > DEF_SPEED) {
        _speed -= DEF_SPEED;
    } else if (_speed < DEF_SPEED) {
        _speed += DEF_SPEED;
    } else if (_speed > DEF_SPEED+0.2f || _speed < DEF_SPEED - 0.2f) {
        _speed = DEF_SPEED;
    }
    
    if (checkOutOfBounds()) { return; }
    
    _posTitle.y += _speed * dt;
    _posY += _speed * dt;
    _credits->setPosition(ccp(_credits->getPosition().x, _posY));
    //_continueBtn->setPosition( ccp(_continueBtn->getPosition().x , _credits->getPosition().y - _credits->getContentSize().height - 100));
}

bool CreditScreen::checkOutOfBounds() {
    if (_credits->getPosition().y > FINAL_POS_Y && _speed > 0) {
        _speed = 0;
        _isPan = false;
        return true;
    }
    if (_title->getPosition().y < START_POS_Y  && _speed < 0) {
        _speed = 0;
        _isPan = false;
        return true;
    }
    return false;
}

bool CreditScreen::checkOut() {
    if (_credits->getPosition().y > FINAL_POS_Y) {
        //_credits.setY(FINAL_POS_Y);
        _speed = 0;
        _isPan = false;
        return true;
    }
    if (_credits->getPosition().y < START_POS_Y) {
        //_credits.setY(START_POS_Y);
        _speed = 0;
        _isPan = false;
        return true;
    }
    return false;
}

void CreditScreen::menuBackCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->replaceScene(Main::scene());
}


void CreditScreen::menuContinueCallClick(CCObject* pSender)
{
    
}

void CreditScreen::onPlayBtnRunClick(CCObject* pSender)
{
    /* SimpleAudioEngine::sharedEngine()->playEffect("click.mp3", false);
     GameScene* gameScene = GameScene::create(RUN_GAME);
     CCDirector::sharedDirector()->replaceScene(gameScene);*/
}

void CreditScreen::ccTouchesBegan(CCSet* touches, CCEvent* event)
{
    CCTouch *touch = (CCTouch*) touches->anyObject();
    
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    std::list<MovingSpaceObject *> *spaceObjcets = _asterBehavior->getSpaceObjects();
    std::list<MovingSpaceObject *>::iterator iter;
    bool flag = false;
    for(iter = spaceObjcets->begin(); iter != spaceObjcets->end(); iter++) {
        MovingSpaceObject *spaceObject = (MovingSpaceObject *)(*iter);
        if(spaceObject->getPosition().x + spaceObject->getContentSize().width / 2 >= location.x &&
           spaceObject->getPosition().x - spaceObject->getContentSize().width / 2 <= location.x &&
           spaceObject->getPosition().y + spaceObject->getContentSize().height / 2 >= location.y &&
           spaceObject->getPosition().y - spaceObject->getContentSize().height / 2 <= location.y) {
            _asterBehavior->setBlow(spaceObject);
            flag = true;
        }
    }

    if(prevTouch == NULL && !flag) {
        prevTouch = touch;
        CCPoint prev_location = prevTouch->getLocationInView();
        prev_location = CCDirector::sharedDirector()->convertToGL(prev_location);
        prevY = prev_location.y;
    }
}

void CreditScreen::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
    
   /* CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if(prevTouch == NULL) return;
    float deltaY = location.y - prevY;
    deltaY = deltaY / 50;
    if(deltaY == 0) return;
    
    if(_credits->getPosition().y + deltaY >= FINAL_POS_Y) return;
    if(_credits->getPosition().y + deltaY <= 0) return;
    
    _title->setPosition(ccp(_title->getPosition().x, _title->getPosition().y + deltaY));
    _credits->setPosition(ccp(_credits->getPosition().x, _credits->getPosition().y + deltaY));
    //_continueBtn->setPosition(ccp(_continueBtn->getPosition().x, _continueBtn->getPosition().y + deltaY));
    
    _posTitle.y += deltaY;
    _posY += deltaY;
    // _isPan = false;
    prevTouch = NULL;*/
}

void CreditScreen::ccTouchesMoved(CCSet* touches, CCEvent* event)
{
    CCTouch *touch = (CCTouch *)touches->anyObject();
    CCPoint location = touch->getLocationInView();
    location = CCDirector::sharedDirector()->convertToGL(location);
    
    if(prevTouch == NULL) return;
    float deltaY = location.y - prevY;
    deltaY = deltaY;
    if(deltaY == 0) return;
    if(deltaY < 0) _speed += MAX(-1700, deltaY * 500);
    else _speed += MIN(1700, deltaY * 500);
    
    prevTouch = NULL;
    _isPan = false;
    /*
    if(_credits->getPosition().y + deltaY >= FINAL_POS_Y) return;
    if(_credits->getPosition().y + deltaY <= 0) return;
    
    _title->setPosition(ccp(_title->getPosition().x, _title->getPosition().y + deltaY));
    _credits->setPosition(ccp(_credits->getPosition().x, _credits->getPosition().y + deltaY));
    //_continueBtn->setPosition(ccp(_continueBtn->getPosition().x, _continueBtn->getPosition().y + deltaY));
    
    _posTitle.y += deltaY;
    _posY += deltaY;
    //_isPan = true;
    */
}