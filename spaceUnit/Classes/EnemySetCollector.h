//
//  EnemySetCollector.h
//  spaceUnit
//
//  Created by PC on 8/9/14.
//
//

#ifndef spaceUnit_EnemySetCollector_h
#define spaceUnit_EnemySetCollector_h

#include <vector>
class EnemySetCollector {
    
public:
    static std::vector<int> * getEnemySet(int strategy) {
		std::vector<int>* result = new std::vector<int>();
		if (strategy == RUN_GAME) {
			result->push_back(ASTEROID);
        } else if (strategy == SHOOT_GAME) {
			result->push_back(ASTEROID);
			result->push_back(ALIEN);
			result->push_back(MINE);
			result->push_back(CRAZY_MINE);
		} else {
			//throw new Error("unknown game strategy");
		}
		return result;
	}
};

#endif
