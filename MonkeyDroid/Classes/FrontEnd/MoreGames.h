//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __MORE_GAMES_H__
#define __MORE_GAMES_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class MoreGames : public cocos2d::CCLayer
{
public:
    virtual ~MoreGames();
    MoreGames();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    void backButtonTapped(CCObject*object);
    void starButtonTapped(CCObject*object);
    void bugButtonTapped(CCObject*object);
    void reviewButtonTapped(CCObject*object);
    void facebookButtonTapped(CCObject*object);
private:
};

#endif // __MORE_GAMES_H__
