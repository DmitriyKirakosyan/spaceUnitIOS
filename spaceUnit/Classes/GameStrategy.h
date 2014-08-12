//
//  GameStrategy.h
//  spaceUnit
//
//  Created by Dmitriy on 1/3/13.
//
//

#ifndef spaceUnit_GameStrategy_h
#define spaceUnit_GameStrategy_h

#include "cocos2d.h"
#include "Enemy.h"
#include "Ship.h"
#include "GameStatus.h"
#include "EnemyFactory.h"
#include "BlowController.h"
#include "ImpactController.h"
#include "EnemySetCollector.h"
#include "RespawnFrequencyCollector.h"
#include "BehaviourOptionsData.h"
#include "Score.h"
#include "Ability.h"

class Ship;

class GameStrategy
{
public:
    GameStrategy(cocos2d::CCNode* screenContainer, Ship* ship, int gameType):_ship(ship),_screenContainer(screenContainer), _gameType(gameType) {
        _enemies = new cocos2d::CCArray();
        _movingTouch = NULL;
        _gameStatus = IN_PROCESS;
        _timeState = 0;
        _blowController = new BlowController();
        _impactController = new ImpactController(_blowController, screenContainer);
    };
    
    virtual void touchesBegan(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
    virtual void touchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;
    virtual void touchesMoved(cocos2d::CCSet* touches, cocos2d::CCEvent* event) = 0;

public:
    Ability *_ability;
private:
    int _gameType;
    int _gameStatus;
    
    
protected:
    
    cocos2d::CCArray* _enemies;
    Ship* _ship;
    cocos2d::CCNode* _screenContainer;

    cocos2d::CCTouch* _movingTouch;
    std::vector<int> *_availableEnemyTypes;
    
    BlowController *_blowController;
    ImpactController *_impactController;
    
    float _timeState;
    

public:
    
    void pauseGame() { _gameStatus = PAUSE; }
    
    void resumeGame() { _gameStatus = IN_PROCESS; }
    
    bool isPaused() { return _gameStatus == PAUSE; }
    
    void startGame() { _gameStatus = IN_PROCESS; }
    
    void stopGame() {
        //hz what here need to be
    }
    
    int getGameStatus() { return _gameStatus; }
    
    virtual Score *getScore() = 0;
    virtual void useAbility() = 0;

    virtual void tick(float dt) {
        _timeState += dt;
		if (_gameStatus == IN_PROCESS) this->createEnemies();
        
		_blowController->tick(dt);
		_impactController->tick(dt);
		this->tickEnemies(dt);
        
		std::list<SpaceObject *> *spaceObjects = getAllSpaceObjects();
        std::list<SpaceObject *>::iterator iter;
		for (iter = spaceObjects->begin(); iter != spaceObjects->end(); iter++) {
            SpaceObject *spaceObject = (SpaceObject *)(*iter);
			_impactController->execute(spaceObject);
		}
        
		if (_ship->isDead()) {
			this->gameOver();
		}
    }
    
    
    virtual std::list<SpaceObject *> *getAllSpaceObjects() {
        std::list<SpaceObject *> *result = new std::list<SpaceObject *>();
        for(int i = 0; i < _enemies->count(); i++) {
            SpaceObject *object = (SpaceObject *)_enemies->objectAtIndex(i);
            result->push_back(object);
        }
		result->push_back(_ship);
		return result;
    }
    
    virtual std::list <cocos2d::CCSprite *> * getDrawableObjects() {
		std::list <cocos2d::CCSprite *> *result = new std::list <cocos2d::CCSprite *>();
        /*for(int i = 0; i < _enemies->count(); i++) {
            Enemy *enemy = (Enemy *)_enemies->objectAtIndex(i);
			if (!enemy->isDead()) result->push_back(enemy);
		}
        
		if (_blowController->getBlows() != NULL) {
            std::list<BlowAnimation *> * blows = _blowController->getBlows();
            std::list<BlowAnimation *>::iterator iter
			for (AnimatedSprite animation : _blowController.getBlows()) {
				result.add(animation);
			}
		}
        
		for (ISpaceImpact impact : _impactController.getImpacts()) {
			result.add(impact.getImage());
		}
        
		if (!_heroShip.isDead()) result.add(_heroShip.getImage());
        */
		return result;
	}

    
    
    void tickEnemies(float delta) {
        cocos2d::CCArray *deadEnemies = NULL;
        
		for (int i = 0; i < _enemies->count(); i++)
		{
            Enemy *enemy = (Enemy *)_enemies->objectAtIndex(i);
			if (enemy->isDead()) {
				if (deadEnemies == NULL) { deadEnemies = cocos2d::CCArray::create(); }
				deadEnemies->addObject(enemy);
			} else {
				enemy->tick(delta);
			}
		}
		if (deadEnemies != NULL) {
            for(int i = 0; i < deadEnemies->count(); i++) {
                Enemy *enemy = (Enemy *)deadEnemies->objectAtIndex(i);
                _enemies->removeObject(enemy);
                enemy->removeFromParentAndCleanup(true);
            }
		}
	}
    
    void createEnemies() {
		if(_availableEnemyTypes == NULL || _availableEnemyTypes->size() == 0) {
            return;
        }
        
		int enemyType;
        std::vector<int>::iterator iter;
		for (iter = _availableEnemyTypes->begin(); iter != _availableEnemyTypes->end(); iter++) {
			enemyType = (*iter);
            float p = (arc4random() % 10000) / 10000.0f;
			if (p < RespawnFrequencyCollector::getFrequency(enemyType, _gameType, _timeState)) {
				Enemy *enemy = EnemyFactory::createEnemy(enemyType);
				_enemies->addObject(enemy);
				this->setEnemyParams(enemy);
                _screenContainer->addChild(enemy);
			}
		}
	}
    
    virtual void setEnemyParams(Enemy* enemy) = 0;
    
    void gameOver() {
        _gameStatus = GAME_OVER;
        for(int i = 0; i < _enemies->count(); i++) {
            Enemy *enemy = (Enemy *)_enemies->objectAtIndex(i);
            enemy->removeAllBehaviours();
        }
    }

    virtual void explodeEnemy(Enemy* enemy)
    {
        enemy->setGeneralSpeed(0);
        _enemies->removeObject(enemy);
        enemy->explode(_blowController);
    }
    
    virtual void explodeHero() {
        _ship->stopMoving();
        _ship->setGeneralSpeed(0);
        _ship->explode(_blowController);
    }
    
protected:
    bool checkObjectsHit(SpaceObject *object1, SpaceObject *object2) {
		if (object1->isDead() || object2->isDead()) { return false; }
        
		float distance;
		float radius1, radius2;
        cocos2d::CCPoint position1, position2;
		radius1 = object1->getContentSize().height / 2;
		radius2 = object2->getContentSize().height / 2;
		position1 = object1->getPosition();
		position2 = object2->getPosition();
        
		distance = ccpDistance(position1, position2);
		return distance < radius1 + radius2;
	}


};


#endif
