//
//  BasicHeroSkin.h
//  spaceUnit
//
//  Created by PC on 8/12/14.
//
//

#ifndef spaceUnit_BasicHeroSkin_h
#define spaceUnit_BasicHeroSkin_h

#include "HeroSkin.h"
#include "cocos2d.h"

class BasicHeroSkin : public HeroSkin {
private:
    AnimatedSprite *_shipAnim;
	const char * _calmState = Assets::ship;
    
public:
    BasicHeroSkin(SpaceObject *owner):HeroSkin(owner) {
        cocos2d::CCArray *pArray = new cocos2d::CCArray();
         const char * array[] = {"ship1.png", "ship2.png", "ship3.png"};
         for(int i = 0; i < 3; i++) {
         cocos2d::CCSpriteFrame *frame = cocos2d::CCSpriteFrame::create(array[i], cocos2d::CCRect(0, 0, 52, 43));
         pArray->addObject(frame);
         }
        _shipAnim = new AnimatedSprite(pArray, 0.1f);
	}
    
	
	bool rotatable() { return true; }
    
	
	void tick(float delta, bool moving) {
		if (moving) {
			_shipAnim->tick(delta);
			_owner->initWithSpriteFrame(_shipAnim->getCurrentSkin());
		}
		else {
            _shipAnim->setStartTime(0);
			_owner->initWithFile(_calmState);
		}
        
	}
};

#endif
