//
//  Ship.h
//  spaceUnit
//
//  Created by Dmitriy on 1/2/13.
//
//

#ifndef __spaceUnit__Ship__
#define __spaceUnit__Ship__

#include "MovingSpaceObject.h"
#include "AGun.h"
#include "Assets.h"
#include "HeroSkin.h"
#include "MultiGun.h"
#include "BasicHeroSkin.h"
#include <list>

class Ship : public MovingSpaceObject {
    
private:
	AGun *_gun;
    cocos2d::CCPoint _targetPosition;
    cocos2d::CCPoint _targetForShooting;
    HeroSkin *_skin;
    
    
    
public:
    Ship(HeroSkin *skin)
    : MovingSpaceObject(cocos2d::CCDirector::sharedDirector()->getWinSize(), Assets::ship, false, STOP)
	{
        _skin = skin;
        _targetPosition = cocos2d::CCPointZero;
        _targetForShooting = cocos2d::CCPointZero;
        _gun = NULL;
        
        /*cocos2d::CCArray *pArray = new cocos2d::CCArray();
        const char * array[] = {"ship1.png", "ship2.png", "ship3.png"};
        for(int i = 0; i < 3; i++) {
            cocos2d::CCSpriteFrame *frame = cocos2d::CCSpriteFrame::create(array[i], cocos2d::CCRect(0, 0, 52, 43));
            pArray->addObject(frame);
        }
        shipAnim = new HeroSkin(pArray, 0.1f);*/
	}
    
    Ship(): MovingSpaceObject(cocos2d::CCDirector::sharedDirector()->getWinSize(), Assets::ship, false, STOP) {
        _skin = new BasicHeroSkin(this);
        _targetPosition = cocos2d::CCPointZero;
        _targetForShooting = cocos2d::CCPointZero;
        _gun = NULL;
    }
    
    void setSkin(HeroSkin *skin)
	{
		_skin = skin;
	}
    
    HeroSkin *getSkin() {
        return _skin;
    }
    
	void setGun(AGun *gun) {
		_gun = gun;
	}
	AGun *getGun() { return _gun; }
    
    
	void tick(float dt)
	{
        
        if(this->isMoving()) {
            MovingSpaceObject::tick(dt);
            if(isReachedTargetPos()) {
                this->setVelocity(0.0f, 0.0f);
            }
            _skin->tick(dt, isMoving());
        }
		if (_gun != NULL) {
            _gun->tick(dt);
        }
	}
    
    bool isReachedTargetPos() {
        float dx = fabs(this->getPosition().x - _targetPosition.x);
        float dy = fabs(this->getPosition().y - _targetPosition.y);
        if(dx < 5 && dy < 5)
            return true;
        else
            return false;
    }
    
    inline cocos2d::CCPoint getTargetPosition() { return _targetPosition; }
    inline void setTargetPosition(cocos2d::CCPoint value) { _targetPosition = value; }
    inline void setTargetForShooting(cocos2d::CCPoint value) { _targetForShooting = value; }
    
    
	void shoot(IShooter *shooter, float targetX, float targetY) {
		if (_gun == NULL) {
			//throw new Error("cant shoot, gun not equiped");
		}
		if (_gun->isReadyForShoot()) {
			_gun->shoot(shooter, this, ccp(targetX, targetY));
		}
	}
    
	
	void setDead() {
        MovingSpaceObject::setDead();
		_gun = NULL;
	}
    
	void moveOn(float dx, float dy) {
		/*float h = (float) sqrtf((double) (dx * dx + dy * dy) );
		float vx = dx / h * _generalSpeed;
		float vy = dy / h * _generalSpeed;
        
		this->setVelocity(vx, vy);
		if (_skin->rotatable()) {
			this->rotateTo(_position.x + vx, _position.y + vy);
		}*/
	}
    
};

#endif /* defined(__spaceUnit__Ship__) */
