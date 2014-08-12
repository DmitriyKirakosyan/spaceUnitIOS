//
//  BlowImpact.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_BlowImpact_h
#define spaceUnit_BlowImpact_h

#include "SpaceObject.h"
#include "ISpaceImpact.h"

class BlowImpact : public SpaceObject, public ISpaceImpact {
private:
    const float MAX_STRAIGHT = 255; //5 seconds active
	const float MAX_SCALE = 3 ;
	const float KICK_STRAIGHT = 30;
	
    float _currentStraight;
    
	IBlowMaker *_blowMaker;
    
public:

    BlowImpact(float x, float y, IBlowMaker *blowMaker, cocos2d::CCNode *parentNode)
    : SpaceObject(cocos2d::CCDirector::sharedDirector()->getWinSize(), Assets::blowCircle, false) {
        this->setPosition(ccp(x, y));
        parentNode->addChild(this);
		_blowMaker = blowMaker;
	}
    

	void start() {
		_currentStraight = MAX_STRAIGHT;
	}
    
	
	void stop() {
		_currentStraight = 0;
	}
    
	
	bool isComplete() {
		return _currentStraight == 0;
	}
    
	
	void tick(float dt) {
        SpaceObject::tick(dt);
		this->setScale(this->getScale() + MAX_SCALE * dt);
        setAlpha(_currentStraight);
		_currentStraight -= MAX_STRAIGHT * dt;
		if (_currentStraight < 0) {
            _currentStraight = 0;
            this->removeFromParentAndCleanup(true);
        }
	}
    
	
	void execute(SpaceObject *object) {
        cocos2d::CCPoint objCenter = object->getPosition();
        cocos2d::CCPoint impactCenter = this->getPosition();
		float maxDistance = (this->getContentSize().width * MAX_SCALE)/2;
        
        
		float distanceCoef = (maxDistance - ccpDistance(objCenter, impactCenter))/maxDistance;
		if (distanceCoef <= 0) { return; }
        
		if (distanceCoef > .7f) {
			object->explode(_blowMaker);
			object->setDead();
		}
        
		float impactValue = distanceCoef * KICK_STRAIGHT;
        
		float dx = objCenter.x - impactCenter.x;
		float dy = objCenter.y - impactCenter.y;
		float h = (float) sqrt((double) (dx * dx + dy * dy) );
		float vx = 0;
		float vy = 0;
		if (h != 0){
			vx = (dx / h) * impactValue;
			vy = (dy / h) * impactValue;
		}
        
        cocos2d::CCPoint objPosition = object->getPosition();
		object->setPosition(ccp(objPosition.x + vx, objPosition.y + vy));
	}
};


#endif
