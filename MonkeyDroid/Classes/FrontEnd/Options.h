//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __OPTIONS_H__
#define __OPTIONS_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class Options : public cocos2d::CCLayer
{
public:
    virtual ~Options();
    Options();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    void backButtonTapped(CCObject*object);
    void moreGamesButtonTapped(CCObject*object);
    void creditsButtonTapped(CCObject*object);
    void questionButtonTapped(CCObject*object);
    void sfxButtonTapped(CCObject*object);
    void musicButtonTapped(CCObject*object);
    
    void update(float dt);
private:
};

#endif // __OPTIONS_H__
