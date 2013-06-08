//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __LEVEL_SELECT_H__
#define __LEVEL_SELECT_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

struct LevelGoals
{
    float time;
    int peanuts;
    int points;
};
class LevelSelect : public cocos2d::CCLayer
{
public:
    virtual ~LevelSelect();
    LevelSelect();
    enum REGIONID
    {
        REGION_TUTORIAL = 0,
        REGION_TIKI = 1,
        REGION_CITY = 2,
        REGION_NIGHT = 3,
        REGION_SPACE = 4,
        REGION_BONUS = 5,
        REGION_ID_MAX = 6,
    };
    void Init(REGIONID regionID);
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene(REGIONID regionID);
    static cocos2d::CCScene* scene();
    
    static const char* getLevelName();
    static const char* getLevelXMLName();
    static void setNextLevel();
    static int getCurrentLevel();
    static LevelGoals *getLevelGoals();
    
    void backButtonTapped(CCObject*object);
    void levelButtonTapped(CCObject*object);
protected:
    void addButtonInfo(cocos2d::CCNode *node, REGIONID regionID, int number);
    static int m_LastRegionID;
    static char s_LevelName[64];
    static int s_LevelID;
    cocos2d::CCObject *m_Buttons[8];
};

#endif // __LEVEL_SELECT_H__
