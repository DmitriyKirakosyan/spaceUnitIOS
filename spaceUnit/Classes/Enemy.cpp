//
//  Enemy.cpp
//  spaceUnit
//
//  Created by Dmitriy on 12/29/12.
//
//
/*
#include "Enemy.h"

using namespace cocos2d;




Enemy::Enemy(CCSize screenSize, bool teleportOnBoarder):MovingSpaceObject(screenSize, true)
{
    _teleportOnBoarder = teleportOnBoarder;
    _speedRotate = 0;
    _speedX = 0;
    _speedY = 0;
}

void Enemy::simpleMove()
{
    CCPoint position = this->getPosition();
    position.x += _speedX;
    position.y += _speedY;
    this->setPosition(position);
    
    this->setRotation(this->getRotation() + _speedRotate);
    if (_teleportOnBoarder) {
        this->checkBoarderTeleport();
    }
}

void Enemy::setRandomLook()
{
    this->initWithFile(dynamicImgs[	() % getSizeImgArray()]);
}

void Enemy::setRandomBehaviour()
{
    float speedX = (arc4random() % 20) / 10.0 - 1;
    float speedY = (arc4random() % 20) / 10.0 - 1;
    
    this->setSpeedX(speedX);
    this->setSpeedY(speedY);
    this->setSpeedRotate(((arc4random() % 100) / 100.0f) * 10);
}



void Enemy::checkBoarderTeleport()
{
    CCPoint position = this->getPosition();
    if ((position.x + this->getContentSize().width < 0) ||
        (position.x - this->getContentSize().width/2 > _screenSize.width) ||
        (position.y + this->getContentSize().height/2 < 0) ||
        (position.y - this->getContentSize().height/2 > _screenSize.height))
    {
        this->setRandomBorderPosition();
    }
}

void Enemy::removeAllBehaviours() {
    
}*/