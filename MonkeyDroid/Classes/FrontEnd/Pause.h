//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __PAUSE_H__
#define __PAUSE_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class Pause : public cocos2d::CCLayer
{
public:
    virtual ~Pause();
    Pause();
    
    // returns a Scene that contains the HelloWorld as the only child
    static void BeginPause(cocos2d::CCNode *hudNode);
    static void EndPause();
    static bool s_bIsPaused;
    void backButtonTapped(CCObject*object);
    void resetButtonTapped(CCObject*object);
    void levelButtonTapped(CCObject*object);
protected:
    cocos2d::CCNode *m_HUD;
    void PauseEndAnim();
    static Pause *s_pPauseMenu;
};

#endif // __PAUSE_H__
