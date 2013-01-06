//
//  MovingSpaceObject.cpp
//  spaceUnit
//
//  Created by Dmitriy on 1/2/13.
//
//

#include "MovingSpaceObject.h"

using namespace cocos2d;


void MovingSpaceObject::moveTo(float targetX, float targetY)
{
    CCPoint position = this->getPosition();
    
    float dx = targetX - position.x;
    float dy = targetY - position.y;
    float h = sqrt(dx * dx + dy * dy);
    float vx = 0;
    float vy = 0;
    if (h != 0){
        vx = dx / h * _generalSpeed;
        vy = dy / h * _generalSpeed;
    }
    this->setPosition(ccp(position.x + vx, position.y + vy));
}

void MovingSpaceObject::rotateTo(float targetX, float targetY)
{
    float dx = this->getPosition().x - targetX;
    float dy = this->getPosition().y - targetY;
    float angle = 180 + atan2f(dy, dx) * 180 / 3.14;
    this->setRotation(-angle);
}

void MovingSpaceObject::setRandomGeneralSpeed()
{
    _generalSpeed = 2. * (arc4random() % 100) / 100.;
}

void MovingSpaceObject::setGeneralSpeed(float value)
{
    _generalSpeed = value;
}
