//
//  Button.cpp
//  spaceUnit
//
//  Created by PC on 8/11/14.
//
//

#include "Button.h"
#include "SimpleAudioEngine.h"


const char * Button::getView() {
    return _currentView;
}

float Button::getWidth() {
    return this->getContentSize().width * this->getScale();
}

float Button::getHeight() {
    return this->getContentSize().height * this->getScale();
}


bool Button::isClicked() {
    return _currentView == _clicked;
}

void Button::setClickedMode() {
    if (_currentView == _clicked) return;
    _currentView = _clicked;
    this->initWithFile(_clicked);
    this->setAnchorPoint(ccp(1, 1));
    CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("click.mp3");
}

void Button::setNormalMode()
{
    if (_currentView == _normal) return;
    _currentView = _normal;
    this->initWithFile(_normal);
    this->setAnchorPoint(ccp(1, 1));
}
