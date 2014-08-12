//
//  MovingSpaceObject.h
//  spaceUnit
//
//  Created by Dmitriy on 1/2/13.
//
//

#ifndef __spaceUnit__MovingSpaceObject__
#define __spaceUnit__MovingSpaceObject__

#include "SpaceObject.h"
#include "BorderBehaviorENUM.h"

class MovingSpaceObject : public SpaceObject
{

private:
    int _borderBehaviour;
    
protected:
    float _generalSpeed;
    float _vX;
	float _vY;
	float _frozenVX;
	float _frozenVY;
	float _rotationSpeed;

    bool _paused;

public:
    MovingSpaceObject(cocos2d::CCSize screenSize, const char *imageFile, bool randomScale, int borderBehaviour)
    : SpaceObject(screenSize, imageFile, randomScale) {
		_borderBehaviour = borderBehaviour;
		_generalSpeed = 0;
		_rotationSpeed = 0;
		this->setVelocity(0, 0);
		_paused = false;
	}
    
    MovingSpaceObject(cocos2d::CCSize screenSize, const char *imageFile)
    :SpaceObject(screenSize, imageFile, false) {
        _borderBehaviour = NONE;
		_generalSpeed = 0;
		_rotationSpeed = 0;
		//this.setVelocity(0, 0);
		_paused = false;
    }
    
    void moveTo(float targetX, float targetY) {
        cocos2d::CCPoint position = this->getPosition();
         
         float dx = targetX - position.x;
         float dy = targetY - position.y;
         float h = sqrt(dx * dx + dy * dy);
         float vx = 0;
         float vy = 0;
         if (h != 0){
         vx = dx / h * _generalSpeed;
         vy = dy / h * _generalSpeed;
         }
        this->setVelocity(vx, vy);

    }
    
    void setVelocity(float vx, float vy) {
		_vX = vx;
		_vY = vy;
		_frozenVX = vx;
		_frozenVY = vy;
	}
    
    void rotateTo(float targetX, float targetY) {
        float dx = this->getPosition().x - targetX;
        float dy = this->getPosition().y - targetY;
        float angle = 180 + atan2f(dy, dx) * 180 / 3.14;
        //this->setRotation(-angle);
        _rotation = -angle;
    }
    
    void stopMoving()
	{
		_vX = 0;
		_vY = 0;
	}
    
	void resumeMoving() {
		_vX = _frozenVX;
		_vY = _frozenVY;
	}
    
    void tick(float dt) {
        float FRAME_TIME = 1 / 60.0f;
        float coef = dt / FRAME_TIME;
        
        SpaceObject::tick(dt);
		if (_isDead) { return; }
		if (_paused) { return; }
        
		float newX = this->getPosition().x + _vX * coef;
		float newY = this->getPosition().y + _vY * coef;
        
		if (_borderBehaviour == STOP) {
			if (newX + this->getContentSize().width / 2 < _screenSize.width && newX - this->getContentSize().width / 2 > 0)
				_position.x = newX;
			if (newY + this->getContentSize().height / 2 < _screenSize.height && newY - this->getContentSize().height / 2 > 0)
				_position.y = newY;
		}
		else {
			_position.x = newX;
			_position.y = newY;
		}
		_rotation+= _rotationSpeed * coef;
		if (_rotation > 360) { _rotation = (int)_rotation % 360; }
		
		if (_borderBehaviour == TELEPORT) {
			if (this->checkBorderHit())
			{
				this->setRandomBorderPosition();
                return;
			}
		}
        
		this->setPosition(ccp(_position.x, _position.y));
		this->setRotation(_rotation);
        
	}
    
    bool checkBorderHit() {
        cocos2d::CCPoint position = this->getPosition();
        if ((position.x + this->getContentSize().width < 0) ||
            (position.x - this->getContentSize().width/2 > _screenSize.width) ||
            (position.y + this->getContentSize().height/2 < 0) ||
            (position.y - this->getContentSize().height/2 > _screenSize.height)) {
            return true;
        } else {
            return false;
        }
    }
    
    void setRandomBorderPosition()
    {
        int randomInt;
        float randomX, randomY;
        
        if (arc4random() % 2 == 1)
        {
            randomInt = arc4random() % (int)(_screenSize.width * 2 - 1);
            randomX = (int) (randomInt / _screenSize.width) * _screenSize.width;
            randomY = arc4random() % (int)_screenSize.height;
        }
        else
        {
            randomX = arc4random() % (int)_screenSize.width;
            randomInt = arc4random() % (int)(_screenSize.height * 2 - 1);
            randomY = (int) (randomInt / _screenSize.height) * _screenSize.height;
        }
        if (randomX == 0) { randomX = -this->getContentSize().width/2; }
        if (randomX == _screenSize.width) { randomX += this->getContentSize().width/2; }
        if (randomY == 0) { randomY = -this->getContentSize().height/2; }
        if (randomY == _screenSize.height) { randomY += this->getContentSize().height/2; }
        
        this->setPosition(ccp(randomX, randomY));
    }
    
    void setRandomGeneralSpeed()
    {
        _generalSpeed = 2. * (arc4random() % 100) / 100.0f;
    }
    
    void setGeneralSpeed(float value)
    {
        _generalSpeed = value;
    }
    
    void setRotationSpeed(float value) { _rotationSpeed = value; }
    float getRotationSpeed() { return _rotationSpeed; }
    
    bool isMoving() { return _vX != 0 || _vY != 0; }
};

#endif /* defined(__spaceUnit__MovingSpaceObject__) */
