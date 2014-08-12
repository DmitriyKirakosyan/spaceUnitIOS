//
//  BasicHeroSkin.h
//  spaceUnit
//
//  Created by PC on 8/9/14.
//
//

#ifndef spaceUnit_BasicHeroSkin_h
#define spaceUnit_BasicHeroSkin_h

#include "HeroSkin.h"
#include "Assets.h"

class BasicHeroSkin : public HeroSkin {
	//private AnimatedSprite _shipAnim;
	const char * _calmState;
    MovingSpaceObject *_owner;
    
public:
    BasicHeroSkin(MovingSpaceObject *owner) : HeroSkin(Assets::ship){
		_calmState = Assets::ship;
        _owner = owner;
		//_shipAnim = new AnimatedSprite(Assets.shipArray, 0.1f, Animation.LOOP_PINGPONG);
	}
    
	
	bool rotatable() { return true; }
    
	
	void tick(float delta, bool moving) {
		if (moving) {
			//_shipAnim->tick(delta);
			//this.setRegion(_shipAnim.getCurrentRegion());
		}
		else {
			this.setRegion(_calmState);
		}
        cocos2d::CCAnimation a;
        cocos2d::CCAnimate* b;
        
        CCAnimation *a = CCAnimation::
        a->
        
	}
}


#endif
