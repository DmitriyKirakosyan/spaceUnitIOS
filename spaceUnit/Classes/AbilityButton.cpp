//
//  AbilityButton.cpp
//  spaceUnit
//
//  Created by PC on 8/11/14.
//
//

#include "AbilityButton.h"
#include "Assets.h"

AbilityButton::AbilityButton(Ability *ability) {
    _highlightFlag = false;
    _highlightTotalTime = 0.4f;
    _highlightTimeLeft = _highlightTotalTime;
    _bkg = Assets::abilBkg;
    
    if (ability->getType() == BLOW) {
        _view = Assets::blowAbil;
    } else if (ability->getType() == MULTIGUN) {
        _view = Assets::superShipAbil;
    } else {
     //   throw new Error("unknown ability : " + ability.toString());
    }
    _ability = ability;
    
    _panelSprite = cocos2d::CCSprite::create(Assets::abilPanel);
    this->addChild(_panelSprite);
    
    _bkgSprite = cocos2d::CCSprite::create(_bkg);
    _bkgSprite->setOpacity(0);
    this->addChild(_bkgSprite);
    
    _viewSprite = cocos2d::CCSprite::create(_view);
    this->addChild(_viewSprite);
}

void AbilityButton::tick(float delta) {
    float opacity;
    float alpha = (_ability->getCooldown() - _ability->timeToReady()) / _ability->getCooldown();
    if (alpha != 1) {
        opacity = 255 * alpha;
    } else {
        if (_highlightFlag) {
            opacity = 255;
        } else {
            opacity = 0;
        }
        
        _highlightTimeLeft -= delta;
        if (_highlightTimeLeft <= 0) {
            _highlightFlag = !_highlightFlag;
            _highlightTimeLeft = _highlightTotalTime;
        }
    }
    _bkgSprite->setOpacity(opacity);
}