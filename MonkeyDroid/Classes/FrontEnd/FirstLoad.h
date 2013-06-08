//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __FIRST_LOAD_H__
#define __FIRST_LOAD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"


class FirstLoad : public cocos2d::CCLayer
{
public:
    virtual ~FirstLoad();
    FirstLoad();
    void update(float dt);
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
protected:
};

#endif // __HELLO_WORLD_H__
