#ifndef __spaceUnit__CreditScreen__
#define __spaceUnit__CreditScreen__

#include "cocos2d.h"
#include "AsteroidsBehavior.h"
#include "Button.h"
#include "MainScene.h"

using namespace cocos2d;

class CreditScreen : public cocos2d::CCLayerColor
{
public:
    virtual bool init();
    static cocos2d::CCScene* scene();
    
    
private:
    
    void initMenuItems();
    void update(float dt);
    void updatePositions(float dt);
    bool checkOutOfBounds();
    bool checkOut();
    
    void onPlayBtnRunClick(CCObject* pSender);
    void menuBackCallback(CCObject* pSender);
    void menuContinueCallClick(CCObject* pSender);
    
    void ccTouchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void ccTouchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
private:
    CCSprite *_title;
    CCSprite *_credits;
    CCMenuItem *_backBtn;
    CCMenuItem *_continueBtn;
    
    float _startX;
    float _startY;
    float START_POS_Y;
    float FINAL_POS_Y;
    float _speed;
    float _posY;
    int DEF_SPEED = 50;
    
    CCTouch *prevTouch;
    float prevY;
    bool _isPan = false;
    
    CCPoint _posTitle;
    
    AsteroidsBehavior *_asterBehavior;
    AsteroidsBehavior *_meteorBehavior;
    
    
    CREATE_FUNC(CreditScreen);
};

#endif /* defined(__spaceUnit__CredistScreen__) */
