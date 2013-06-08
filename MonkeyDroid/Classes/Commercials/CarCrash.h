//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __CARCRASH_H__
#define __CARCRASH_H__

// When you import this file, you import all the cocos2d classes
#include "Commercial.h"


class CarCrash : public Commercial
{
public:
    virtual ~CarCrash();
    CarCrash();
    virtual void update(float dt);
};
#endif // __HELLO_WORLD_H__
