//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __CRASH_OVERLAY_H__
#define __CRASH_OVERLAY_H__

// When you import this file, you import all the cocos2d classes
#include "FinishOverlay.h"


class CrashOverlay : public FinishOverlay
{
public:
    virtual ~CrashOverlay();
    CrashOverlay(float time, int peanuts, int points);
    
    virtual void ChimpHead(float startTime);
    virtual void Score(float startTime);
    virtual bool Medal(float startTime);
protected:
    
};

#endif // __CRASH_OVERLAY_H__
