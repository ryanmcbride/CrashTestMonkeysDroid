//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __FINISH_OVERLAY_H__
#define __FINISH_OVERLAY_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class FinishOverlay : public cocos2d::CCLayer
{
public:
    virtual ~FinishOverlay();
    FinishOverlay();
    FinishOverlay(float time, int peanuts, int points);
    
    static cocos2d::CCLayer* createFinish(float time, int peanuts, int points);
    
    // returns a Scene that contains the HelloWorld as the only child
    void restartButtonTapped(CCObject*object);
    void levelSelectButtonTapped(CCObject*object);
    void nextLevelButtonTapped(CCObject*object);
    void storeButtonTapped(CCObject*object);
    
    virtual void SocialBar(float startTime);
    virtual void NavBar(float startTime);
    virtual void Store(float startTime);
    virtual void ChimpHead(float startTime);
    virtual void Score(float startTime);
    virtual bool Medal(float startTime);
    
    void PlaySound1(CCNode * node);
    void PlaySound2(CCNode * node);
    void PlaySoundGold(CCNode * node);
    void PlaySoundSilver(CCNode * node);
    void PlaySoundBronze(CCNode * node);
protected:
    bool DoFinalTrainingMessage(float startTime);
    virtual bool canDoNextLevel(int levelNum);
    float m_time;
    int m_peanuts;
    int m_points;
    bool m_EarningMedal;
    virtual void ScreenInit(float time, int peanuts, int points);
};

#endif // __FINISH_OVERLAY_H__
