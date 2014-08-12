//
//  AsteroidsBehavior.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_AsteroidsBehavior_h
#define spaceUnit_AsteroidsBehavior_h

#include <list>
#include "MovingSpaceObject.h"
#include "BlowController.h"
#include "SpeedCollector.h"
#include "Assets.h"

class AsteroidsBehavior {
	
private:
    int _numStartEnemies;
    std::list<MovingSpaceObject *> *_spaceObjects;
	BlowController *_blowControl;
    
public:
    AsteroidsBehavior(int numStartEnemies, cocos2d::CCSpriteBatchNode *spriteBatch) {
		_numStartEnemies = numStartEnemies;
		
		_blowControl = new BlowController();
		
		_spaceObjects = new std::list<MovingSpaceObject *>();
		for (int i = 0; i < _numStartEnemies; i++) {
            const char *imageFile = Assets::soImages[arc4random() % 2];
			MovingSpaceObject *spaceObject = this->createRandomSpaceObject(imageFile);
			_spaceObjects->push_back(spaceObject);
		}
	}
	
	
    
	void tick(float dt) {
        std::list<MovingSpaceObject *>::iterator iter;
		for (iter = _spaceObjects->begin(); iter != _spaceObjects->end(); iter++) {
            MovingSpaceObject * spaceObject = (MovingSpaceObject *)(*iter);
			spaceObject->tick(dt);
            
		}
		if (_blowControl->getBlows() != NULL) {
			_blowControl->tick(dt);
            
            std::list<BlowAnimation *>::iterator iter;
            std::list<BlowAnimation *> *_blows = _blowControl->getBlows();
			for (iter = _blows->begin(); iter != _blows->end(); iter++) {
				BlowAnimation *blow = (BlowAnimation *)(*iter);
                //blow->tick();
				//blow->draw(_spriteBatch);
			}
		}
	}
    
    std::list<MovingSpaceObject *> * getSpaceObjects() {
        return _spaceObjects;
    }
	
	void setBlow(MovingSpaceObject *spaceObject) {
		_blowControl->makeBlow(spaceObject);
		//Sprite image = new Sprite(Assets.soImages[Math.round((float)Math.random())]);
		//spaceObject = this.createRandomSpaceObject(image);
		spaceObject->setRandomBorderPosition();
	}
	
private:
    MovingSpaceObject *createRandomSpaceObject(const char * imageFile) {
        cocos2d::CCSize winSize = cocos2d::CCDirector::sharedDirector()->getWinSize();
		MovingSpaceObject *spaceObject = new MovingSpaceObject(winSize, imageFile, true, TELEPORT);
		spaceObject->setRandomBorderPosition();
		spaceObject->setGeneralSpeed(SpeedCollector::getMenuAsteroidSpeed());
		spaceObject->setRotationSpeed((((arc4random() % 100) / 100.0f)  * 2 - 1) * 5); //TODO kick it out
        spaceObject->moveTo(arc4random() % (int)winSize.width, arc4random() % (int)winSize.height);
		return spaceObject;
	}
    
};


#endif
