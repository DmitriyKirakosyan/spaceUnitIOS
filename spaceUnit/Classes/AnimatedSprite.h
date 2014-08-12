//
//  AnimatedSprite.h
//  spaceUnit
//
//  Created by PC on 8/9/14.
//
//

#ifndef spaceUnit_AnimatedSprite_h
#define spaceUnit_AnimatedSprite_h

#include <vector>

class AnimatedSprite {
private:
    float _startTime;
    float _maxStateTime;
    float _frameDuration;
    cocos2d::CCArray *animArray;
    bool isFinished;
    
public:
    AnimatedSprite(cocos2d::CCArray *pArray, float frameDuration) {
        animArray = pArray;
        _startTime = 0;
        _maxStateTime = frameDuration * pArray->count();
        _frameDuration = frameDuration;
        isFinished = false;
    }
    
    void tick(float dt) {
        _startTime += dt;
        if(_startTime >= _maxStateTime) {
            _startTime = 0;
            isFinished = true;
        }
    }
    
    cocos2d::CCSpriteFrame * getCurrentSkin() {
        int n = (int)(_startTime / _frameDuration);
        if(_startTime >= _maxStateTime) {
            n = 0;
        }
        
        return (cocos2d::CCSpriteFrame *)animArray->objectAtIndex(n);
    }
    
    void setStartTime(float startTime) {
        _startTime = startTime;
    }
    
    bool isAnimationFinished() {
        return isFinished;
    }
    
    void release() {
        delete animArray;
        delete this;
    }
};

#endif
