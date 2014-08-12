//
//  Enemy.h
//  spaceUnit
//
//  Created by Dmitriy on 12/29/12.
//
//

#ifndef __spaceUnit__Enemy__
#define __spaceUnit__Enemy__

#include "MovingSpaceObject.h"
#include "AEnemyBehaviour.h"
#include "EBehaviourENUM.h"
#include "BorderBehaviorENUM.h"
#include <vector>

class Enemy : public  MovingSpaceObject {
    
protected:
	SpaceObject *_target;

private:
	int _enemyType;
    std::vector<AEnemyBehaviour *> *_behaviours;
    
public:
    
	Enemy(cocos2d::CCSize screenSize, int enemyType, const char *imageFile, bool randomScale, int borderBehaviour)
    : MovingSpaceObject(screenSize, imageFile, randomScale, borderBehaviour) {
		_enemyType = enemyType;
        _behaviours = new std::vector<AEnemyBehaviour *>();
	}
    
	int getEnemyType() { return _enemyType; }
    
    
	void tick(float dt) {
        MovingSpaceObject::tick(dt);
		if (_behaviours != NULL) {
            
            std::vector<AEnemyBehaviour *> *clonedBehaviours = new std::vector<AEnemyBehaviour *>();
            std::vector<AEnemyBehaviour *>::iterator iter;
            
            for (iter = _behaviours->begin(); iter != _behaviours->end(); iter++) {
                AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
                clonedBehaviours->push_back(behaviour);
			}
            
            for (iter = clonedBehaviours->begin(); iter != clonedBehaviours->end(); iter++) {
                AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
                behaviour->tick(dt);
			}
            
            clonedBehaviours->clear();
        }
	}
    
	
	void setDead(){
        MovingSpaceObject::setDead();
		this->removeAllBehaviours();
	}
    
	/**
	 *
	 * @param behaviour
	 * @throws Error "behaviour already exists"
	 */
	void addBehaviour(AEnemyBehaviour *behaviour) {
		if (_behaviours == NULL) { _behaviours = new std::vector<AEnemyBehaviour *>(); }
		if (this->hasBehaviour(behaviour->getName())) {
			//throw new Error("behaviour already exists");
		}
		_behaviours->push_back(behaviour);
		behaviour->start();
	}
    
	/**
	 *
	 */
	void removeAllBehaviours() {
		if (_behaviours != NULL) {
            std::vector<AEnemyBehaviour *>::iterator iter;
			for (iter = _behaviours->begin(); iter != _behaviours->end(); iter++) {
                AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
				behaviour->stop();
			}
			_behaviours->clear();
		}
	}
    
	/**
	 *
	 * @param behaviourName
	 * @throws Error "behaviour " + behaviourName + " not found in behaviours"
	 */
	void removeBehaviour(int behaviourName) {
		bool behaviourFound = false;
		if (_behaviours != NULL) {
            std::vector<AEnemyBehaviour *>::iterator iter;
			for (iter = _behaviours->begin(); iter != _behaviours->end(); iter++) {
                AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
				if (behaviour->getName() == behaviourName) {
                    _behaviours->erase(iter);
					behaviour->stop();
					behaviourFound = true;
					break;
				}
			}
		}
		if (!behaviourFound) {
			//throw new Error("behaviour " + behaviourName + " not found in behaviours");
		}
	}
    
	bool hasBehaviour(int behaviourName) {
		bool result = false;
        std::vector<AEnemyBehaviour *>::iterator iter;
        for (iter = _behaviours->begin(); iter != _behaviours->end(); iter++) {
            AEnemyBehaviour *behaviour = (AEnemyBehaviour *)(*iter);
            if (behaviour->getName() == behaviourName) {
				result = true;
				break;
			}
        }
		return result;
	}
    
	void setTarget(SpaceObject *target) {
		_target = target;
	}
    
    
};

#endif /* defined(__spaceUnit__Enemy__) */

