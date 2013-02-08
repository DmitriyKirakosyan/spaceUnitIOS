//
//  Ship.cpp
//  spaceUnit
//
//  Created by Dmitriy on 1/2/13.
//
//

#include "Ship.h"

using namespace cocos2d;

Ship::Ship(CCSize screenSize, int reloadTime):MovingSpaceObject(screenSize, false)
{
    _reloadTime = reloadTime;
    _currentReloadTime = 0;
    _readyForShoot = false;
    _targetPosition = cocos2d::CCPointZero;
    _targetForShooting = cocos2d::CCPointZero;
    _moving = false;
    _shooting = false;
    this->initWithFile("ShipView.png");
    this->setScale(1.0f);
}


void Ship::tick()
{
    _readyForShoot = false;
    if (_moving)
    {
        this->moveTo(_targetPosition.x, _targetPosition.y);
        this->rotateTo(_targetPosition.x, _targetPosition.y);
    }
    
    if (_shooting)
    {
        if (_currentReloadTime>= _reloadTime)
        {
            _readyForShoot = true;
            _currentReloadTime = 0;
        }
        else
        {
            _currentReloadTime++;
        }
    }
}