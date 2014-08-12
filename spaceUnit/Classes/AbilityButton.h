//
//  AbilityButton.h
//  spaceUnit
//
//  Created by PC on 8/11/14.
//
//

#ifndef __spaceUnit__AbilityButton__
#define __spaceUnit__AbilityButton__

#include "cocos2d.h"
#include "Ability.h"
class AbilityButton : public cocos2d::CCNode {
private:
    const char * _bkg;
	const char * _view;
	Ability *_ability;
	float _highlightTimeLeft;
	float _highlightTotalTime;
	bool _highlightFlag;
public:
    cocos2d::CCSprite *_panelSprite;
    cocos2d::CCSprite *_viewSprite;
    cocos2d::CCSprite *_bkgSprite;
public:
    AbilityButton(Ability *ability);
    
	const char * getView() { return _view; }
    
	void tick(float delta);
    
	bool isReady() { return _ability->isReady(); }
};


#endif /* defined(__spaceUnit__AbilityButton__) */
