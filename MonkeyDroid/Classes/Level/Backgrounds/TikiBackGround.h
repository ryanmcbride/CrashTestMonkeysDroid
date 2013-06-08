//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __TIKIBACKGROUND_H__
#define __TIKIBACKGROUND_H__

// When you import this file, you import all the cocos2d classes
#include "BackGround.h"


class TikiBackGround : public BackGround
{
public:
    virtual ~TikiBackGround();
    TikiBackGround();
    virtual void InitBG(cocos2d::CCNode *layer);
    virtual void Step(float xpos, float ypos);

protected:
    cocos2d::CCSprite *m_Scale9[4];
    int numScale9;
    
    cocos2d::CCPoint m_Parallax2Points[4];
    cocos2d::CCArray *m_Parallax2;
    cocos2d::CCPoint m_Parallax3Points[4];
    cocos2d::CCArray *m_Parallax3;
    cocos2d::CCPoint m_Parallax4Points[4];
    cocos2d::CCArray *m_Parallax4;

};

#endif // __BACKGROUND_H__
