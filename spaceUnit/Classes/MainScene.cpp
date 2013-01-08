#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "Enemy.h"
#include "GameScene.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int Main::MAX_STATIC_OBJECTS = 30;
const int Main::MAX_MOVING_OBJECTS = 20;
const int Main::MIN_MOVING_OBJECTS = 5;

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

    //кнопка старта игры типа "бег"
    CCMenuItemImage *playBtnRun = CCMenuItemImage::create(
                                                          "PlayBtnRun_1.png",
                                                          "PlayBtnRun_2.png",
                                                          this,
                                                          menu_selector(Main::onPlayBtnRunClick) );
    playBtnRun->setPosition( ccp(winSize.width/2 - playBtnRun->getContentSize().width - 20, winSize.height/2) );
    playBtnRun->setScale(2.0f);

    //кнопка старта игры типа "стрельба"
    CCMenuItemImage *playBtnShoot = CCMenuItemImage::create(
                                                          "PlayBtnShoot_1.png",
                                                          "PlayBtnShoot_2.png",
                                                          this,
                                                          menu_selector(Main::onPlayBtnShootClick) );
    playBtnShoot->setPosition( ccp(winSize.width/2 + playBtnShoot->getContentSize().width + 20, winSize.height/2) );
    playBtnShoot->setScale(2.0f);

    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(pCloseItem, playBtnRun, playBtnShoot, NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);

    // ask director the window size
    CCSize size = CCDirector::sharedDirector()->getWinSize();
    
    this->schedule(schedule_selector(Main::update));

    return true;
}

void Main::update(CCTime dt)
{
    CCObject* item;
    CCARRAY_FOREACH(_movingObjects, item)
    {
        ((Enemy*) item)->simpleMove();
    }
}

void Main::createBackObjecs()
{
    _staticObjects = new CCArray();
    _movingObjects = new CCArray();
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    SpaceObject* object;
    
    int i;
    int numObjects = arc4random() % MAX_STATIC_OBJECTS;

    for (i = 0; i < numObjects; ++i) {
        object = new SpaceObject(winSize);
        object->initWithFile(SpaceObject::staticImgs[arc4random() % SpaceObject::getSizeImgArray()]);
        _staticObjects->addObject(object);
        object->setRandomPosition();
        this->addChild(object);
    }
    
    Enemy* movingObject;
    
    numObjects = arc4random() % (MAX_MOVING_OBJECTS + 1 - MIN_MOVING_OBJECTS) + MIN_MOVING_OBJECTS;
    
    for (i = 0; i < numObjects; ++i) {
        movingObject = new Enemy(winSize, true);
        movingObject->setRandomLook();
        _movingObjects->addObject(movingObject);
        
        movingObject->setRandomPosition();
        movingObject->setRandomBehaviour();
        
        this->addChild(movingObject);
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
    GameScene* gameScene = GameScene::create(GameScene::RUN_GAME);
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

void Main::onPlayBtnShootClick(CCObject* pSender)
{
    GameScene* gameScene = GameScene::create(GameScene::SHOOT_GAME);
    CCDirector::sharedDirector()->replaceScene(gameScene);
}
