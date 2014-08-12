//
//  Button.h
//  spaceUnit
//
//  Created by PC on 8/11/14.
//
//

#ifndef __spaceUnit__Button__
#define __spaceUnit__Button__

#include "cocos2d.h"

class Button : public cocos2d::CCSprite{

protected:
    const char *_normal;
    const char *_clicked;
    const char *_currentView;
    float _width;
    float _height;
    float _scale;

public:
    int index = -1;

public:
    Button(const char * normal, const char * clicked) {
        _normal = normal;
        _clicked = clicked;
        _currentView = _normal;
        this->initWithFile(_normal);
    }

    const char * getView();
    float getWidth();
    float getHeight();

    bool isClicked();

    void setClickedMode();
    void setNormalMode();
};

#endif /* defined(__spaceUnit__Button__) */
