//
//  ScoreView.h
//  spaceUnit
//
//  Created by PC on 8/8/14.
//
//

#ifndef spaceUnit_ScoreView_h
#define spaceUnit_ScoreView_h

#include "cocos2d.h"
#include "Assets.h"

using namespace cocos2d;

class ScoreView : public cocos2d::CCSprite {
private:
    const char* SCORE_TEXT = "Score :";
	const float MAGIC_OFFSET = 15;
	char * _score;
	int _scoreType;
    CCLabelTTF *scoreLabel;
    
public:
    
    ScoreView(char * score){
        _score = score;
		initElements();
    }
    
	ScoreView() {
        _score = (char *)"0";
		initElements();
	}
    
    
    void initElements() {
        this->initWithFile(Assets::scorePad);
        
        cocos2d::CCLabelTTF *label = cocos2d::CCLabelTTF::create("Score:", "Calibri", 33, CCSizeMake(150, this->getContentSize().height), kCCTextAlignmentLeft, kCCVerticalTextAlignmentCenter);
        label->setAnchorPoint(ccp(0, 0));
        label->setColor(cocos2d::ccc3(255, 0, 0));
        label->setPosition(ccp(40, 0));
        this->addChild(label);
        
        scoreLabel = cocos2d::CCLabelTTF::create("14:00:00", "Calibri", 30, CCSizeMake(200, this->getContentSize().height), kCCTextAlignmentCenter, kCCVerticalTextAlignmentCenter);
        scoreLabel->setAnchorPoint(ccp(1, 1));
        scoreLabel->setColor(cocos2d::ccc3(255, 0, 0));
        scoreLabel->setPosition(ccp(this->getContentSize().width, this->getContentSize().height));
        this->addChild(scoreLabel);
        
        scoreLabel->setString(_score);
    }
    
	void setScoreType(int scoreType) {
		_scoreType = scoreType;
	}
    
	void setScore(char * scoreValue) {
		_score = scoreValue;
        scoreLabel->setString(_score);
	}
    
	/*void draw() {
		super.draw(spriteBatch);
		BitmapFont font = FontProvider.getFont();
		Color prevColor = font.getColor();
		font.setColor(Color.RED);
		BitmapFont.TextBounds bounds = font.getBounds(SCORE_TEXT);
		float x = super.getX() + super.getWidth()/4 - bounds.width/2;
		float y = super.getY() + (getHeight() + bounds.height)/2;
		font.draw(spriteBatch, SCORE_TEXT, x, y);
        
		bounds = font.getBounds(_score);
		if (_scoreType == Score.SECONDS) {
			x = super.getX() + super.getWidth() / 2 + MAGIC_OFFSET;
		} else {
			x = super.getX() + super.getWidth() / 4 * 3 - bounds.width/2;
		}
        
		font.draw(spriteBatch, _score, x, y);
        
		font.setColor(prevColor);
    }*/
};

#endif
