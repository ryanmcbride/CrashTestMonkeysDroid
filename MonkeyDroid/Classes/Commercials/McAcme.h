//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __MCACME_H__
#define __MCACME_H__

// When you import this file, you import all the cocos2d classes
#include "Commercial.h"


class McAcme : public Commercial
{
public:
    virtual ~McAcme();
    McAcme();
    
    static void SetAdNumber(int num);
    virtual void update(float dt);
protected:
    void BuildIntroShort();
    void BuildOutroShort();
    void BuildIntroMed();
    void BuildOutroMed();
    void BuildIntro();
    void BuildOutro();
    cocos2d::CCSprite *m_Ad;
    static int s_adNumber;
};

#endif // __MCACME_H__
