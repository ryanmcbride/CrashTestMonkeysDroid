//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __MAIN_MENU_H__
#define __MAIN_MENU_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class MainMenu : public cocos2d::CCLayer
{
public:
    virtual ~MainMenu();
    MainMenu();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    void playButtonTapped(CCObject*object);
    void storeButtonTapped(CCObject*object);
    void optionsButtonTapped(CCObject*object);
    void achievementsButtonTapped(CCObject*object);
    void feedbackButtonTapped(CCObject*object);
    void update(float dt);
private:
    bool playbuttonTapped;
    void *m_AngryBirds[3];
    cocos2d::CCNode* m_BirdNode;
};

#endif // __MAIN_MENU_H__
