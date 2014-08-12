//
//  ActiveEnemy.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_ActiveEnemy_h
#define spaceUnit_ActiveEnemy_h

#include "Enemy.h"

class ActiveEnemy : public Enemy {
    
private:
    bool _isActiveMode;

public:
	const char *_passiveImage;
	const char *_activeImage;
    
	ActiveEnemy(cocos2d::CCSize winSize, int enemyType, const char * passiveImage, const char * activeImage,
                bool randomScale, int borderBehaviour) : Enemy(winSize, enemyType, passiveImage, randomScale, borderBehaviour) {
		_activeImage = activeImage;
		_passiveImage = passiveImage;
		_isActiveMode = false;
	}
    
	bool isActiveMode() { return _isActiveMode; }
    
	void changeToActiveMode() {
        Enemy::setImage(_activeImage);
		_isActiveMode = true;
	}
    
	void changeToPassiveMode() {
        Enemy::setImage(_passiveImage);
		_isActiveMode = false;
	}
};


#endif
