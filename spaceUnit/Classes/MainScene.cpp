#include "MainScene.h"
#include "SimpleAudioEngine.h"
#include "GameScene.h"
#include "BorderBehaviorENUM.h"
#include "EnemyFactory.h"
#include "GameStatus.h"

using namespace cocos2d;
using namespace CocosDenshion;

const int Main::MAX_STATIC_OBJECTS = 30;
const int Main::MAX_MOVING_OBJECTS = 30;
const int Main::MIN_MOVING_OBJECTS = 20;

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
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    spriteBatch = new CCSpriteBatchNode();
    
    CCSprite *backSprite = CCSprite::create("firstscreen_back.png");
    backSprite->setPosition(ccp(winSize.width / 2, winSize.height / 2));
    backSprite->setScale(1.3f);
    this->addChild(backSprite);
    
    this->initMenuItems();
    this->schedule(schedule_selector(Main::update));

    SimpleAudioEngine::sharedEngine()->stopAllEffects();
    SimpleAudioEngine::sharedEngine()->playBackgroundMusic("mainmenu.mp3", true);
    return true;
}

void Main::initMenuItems() {
    
    
    CCSize winSize = CCDirector::sharedDirector()->getWinSize();
    
    _behavior = new AsteroidsBehavior(15, spriteBatch);
    std::list<MovingSpaceObject *> *spaceObjcets = _behavior->getSpaceObjects();
    std::list<MovingSpaceObject *>::iterator iter;
    for(iter = spaceObjcets->begin(); iter != spaceObjcets->end(); iter++) {
        MovingSpaceObject *spaceObject = (MovingSpaceObject *)(*iter);
        this->addChild(spaceObject);
    }
    

    
    //кнопка старта игры типа "бег"
    CCMenuItemImage *playBtnRun = CCMenuItemImage::create(
                                                          "runBtn_Up.png",
                                                          "runBtn_Down.png",
                                                          this,
                                                          menu_selector(Main::onPlayBtnRunClick));
    playBtnRun->setAnchorPoint(ccp(0,0));
    playBtnRun->setPosition( ccp(winSize.width/2 - playBtnRun->getContentSize().width - 20, winSize.height / 2 - 30) );
   
    
    //кнопка старта игры типа "стрельба"
    CCMenuItemImage *playBtnShoot = CCMenuItemImage::create(
                                                            "shootBtn_Up.png",
                                                            "shootBtn_Down.png",
                                                            this,
                                                            menu_selector(Main::onPlayBtnShootClick));
    playBtnShoot->setAnchorPoint(ccp(0, 0));
    playBtnShoot->setPosition( ccp(winSize.width/2 + 20, winSize.height / 2 - 30) );
    
    
    
    CCMenuItemImage *pScoreBtn = CCMenuItemImage::create(
                                                          "scoreBtn_Up.png",
                                                          "scoreBtn_Down.png",
                                                          this,
                                                          menu_selector(Main::menuSoundCallback) );
    pScoreBtn->setAnchorPoint(ccp(0.5, 1));
    pScoreBtn->setPosition( ccp(winSize.width / 4, winSize.height / 2 - 95));
    
    CCMenuItemImage *pAchieveBtn = CCMenuItemImage::create(
                                                         "achieveBtn_Up.png",
                                                         "achieveBtn_Down.png",
                                                         this,
                                                         menu_selector(Main::menuSoundCallback) );
    pAchieveBtn->setAnchorPoint(ccp(0.5, 1));
    pAchieveBtn->setPosition( ccp(winSize.width * 3 / 4 , winSize.height / 2 - 95));
    
    CCMenuItemImage *pAboutBtn = CCMenuItemImage::create(
                                                           "aboutBtn_Up.png",
                                                           "aboutBtn_Down.png",
                                                           this,
                                                           menu_selector(Main::menuSoundCallback) );
    pAboutBtn->setAnchorPoint(ccp(0.5, 0));
    pAboutBtn->setPosition( ccp(winSize.width / 2 , 50));
    
    /*CCMenuItemImage *pAudioBtn = CCMenuItemImage::create(
                                                        "soundBtn_On.png",
                                                        "soundBtn_Off.png",
                                                        this,
                                                        menu_selector(Main::menuSoundCallback) );
    pAudioBtn->setAnchorPoint(ccp(0, 0));
    pAudioBtn->setPosition( ccp(
                                winSize.width - pAudioBtn->getContentSize().width - 10,
                                winSize.height - pAudioBtn->getContentSize().height - 50
                            ));*/
    
    // create menu, it's an autorelease object
    CCMenu* pMenu = CCMenu::create(playBtnRun, playBtnShoot, pScoreBtn, pAchieveBtn, pAboutBtn, /*pAudioBtn,*/ NULL);
    pMenu->setPosition( CCPointZero );
    this->addChild(pMenu, 1);
}

void Main::update(float dt)
{
    _behavior->tick(dt);
}



void Main::menuSoundCallback(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("click.mp3", false);
}
void Main::menuCloseCallback(CCObject* pSender)
{
    CCDirector::sharedDirector()->end();
    SimpleAudioEngine::sharedEngine()->playEffect("click.mp3", false);

    #if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
        exit(0);
    #endif

}

void Main::onPlayBtnRunClick(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("click.mp3", false);
    GameScene* gameScene = GameScene::create(RUN_GAME);
    CCDirector::sharedDirector()->replaceScene(gameScene);
}

void Main::onPlayBtnShootClick(CCObject* pSender)
{
    SimpleAudioEngine::sharedEngine()->playEffect("click.mp3", false);
    GameScene* gameScene = GameScene::create(SHOOT_GAME);
    CCDirector::sharedDirector()->replaceScene(gameScene);
}
