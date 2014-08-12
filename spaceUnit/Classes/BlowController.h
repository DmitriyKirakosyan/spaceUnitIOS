//
//  BlowController.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_BlowController_h
#define spaceUnit_BlowController_h

#include "IBlowMaker.h"
#include "BlowAnimation.h"
#include <list>


class BlowController : public IBlowMaker {
private:
    std::list<BlowAnimation *> *_blows;
    
public:
    BlowController() { _blows = NULL; }
    
	void tick(float dt) {
		if (_blows != NULL) {
            std::list<BlowAnimation *> *animationsForRemove = new std::list<BlowAnimation *>();
            std::list<BlowAnimation *>::iterator iter;
			for (iter = _blows->begin(); iter != _blows->end(); iter++)
			{
                BlowAnimation * blow = (BlowAnimation *)(*iter);
				if (blow->_blowAnim->isAnimationFinished())
				{
					animationsForRemove->push_back(blow);
				} else {
                    blow->_blowAnim->tick(dt);
                    blow->_target->initWithSpriteFrame(blow->_blowAnim->getCurrentSkin());
				}
                
			}
            
			for (iter = animationsForRemove->begin(); iter != animationsForRemove->end(); iter++)
			{
                BlowAnimation *blow = (BlowAnimation *)(*iter);
				_blows->remove(blow);
                blow->_target->setDead();
                blow->_target->removeFromParentAndCleanup(true);
                blow->_blowAnim->release();
                delete blow;
                
			}
			animationsForRemove->clear();
		}
	}
    
	void makeBlow(SpaceObject *target) {
		BlowAnimation *blow = new BlowAnimation(target);
		if (_blows == NULL) {
			_blows = new std::list<BlowAnimation *>();
		}
		_blows->push_back(blow);
	}
    
	std::list<BlowAnimation *> * getBlows() { return _blows; }
};


#endif
