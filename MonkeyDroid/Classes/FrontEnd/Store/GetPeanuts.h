//
//  Store.h
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#ifndef __GET_PEANUTS_H__
#define __GET_PEANUTS_H__

#include "cocos2d.h"

class GetPeanuts : public cocos2d::CCLayer
{
public:
    virtual ~GetPeanuts();
    GetPeanuts();
    void update(float dt);
    void returnButtonTapped(CCObject*object);
    void buyButtonTapped(CCObject*object);
protected:
    cocos2d::CCNode *m_MenuItems[6];
    cocos2d::CCSprite *spriteBG;
    bool bMenuBuilt;
    bool isReturning;
    void BuildMenu();
    void StopPeanuts();
    void unableToPurchasePopup();
    bool isFinishingPurchase();
};

#endif