//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __LOADING_H__
#define __LOADING_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class Loading : public cocos2d::CCLayer
{
public:
    virtual ~Loading();
    Loading();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    void backButtonTapped(CCObject*object);
    void storeButtonTapped(CCObject*object);
    void nutsButtonTapped(CCObject*object);
    void fireButtonTapped(CCObject*object);
    void timeButtonTapped(CCObject*object);
    
    void update(float dt);
private:
    float m_TimeOut;
    cocos2d::CCNode *loadingBar;
};

#endif // __LOADING_H__
