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

class SpaceObject : public cocos2d::CCSprite
{
public:
    SpaceObject(cocos2d::CCSize screenSize, bool randomScale = false):_screenSize(screenSize) {
        float scale = randomScale ? (arc4random() % 100) / 200.0 + .5 : 0.5f;
        cocos2d::CCSprite::setScale(scale);
    }

    inline void setScreenSize(cocos2d::CCSize value) { _screenSize = value; }

    inline void setRandomPosition()
    {
        cocos2d::CCPoint position = ccp(arc4random() % (int)_screenSize.width, arc4random() % (int)_screenSize.height);
        this->setPosition(position);
    }
    
    static inline int getSizeImgArray() { return 4; }
    
    static const char* staticImgs[4];
    static const char* dynamicImgs[4];

protected:
    cocos2d::CCSize _screenSize;
};


#endif
