//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __ACHIEVEMENTS_H__
#define __ACHIEVEMENTS_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class Achievements : public cocos2d::CCLayer
{
public:
    virtual ~Achievements();
    Achievements();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    static void EarnAchievement(cocos2d::CCNode* topNode, int index);
    
    void backButtonTapped(CCObject*object);
private:
};

#endif // __ACHIEVEMENTS_H__
