//
//  SpaceObject.h
//  spaceUnit
//
//  Created by Dmitriy on 12/30/12.
//
//

#ifndef spaceUnit_SpaceObject_h
#define spaceUnit_SpaceObject_h

#include "cocos2d.h"
#include "IBlowMaker.h"
#include "SimpleAudioEngine.h"

class SpaceObject : public cocos2d::CCSprite
{

private:
    float _scale;

protected:
    cocos2d::CCPoint _position;
    float _rotation;
    float _width;
    float _height;
    float _isDead;
    
public:
    SpaceObject(cocos2d::CCSize screenSize, const char *imageFile, bool randomScale = false):_screenSize(screenSize) {
        float scale = randomScale ? (arc4random() % 100) / 200.0 + .7 : 1.0f;
        this->setScale(scale);
        _position = ccp(0, 0);
        _rotation = 0;
        _isDead = false;
        this->initWithFile(imageFile);
    }
    
    void tick(float dt) {
    }
    
    void setDead() {
        _isDead = true;
    }
    
    bool isDead() { return _isDead; }
    
    void setImage(const char *imageFile) {
        this->initWithFile(imageFile);
    }
    
    void setAlpha(float alpha) {
        this->setOpacity(alpha);
	}
    
    inline void setScreenSize(cocos2d::CCSize value) { _screenSize = value; }

    inline void setRandomPosition()
    {
        cocos2d::CCPoint position = ccp(arc4random() % (int)_screenSize.width, arc4random() % (int)_screenSize.height);
        this->setPosition(position);
    }
    
    void explode(IBlowMaker *blowMaker) {
		blowMaker->makeBlow(this);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("bam2.wav");
	}
    
    static inline int getSizeImgArray() { return 4; }
    
    static const char* staticImgs[4];
    
    

public:
    cocos2d::CCSize _screenSize;
};


#endif
