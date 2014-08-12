//
//  CCLabelChange.h
//  testLabelChange
//
//  Created by chenquanjun on 14-1-23.
//
//

#ifndef __testLabelChange__CCLabelChange__
#define __testLabelChange__CCLabelChange__

#include "cocos2d.h"
USING_NS_CC;
#pragma -mark- CCLabelChange
//数字变化效果
class CCLabelChange : public CCActionInterval
{
public:
    CCLabelChange();
    
public:
    //数字变化 使用对象CCLabelTTF
    
    /** creates the action */
    static CCLabelChange* create(float duration, int fromNum, int toNum);
    
    /** initializes the action */
    bool initWithDuration(float duration, int fromNum, int toNum);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void update(float time);
    
protected:
    
    int m_nFromNum;
    int m_nToNum;
};

#pragma -mark- CCHPLabelChange
//数字变化效果（hp）
class CCHPLabelChange : public CCActionInterval
{
public:
    CCHPLabelChange();
    
public:
    //数字变化 使用对象CCLabelTTF
    
    /** creates the action */
    static CCHPLabelChange* create(float duration, int fromNum, int toNum, int fullHp);
    
    /** initializes the action */
    bool initWithDuration(float duration, int fromNum, int toNum, int fullHp);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void update(float time);
    
protected:
    
    int m_nFromNum;
    int m_nToNum;
    int m_nFullHp;
};

#pragma -mark- CCLabelFadeIn
//文字淡入效果
class CCLabelFadeIn : public CCActionInterval
{
private:
    CCLabelFadeIn();
    
    ~CCLabelFadeIn();
    
public:
    /** creates the action */
    static CCLabelFadeIn* create(float duration, const char* labelStr);
    
    /** initializes the action */
    bool initWithDuration(float duration, const char* labelStr);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void update(float time);
    
private:
    void figureStr();
    
protected:
    
    std::string m_labelStr;
    
private:
    int m_nTotalNum;
    
    int m_nCurrentIndex;
    
    int m_nCurrentOffset;
    
    std::string m_currentStr;
    
    //保存偏移大小的
    CC_SYNTHESIZE_RETAIN(CCArray*, _wordPosArr, WordPosArr);
};


#pragma -mark- CCLabelFadeOut
//文字淡入效果
class CCLabelFadeOut : public CCActionInterval
{
private:
    CCLabelFadeOut();
    
    ~CCLabelFadeOut();
    
public:
    /** creates the action */
    static CCLabelFadeOut* create(float duration, const char* labelStr);
    
    /** initializes the action */
    bool initWithDuration(float duration, const char* labelStr);
    
    virtual CCObject* copyWithZone(CCZone* pZone);
    virtual void startWithTarget(CCNode *pTarget);
    virtual CCActionInterval* reverse(void);
    virtual void update(float time);
    
private:
    void figureStr();
    
protected:
    
    std::string m_labelStr;
    
private:
    int m_nTotalNum;
    
    int m_nCurrentIndex;
    
    int m_nCurrentOffset;
    
    std::string m_currentStr;
    
    //保存偏移大小的
    CC_SYNTHESIZE_RETAIN(CCArray*, _wordPosArr, WordPosArr);
};



#endif /* defined(__testLabelChange__CCLabelChange__) */
