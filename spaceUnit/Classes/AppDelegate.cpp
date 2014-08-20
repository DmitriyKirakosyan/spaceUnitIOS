//
//  spaceUnitAppDelegate.cpp
//  spaceUnit
//
//  Created by Dmitriy on 12/25/12.
//  Copyright __MyCompanyName__ 2012. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "MainScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // initialize director
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    CCSize screenSize = CCEGLView::sharedOpenGLView()->getFrameSize();
    //CCFileUtils *pFileUtils = CCFileUtils::sharedFileUtils();
    //std::vector<std::string> searchPaths;
    
    CCSize designSize = CCSizeMake(960, 640);
    CCSize resourceSize;
    
    // if the device is iPad
    if (screenSize.height >= 768) {
        //searchPaths.push_back("hd");
        //searchPaths.push_back("sd");
        resourceSize = CCSizeMake(1024, 768);
        designSize = CCSizeMake(1024, 768);
    }
    // if the device is iPhone
    else{
        // for retina iPhone
        if (screenSize.height > 320) {
            //searchPaths.push_back("hd");
            //searchPaths.push_back("sd");
            resourceSize = CCSizeMake(960, 640);
        }
        else{
            //searchPaths.push_back("sd");
            resourceSize = CCSizeMake(480, 320);
        }
    }
    //searchPaths.push_back("WhackAMoleSounds");
    
    
   // pFileUtils->setSearchPaths(searchPaths);
    pDirector->setContentScaleFactor(/*resourceSize.width / designSize.width*/1);
    
    CCEGLView::sharedOpenGLView()->setDesignResolutionSize(designSize.width, designSize.height, /*kResolutionExactFit*/kResolutionShowAll);
    // turn on display FPS
   // pDirector->setDisplayStats(true);

    // set FPS. the default value is 1.0/60 if you don't call this
    pDirector->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    CCScene *pScene = Main::scene();
    

    // run
    pDirector->runWithScene(pScene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground()
{
    CCDirector::sharedDirector()->pause();

    // if you use SimpleAudioEngine, it must be paused
    // SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground()
{
    CCDirector::sharedDirector()->resume();
    
    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::sharedEngine()->resumeBackgroundMusic();
}
