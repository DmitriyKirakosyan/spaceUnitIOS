//
//  AEnemyBehaviour.h
//  spaceUnit
//
//  Created by PC on 8/7/14.
//
//

#ifndef __spaceUnit__AEnemyBehaviour__
#define __spaceUnit__AEnemyBehaviour__

#include <iostream>
#include "EBehaviourENUM.h"
#include "BehaviourOptions.h"
//#include "Enemy.h"

class Enemy;
class AEnemyBehaviour {

private:
    int _behaviourName;

protected:
    Enemy *_enemy;
    bool _actual;
    BehaviourOptions *_options;
    
public:
    AEnemyBehaviour(int behaviourName, Enemy *enemy, BehaviourOptions *options) {
        _enemy = enemy;
        _behaviourName = behaviourName;
        _options = options;
    }
    
    AEnemyBehaviour(int behaviourName, Enemy *enemy) {
        _enemy = enemy;
        _behaviourName = behaviourName;
        _options = NULL;
    }
    
    int getName() { return _behaviourName; }
    
    virtual void start() { _actual = true; }
    virtual void stop() { _actual = false; }
    bool isActual() { return _actual; }
    
    virtual void tick(float delta) = 0;
};

#endif /* defined(__spaceUnit__AEnemyBehaviour__) */
