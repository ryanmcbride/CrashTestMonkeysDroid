//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __CNN_H__
#define __CNN_H__

// When you import this file, you import all the cocos2d classes
#include "Commercial.h"


class CNN : public Commercial
{
public:
    virtual ~CNN();
    CNN();
    virtual void update(float dt);
protected:
    cocos2d::CCSprite *mouthSprite;
    int mouthIndex;
    float mouthIndexTime;
    float talkTime;
    bool bMouthAudio;
    unsigned int m_mouthAudio;
};

#endif // __HELLO_WORLD_H__
