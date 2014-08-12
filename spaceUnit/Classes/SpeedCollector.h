//
//  SpeedCollector.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_SpeedCollector_h
#define spaceUnit_SpeedCollector_h
#include "EnemyTypeENUM.h"
class SpeedCollector {
    
public:
    static float getHeroSpeed(int gameType) {
		return 3.0f;
	}
    
    static float getEnemySpeed(int enemyType, int gameType) {
		float result = 0.0f;
        //basic enemy (asteroids)
        if (enemyType == ASTEROID) {
            result = (arc4random() % 100) / 100.0f * 2.0f;
        }
        //mine
        else if (enemyType == MINE) {
            result = 1.0f;
        }
        //crazy mine
        else if (enemyType == CRAZY_MINE) {
            result = 1.0f;
        }
        //alien
        else if (enemyType == ALIEN) {
            result = 1.6f;
        }
		return result;
	}
    
	static float getMenuAsteroidSpeed() {
        return ((arc4random() % 100) / 100.0f) * 2.0f;
	}
    
	static float getBulletSpeed(SpaceObject owner, int gameType) {
		return 5.0f;
	}
};


#endif
