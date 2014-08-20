#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "AsteroidsBehavior.h"

USING_NS_CC;

class Main : public cocos2d::CCLayerColor
{
public:
    // Method 'init' in cocos2d-x returns bool, instead of 'id' in cocos2d-iphone (an object pointer)
    virtual bool init();

    // there's no 'id' in cpp, so we recommend to return the class instance pointer
    static cocos2d::CCScene* scene();
    
    AsteroidsBehavior *_behavior;
    
private:
    
    void initMenuItems();
    void update(float dt);
    
    // a selector callback
    void menuCloseCallback(CCObject* pSender);
    void menuSoundCallback(CCObject* pSender);
    
    void onPlayBtnRunClick(CCObject* pSender);
    void onPlayBtnShootClick(CCObject* pSender);
    void menuAboutClick(CCObject* pSender);
    
    
    cocos2d::CCArray* _staticObjects;
    cocos2d::CCArray* _movingObjects;
    
    static const int MAX_STATIC_OBJECTS;
    static const int MAX_MOVING_OBJECTS;
    static const int MIN_MOVING_OBJECTS;

    // preprocessor macro for "static create()" constructor ( node() deprecated )
    CREATE_FUNC(Main);
    
private:
    CCSize _winSize;
};

#endif // __HELLOWORLD_SCENE_H__
