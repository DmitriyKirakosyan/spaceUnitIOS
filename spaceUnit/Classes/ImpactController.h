//
//  ImpactController.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_ImpactController_h
#define spaceUnit_ImpactController_h

#include "IImpactMaker.h"
#include "ISpaceImpact.h"
#include "BlowImpact.h"
#include "AbilityBlowImpact.h"

#include <list>

class ImpactController :public IImpactMaker {
private:
    std::list<ISpaceImpact *> *_impacts;
    
	IBlowMaker *_blowMaker;
    cocos2d::CCNode *_parentNode;
    
public:
    ImpactController(IBlowMaker *blowMaker, cocos2d::CCNode *parentNode) {
		_impacts = new std::list<ISpaceImpact *>();
		_blowMaker = blowMaker;
        _parentNode = parentNode;
	}
    
	void execute(SpaceObject *object) {
        std::list<ISpaceImpact *>::iterator iter;
		for (iter = _impacts->begin(); iter != _impacts->end(); iter++) {
			ISpaceImpact *impact = (ISpaceImpact *)(*iter);
            impact->execute(object);
		}
	}
    
	void tick(float dt) {
        std::list<ISpaceImpact *> *completedImpacts = new std::list<ISpaceImpact *>();
        std::list<ISpaceImpact *>::iterator iter;
		for (iter = _impacts->begin(); iter != _impacts->end(); iter++) {
            ISpaceImpact *impact = (ISpaceImpact *)(*iter);
			if (impact->isComplete()) {
				completedImpacts->push_back(impact);
			} else {
				impact->tick(dt);
			}
		}
        
        for (iter = completedImpacts->begin(); iter != completedImpacts->end(); iter++) {
            ISpaceImpact *impact = (ISpaceImpact *)(*iter);
			impact->stop();
			_impacts->remove(impact);
            ((cocos2d::CCSprite *)impact)->release();
            
		}
		completedImpacts->clear();
	}
    
	void createBlow(float x, float y) {
		ISpaceImpact *blowImpact = new BlowImpact(x, y, _blowMaker, _parentNode);
		blowImpact->start();
		_impacts->push_back(blowImpact);
	}
    
	void createAbilityBlow(float x, float y) {
		ISpaceImpact *abilityImpact = new AbilityBlowImpact(x, y, _blowMaker, _parentNode);
		abilityImpact->start();
		_impacts->push_back(abilityImpact);
	}
    
	std::list<ISpaceImpact *> * getImpacts() { return _impacts; }
};

#endif
