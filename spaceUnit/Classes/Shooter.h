//
//  Shooter.h
//  spaceUnit
//
//  Created by PC on 8/10/14.
//
//

#ifndef spaceUnit_Shooter_h
#define spaceUnit_Shooter_h

#include "IShooter.h"
#include "Bullet.h"
#include "SimpleAudioEngine.h"
#include <list>

class Shooter : public IShooter {
public:
	static const float DEFAULT_BULLET_SPEED;
	static const int HERO_BULLET;
	static const int ENEMY_BULLET;
    
private:
    float _bulletSpeed;
    cocos2d::CCNode *_screenContainer;
    
    std::list<Bullet *> *_bullets;
    
public:
    Shooter(cocos2d::CCNode *screenContainer, float bulletSpeed) {
        _screenContainer = screenContainer;
		_bulletSpeed = bulletSpeed;
		_bullets = new std::list<Bullet *>();
	}
    
	Shooter(cocos2d::CCNode *screenContainer) {
        _screenContainer = screenContainer;
		_bulletSpeed = DEFAULT_BULLET_SPEED;
		_bullets = new std::list<Bullet *>();
	}
    
	
	void tick(float delta) {
        
		std::list<Bullet *> *deadBullets = NULL;
        
        std::list<Bullet *>::iterator iter;
        
		for (iter = _bullets->begin(); iter != _bullets->end(); iter++)
		{
            Bullet *bullet = (Bullet *)(*iter);
			if (bullet->isDead()) {
				if (deadBullets == NULL) {
					deadBullets = new std::list<Bullet *>();
				}
				deadBullets->push_back(bullet);
			}
			else {
				bullet->tick(delta);
			}
		}
        
		if (deadBullets != NULL) {
			for (iter = deadBullets->begin(); iter != deadBullets->end(); iter++) {
                Bullet * bullet = (Bullet *)(*iter);
                _bullets->remove(bullet);
                bullet->removeFromParentAndCleanup(true);
            }
			deadBullets->clear();
		}
	}
    
	
	void shoot(SpaceObject *owner, cocos2d::CCPoint from, cocos2d::CCPoint to, int bulletType) {
		if (_bullets == NULL) {
			_bullets = new std::list<Bullet *>();
		}
        
        const char *bulletFile;
		if (bulletType == HERO_BULLET) {
			bulletFile = "ship_gun.png";
		} else {
			bulletFile = "redgun.png";
		}
		Bullet *bullet = new Bullet(bulletFile, owner);
		bullet->setGeneralSpeed(_bulletSpeed);
		bullet->setPosition(ccp(from.x - bullet->getContentSize().width / 2, from.y - bullet->getContentSize().height / 2));
		bullet->moveTo(to.x, to.y);
		bullet->rotateTo(to.x, to.y);
		_bullets->push_back(bullet);
        _screenContainer->addChild(bullet);
		CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("shot.mp3");
	}
    
    void shoot(cocos2d::CCPoint from, cocos2d::CCPoint to, int bulletType) {
		shoot(NULL, from, to, bulletType);
	}
    
	
	void shoot(SpaceObject *owner, cocos2d::CCPoint to, int bulletType) {
		shoot(owner, owner->getPosition(), to, bulletType);
	}
    
	
    std::list<Bullet *> * getBullets() {
		return _bullets;
	}
};

#endif
