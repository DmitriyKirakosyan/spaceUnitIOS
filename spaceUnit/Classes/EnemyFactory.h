//
//  EnemyFactory.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef spaceUnit_EnemyFactory_h
#define spaceUnit_EnemyFactory_h


#include "EnemyTypeENUM.h"
#include "GameStatus.h"
#include "Enemy.h"
#include "ActiveEnemy.h"
#include "Ship.h"
#include "BehaviourOptionsData.h"

class EnemyFactory {
    
public:
	static int _gameType;
	static Ship *_heroShip;
	static BehaviourOptionsData *_behaviourOptions;

public:
	static void init(int gameType, Ship *heroShip, BehaviourOptionsData *behaviourOptions);
	static Enemy *createEnemy(int enemyType);
	static Enemy * createAsteroid();
	static Enemy * createMine();
	static Enemy * createCrazyMine();
	static Enemy * createAlien();
};


#endif
