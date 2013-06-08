//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __HUD_H__
#define __HUD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"
#include "../Level/Rider/Rider.h"

class HUD : public cocos2d::CCLayer
{
public:
    virtual ~HUD();
    HUD();
    
    // returns a Scene that contains the HelloWorld as the only child
    void pauseButtonTapped(CCObject*object);
    void fwdButtonTapped(CCObject*object);
    void backButtonTapped(CCObject*object);
    void jumpButtonTapped(CCObject*object);
    
    virtual void didAccelerate(cocos2d::CCAcceleration* pAccelerationValue);
    
    void SetRider(Rider* rider){m_Rider = rider;}
    
    void finishButtonTapped(CCObject*object);
    void crashButtonTapped(CCObject*object);
    
    void update(float dt);
    void startCrashSequence();
    void startFinishSequence();
protected:
    friend class Pause;
    float m_fTrickButtonDelay;
    Rider *m_Rider;
    cocos2d::CCMenuItem *m_ForwardButton;
    cocos2d::CCMenuItem *m_BackwardButton;
    cocos2d::CCMenuItem *m_JumpButton;
    bool m_bIsInFinishSequence;
    
    cocos2d::CCLabelBMFont *m_TimeString;
    cocos2d::CCLabelBMFont *m_PointString;
    cocos2d::CCLabelBMFont *m_PeanutString;
    float m_Time;
    
    cocos2d::CCNode *m_startPrompt;
};

#endif // __PAUSE_H__
