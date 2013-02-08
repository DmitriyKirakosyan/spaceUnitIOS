//
//  Bullet.h
//  spaceUnit
//
//  Created by Dmitriy on 2/8/13.
//
//

#ifndef spaceUnit_Bullet_h
#define spaceUnit_Bullet_h

#include "cocos2d.h"

class Bullet : public cocos2d::CCSprite
{
public:
    Bullet(float speed, float xCoef, float yCoef)
    {
        _speed = speed;
        _xCoef = xCoef;
        _yCoef = yCoef;
    }
    
    void move()
    {
        cocos2d::CCPoint position = this->getPosition();
        position.x += _speed * _xCoef;
        position.y += _speed * _yCoef;
        this->setPosition(position);
    }
    
private:
    float _speed;
    float _xCoef;
    float _yCoef;
};

#endif
