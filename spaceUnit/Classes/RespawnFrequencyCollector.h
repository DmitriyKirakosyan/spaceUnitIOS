//
//  RespawnFrequencyCollector.h
//  spaceUnit
//
//  Created by PC on 8/9/14.
//
//

#ifndef spaceUnit_RespawnFrequencyCollector_h
#define spaceUnit_RespawnFrequencyCollector_h

class RespawnFrequencyCollector {
    
	//TODO game balance here
public:
    static float getFrequency(int enemyType, int gameType, float timeState) {
		float result;
		if (enemyType == ASTEROID) {
			if (gameType == RUN_GAME) {
				if (timeState < 3) { //чтобы вначале небыло простоя
					result = 0.1f;
				} else {
					result =  0.1f * (timeState / 200); //after 200 sec -- 0.1 frequency
				}
			} else {
				if (timeState < 3) {
					result = 0.1f;
				} else {
					result = 0.1f * (timeState / 200);
				}
			}
		} else if (enemyType == MINE) {
			result = 0.1f * (timeState / 1000);
		} else if (enemyType == CRAZY_MINE) {
			result = 0.1f * (timeState / 1500);
		} else if (enemyType == ALIEN) {
			result = 0.1f * (timeState / 3000);
		} else {
			//throw new Error("unknown enemy : " + enemyType);
		}
		return result;
	}
};


#endif
