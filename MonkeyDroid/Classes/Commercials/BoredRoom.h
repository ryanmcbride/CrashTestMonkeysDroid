//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __BORED_ROOM_H__
#define __BORED_ROOM_H__

// When you import this file, you import all the cocos2d classes
#include "Commercial.h"


class BoredRoom : public Commercial
{
public:
    virtual ~BoredRoom();
    BoredRoom();
    virtual void update(float dt);
protected:
    void blinkTick(float dt);
    void punchTick(float dt);
    void headBobbleTick(float dt);
    void fartTick(float dt);

    cocos2d::CCSprite *eyes[2];
    cocos2d::CCSprite *arms[6];
    cocos2d::CCSprite *geoff[6];
    cocos2d::CCSprite *geoffHead[7];
    bool isSlap;
    float blinkTime;
    int blinkState;
    
    float punchTime;
    int punchState;
    
    float headBobbleTime;
    int headBobbleState;
    
    bool isFart;
    float fartTime;
    int fartState;
    cocos2d::CCSprite *geoffFart[2];
};

#endif // __BORED_ROOM_H__
