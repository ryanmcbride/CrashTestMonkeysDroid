//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __COMMERCIAL_H__
#define __COMMERCIAL_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class Commercial : public cocos2d::CCLayer
{
public:
    virtual ~Commercial();
    Commercial();
    virtual void update(float dt);
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
protected:
    float m_TimeOut;
};

#endif // __COMMERCIAL_H__
