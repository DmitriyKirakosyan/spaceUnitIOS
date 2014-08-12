//
//  BlowAnimation.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_BlowAnimation_h
#define spaceUnit_BlowAnimation_h

#include "AnimatedSprite.h"

class BlowAnimation {
public:
    SpaceObject *_target;
    AnimatedSprite *_blowAnim;
    
	BlowAnimation(SpaceObject *target) {
        _target = target;
        cocos2d::CCArray *pArray = new cocos2d::CCArray();
        const char * array[] = {"blow1.png", "blow2.png", "blow3.png", "blow4.png", "blow5.png", "blow6.png", "blow7.png"};
        for(int i = 0; i < 7; i++) {
            cocos2d::CCSpriteFrame *frame = cocos2d::CCSpriteFrame::create(array[i], cocos2d::CCRect(0, 0, 73, 73));
            pArray->addObject(frame);
        }
        _blowAnim = new AnimatedSprite(pArray, 0.02f);
	}
};

#endif
