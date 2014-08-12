//
//  CCLabelChange.cpp
//  testLabelChange
//
//  Created by chenquanjun on 14-1-23.
//
//

#include "CCLabelChange.h"

CCLabelChange::CCLabelChange():
m_nFromNum(0),
m_nToNum(0)
{
    
}

CCLabelChange* CCLabelChange::create(float duration, int fromNum, int toNum)
{
    CCLabelChange *pRet = new CCLabelChange();
    pRet->initWithDuration(duration, fromNum, toNum);
    pRet->autorelease();
    
    return pRet;
}

bool CCLabelChange::initWithDuration(float duration, int fromNum, int toNum)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_nFromNum = fromNum;
        m_nToNum = toNum;
        return true;
    }
    
    return false;
}

CCObject* CCLabelChange::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCLabelChange* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCLabelChange*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCLabelChange();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, m_nFromNum, m_nToNum);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCLabelChange::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        CCString *numStr = CCString::createWithFormat("%i", m_nFromNum);
        pLabel->setString(numStr->getCString());
    }
    
}

CCActionInterval* CCLabelChange::reverse(void)
{
    return CCLabelChange::create(m_fDuration, m_nToNum, m_nFromNum);
}


void CCLabelChange::update(float t)
{
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        //fix bug
        int tempNum = (m_nToNum - m_nFromNum) * t;
        int num = m_nFromNum + tempNum;
        CCString *numStr = CCString::createWithFormat("%i", num);
        pLabel->setString(numStr->getCString());
    }
    
}


#pragma -mark- hp label change

CCHPLabelChange::CCHPLabelChange():
m_nFromNum(0),
m_nToNum(0),
m_nFullHp(0)
{
    
}

CCHPLabelChange* CCHPLabelChange::create(float duration, int fromNum, int toNum, int fullHp)
{
    CCHPLabelChange *pRet = new CCHPLabelChange();
    pRet->initWithDuration(duration, fromNum, toNum, fullHp);
    pRet->autorelease();
    
    return pRet;
}

bool CCHPLabelChange::initWithDuration(float duration, int fromNum, int toNum, int fullHp)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_nFromNum = fromNum;
        m_nToNum = toNum;
        m_nFullHp = fullHp;
        return true;
    }
    
    return false;
}

CCObject* CCHPLabelChange::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCHPLabelChange* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCHPLabelChange*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCHPLabelChange();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration, m_nFromNum, m_nToNum, m_nFullHp);
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCHPLabelChange::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        CCString *numStr = CCString::createWithFormat("%i / %i", m_nFromNum, m_nFullHp);
        pLabel->setString(numStr->getCString());
    }
    
}

CCActionInterval* CCHPLabelChange::reverse(void)
{
    return CCHPLabelChange::create(m_fDuration, m_nToNum, m_nFromNum, m_nFullHp);
}


void CCHPLabelChange::update(float t)
{
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        int tempNum = (m_nToNum - m_nFromNum) * t;
        int num = m_nFromNum + tempNum;
        CCString *numStr = CCString::createWithFormat("%i / %i", num, m_nFullHp);
        pLabel->setString(numStr->getCString());
    }
    
}


#pragma -mark-  label change fade in

CCLabelFadeIn::CCLabelFadeIn():
m_labelStr(""),
_wordPosArr(NULL)
{
    
}

CCLabelFadeIn::~CCLabelFadeIn(){
    CC_SAFE_RELEASE(_wordPosArr);
}

CCLabelFadeIn* CCLabelFadeIn::create(float duration, const char* labelStr)
{
    CCLabelFadeIn *pRet = new CCLabelFadeIn();
    pRet->initWithDuration(duration, labelStr);
    pRet->autorelease();
    
    return pRet;
}

bool CCLabelFadeIn::initWithDuration(float duration, const char* labelStr)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_labelStr = labelStr;
        
        this->figureStr();
        return true;
    }
    
    return false;
}

CCObject* CCLabelFadeIn::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCLabelFadeIn* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCLabelFadeIn*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCLabelFadeIn();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration,m_labelStr.c_str());
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCLabelFadeIn::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        //        CCString *numStr = CCString::createWithFormat("%i", m_nFromNum);
        //        pLabel->setString(numStr->getCString());
    }else{
        //继承CCLabelProtocol的才能使用
        CCLog("Warning: not CCLabel Type, this action won't work");
    }
    
}

CCActionInterval* CCLabelFadeIn::reverse(void)
{
    return CCLabelFadeIn::create(m_fDuration, m_labelStr.c_str());
}

void CCLabelFadeIn::figureStr(){
//    Unicode符号范围 | UTF-8编码方式
//    (十六进制) | （二进制）
//    --------------------+---------------------------------------------
//    0000 0000-0000 007F | 0xxxxxxx
//    0000 0080-0000 07FF | 110xxxxx 10xxxxxx
//    0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
//    0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    
    //2dx引擎的字符使用 UTF-8编码方式
    
    setWordPosArr(CCArray::create());
    
    int count = m_labelStr.length();
    
    int pos = 0;
    
    while (1) {
        char utf8Head = m_labelStr[pos];
        
        int offset = 0;
        
        if ((utf8Head & 0x80) == 0x00) {
            //1个字节 与 10000000 = 00000000
            offset = 1;
        }else if ((utf8Head & 0xe0) == 0xc0){
            offset = 2;
            //2个字节 与 11100000 = 11000000
        }else if ((utf8Head & 0xf0) == 0xe0){
            offset = 3;
            //3个字节 与 11110000 = 11100000
        }else if ((utf8Head & 0xf8) == 0xf0){
            offset = 4;
            //4个字节 与 11111000 = 11110000
        }
        
        CCInteger *pOffset = CCInteger::create(offset);
        _wordPosArr->addObject(pOffset);
        
        pos += offset;
        if (pos == count || count == 0) {
            break;
        }
    }
    
    
    m_nTotalNum = _wordPosArr->count();
    
    CCInteger *pOffset = (CCInteger*)_wordPosArr->objectAtIndex(0);
    
    m_nCurrentOffset = pOffset->getValue();
    
    //第一个index直接赋值
    m_currentStr.append(m_labelStr.c_str(), m_nCurrentOffset);
    
    m_nCurrentIndex = 1;

}

void CCLabelFadeIn::update(float t)
{
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        int index = t * m_nTotalNum;
        
        if (index <= m_nCurrentIndex) {
            return;
        }
        
        int totalOffset = 0;
        
        //因为根据t来计算index，所以可能跳过几个index，此处用循环累计offset
        for (int i = m_nCurrentIndex; i < index; i++) {
            CCInteger *pOffset = (CCInteger*)_wordPosArr->objectAtIndex(i);
            
            totalOffset += pOffset->getValue();
        }
        
        m_currentStr.append(m_labelStr, m_nCurrentOffset, totalOffset);
        
        pLabel->setString(m_currentStr.c_str());
        
        m_nCurrentIndex = index;
        
        m_nCurrentOffset += totalOffset;
    }
    
}

#pragma -mark-  label change fade out

CCLabelFadeOut::CCLabelFadeOut():
m_labelStr(""),
_wordPosArr(NULL)
{
    
}

CCLabelFadeOut::~CCLabelFadeOut(){
    CC_SAFE_RELEASE(_wordPosArr);
}

CCLabelFadeOut* CCLabelFadeOut::create(float duration, const char* labelStr)
{
    CCLabelFadeOut *pRet = new CCLabelFadeOut();
    pRet->initWithDuration(duration, labelStr);
    pRet->autorelease();
    
    return pRet;
}

bool CCLabelFadeOut::initWithDuration(float duration, const char* labelStr)
{
    if (CCActionInterval::initWithDuration(duration))
    {
        m_labelStr = labelStr;
        
        this->figureStr();
        return true;
    }
    
    return false;
}

CCObject* CCLabelFadeOut::copyWithZone(CCZone *pZone)
{
    CCZone* pNewZone = NULL;
    CCLabelFadeOut* pCopy = NULL;
    if(pZone && pZone->m_pCopyObject)
    {
        //in case of being called at sub class
        pCopy = (CCLabelFadeOut*)(pZone->m_pCopyObject);
    }
    else
    {
        pCopy = new CCLabelFadeOut();
        pZone = pNewZone = new CCZone(pCopy);
    }
    
    CCActionInterval::copyWithZone(pZone);
    
    pCopy->initWithDuration(m_fDuration,m_labelStr.c_str());
    
    CC_SAFE_DELETE(pNewZone);
    return pCopy;
}

void CCLabelFadeOut::startWithTarget(CCNode *pTarget)
{
    CCActionInterval::startWithTarget(pTarget);
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        //        CCString *numStr = CCString::createWithFormat("%i", m_nFromNum);
        pLabel->setString(m_labelStr.c_str());
    }else{
        //继承CCLabelProtocol的才能使用
        CCLog("Warning: not CCLabel Type, this action won't work");
    }
    
}

CCActionInterval* CCLabelFadeOut::reverse(void)
{
    return CCLabelFadeOut::create(m_fDuration, m_labelStr.c_str());
}

void CCLabelFadeOut::figureStr(){
    //    Unicode符号范围 | UTF-8编码方式
    //    (十六进制) | （二进制）
    //    --------------------+---------------------------------------------
    //    0000 0000-0000 007F | 0xxxxxxx
    //    0000 0080-0000 07FF | 110xxxxx 10xxxxxx
    //    0000 0800-0000 FFFF | 1110xxxx 10xxxxxx 10xxxxxx
    //    0001 0000-0010 FFFF | 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
    
    //2dx引擎的字符使用 UTF-8编码方式
    
    setWordPosArr(CCArray::create());
    
    int count = m_labelStr.length();
    
    int pos = 0;
    
    while (1) {
        char utf8Head = m_labelStr[pos];
        
        int offset = 0;
        
        if ((utf8Head & 0x80) == 0x00) {
            //1个字节 与 10000000 = 00000000
            offset = 1;
        }else if ((utf8Head & 0xe0) == 0xc0){
            offset = 2;
            //2个字节 与 11100000 = 11000000
        }else if ((utf8Head & 0xf0) == 0xe0){
            offset = 3;
            //3个字节 与 11110000 = 11100000
        }else if ((utf8Head & 0xf8) == 0xf0){
            offset = 4;
            //4个字节 与 11111000 = 11110000
        }
        
        CCInteger *pOffset = CCInteger::create(offset);
        _wordPosArr->addObject(pOffset);
        
        pos += offset;
        if (pos == count || count == 0) {
            break;
        }
    }
    
    
    m_nTotalNum = _wordPosArr->count();
    
    CCInteger *pOffset = (CCInteger*)_wordPosArr->objectAtIndex(0);
    
    m_nCurrentOffset = pOffset->getValue();
    
    //第一个index直接赋值
    m_currentStr.append(m_labelStr.c_str(), m_nCurrentOffset);
    
    m_nCurrentIndex = 1;
    
}

void CCLabelFadeOut::update(float t)
{
    
    CCLabelProtocol *pLabel = dynamic_cast<CCLabelProtocol*>(m_pTarget);
    if (pLabel)
    {
        int index = t * m_nTotalNum;
        
        if (index <= m_nCurrentIndex) {
            return;
        }
        
        int totalOffset = 0;
        
        //因为根据t来计算index，所以可能跳过几个index，此处用循环累计offset
        for (int i = m_nCurrentIndex; i < index; i++) {
            CCInteger *pOffset = (CCInteger*)_wordPosArr->objectAtIndex(i);
            
            totalOffset += pOffset->getValue();
        }
        
        m_currentStr.append(m_labelStr, m_nCurrentOffset, totalOffset);
        
        pLabel->setString(m_currentStr.c_str());
        
        m_nCurrentIndex = index;
        
        m_nCurrentOffset += totalOffset;
    }
    
}