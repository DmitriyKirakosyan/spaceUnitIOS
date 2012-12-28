#include "MainScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* Main::scene()
{
    // 'scene' is an autorelease object
    CCScene *scene = CCScene::create();
    
    // 'layer' is an autorelease object
    Main *layer = Main::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool Main::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)) )
    {
        return false;
    }


    this->createBackObjecs();

    CCSize winSize = CCDirector::sharedDirector()->getWinSize();

    CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
                                        "CloseNormal.png",
                                        "CloseSelected.png",
                                        this,
                                        menu_selector(Main::menuCloseCallback) );
    pCloseItem->setPosition( ccp(winSize.width - 20, 20) );

    CCMenuItemImage *playBtnRun = CCMenuItemImage::create(
                                                          "PlayBtnRun_1.png",
                                                          "PlayBtnRun_2.png",
                                                          this,
                                                          menu_selector(Main::onPlayBtnRunClick) );
    playBtnRun->setPosition( ccp(winSize.width/2 - playBtnRun->getContentSize().width/2 - 20, winSize.height/2) );

    CCMenuItemImage *playBtnShoot = CCMenuItemImage::create(
                                                          "PlayBtnShoot_1.png",
                                                          "PlayBtnShoot_2.png",
                                                          this,
                                                          menu_selector(Main::onPlayBtnShootClick) );
    playBtnShoot->setPosition( ccp(winSize.width/2 + playBtnShoot->getContentSize().width/2 + 20, winSize.height/2) );

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, playBtnRun, playBtnShoot, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();

    return true;
}

void Main::createBackObjecs()
{
    _staticObjects = new CCArray();
    _movingObjects = new CCArray();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    CCSprite* object;
    
    int i;
    int numObjects = arc4random() % 30;
    char* staticImgs[4] = {"Star_1.png", "Star_2.png", "SaturnView.png", "PlanetView.png"};
    for (i = 0; i < numObjects; ++i) {
        object = CCSprite::create(staticImgs[arc4random() % 4]);
        _staticObjects->addObject(object);
        object->setScale(0.3f);
        object->setPosition(ccp(arc4random() % (int)winSize.width, arc4random() % (int)winSize.height));
        this->addChild(object);
    }
    
    numObjects = arc4random() % 10;
    char* dynamicImgs[4] = {"EnemyView.png", "EnemyView_2.png", "Star_2.png", "PlanetView.png"};
    for (i = 0; i < numObjects; ++i) {
        object = CCSprite::create(dynamicImgs[arc4random() % 4]);
        _movingObjects->addObject(object);
        object->setScale(0.3f);
        object->setPosition(ccp(arc4random() % (int)winSize.width, arc4random() % (int)winSize.height));
        this->addChild(object);
    }
    
}

void Main::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

void Main::onPlayBtnRunClick(CCObject* pSender)
{
    
}

void Main::onPlayBtnShootClick(CCObject* pSender)
{
    
}
