//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __CITYBACKGROUND_H__
#define __CITYBACKGROUND_H__

// When you import this file, you import all the cocos2d classes
#include "BackGround.h"


class CityBackGround : public BackGround
{
public:
    virtual ~CityBackGround();
    CityBackGround();
    virtual void InitBG(cocos2d::CCNode *layer);
    virtual void Step(float xpos, float ypos);

protected:
    cocos2d::CCPoint m_Parallax2Points[4];
    cocos2d::CCArray *m_Parallax2;
};

#endif // __BACKGROUND_H__
