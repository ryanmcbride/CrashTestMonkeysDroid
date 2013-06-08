//
//  Store.h
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//
#ifndef __STORE_H__
#define __STORE_H__

#include "cocos2d.h"

class Store : public cocos2d::CCLayer
{
public:
    virtual ~Store();
    Store();
    
    
    static int numItemsCanBuy();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    void backButtonTapped(CCObject*object);
    void peanutButtonTapped(CCObject*object);
    void nullButtonTapped(CCObject*object);
    void buyUpgradeButtonTapped(CCObject*object);
    void powerupButtonTapped(CCObject*object);
    void charButtonTapped(CCObject*object);
    void bikeButtonTapped(CCObject*object);
    void update(float dt);
    void StopGetPeanuts();
protected:
    
    void StartGetPeanuts();
    void BuildUpgrades(cocos2d::CCMenu* menu);
    void BuildPowerUps(cocos2d::CCMenu* menu);
    void BuildCharacters(cocos2d::CCMenu* menu);
    void BuildBikes(cocos2d::CCMenu* menu);
    void addUpgradeBar(cocos2d::CCNode *sender, int amount, int buttonNum);
    
    cocos2d::CCLabelBMFont *m_currency;
    cocos2d::CCMenuItem *m_UpgradeButtons[10];
    cocos2d::CCLabelBMFont *m_UpgradeCosts[10];
    
    cocos2d::CCMenuItem *m_PowerUpbuttons[10];
    cocos2d::CCLabelTTF *m_PowerUpNames[10];
    
    cocos2d::CCMenuItem *m_Bikebuttons[10];
    cocos2d::CCLabelTTF *m_BikeDescriptions[10];
    
    cocos2d::CCMenuItem *m_Charbuttons[10];
    cocos2d::CCLabelTTF *m_CharDescriptions[10];
    
    cocos2d::CCNode *m_getPeanuts;
    cocos2d::CCNode *m_slideControl;
    
    cocos2d::CCMenuItem *ReturnButton;
    cocos2d::CCMenu *m_Menu;
};

#endif
