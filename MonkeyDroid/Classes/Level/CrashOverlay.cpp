//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "CrashOverlay.h"
#include "SimpleAudioEngine.h"
#include "../FrontEnd/MainMenu.h"
#include "../ScreenHelper.h"
#include "../FrontEnd/LevelSelect.h"
#include "../FrontEnd/Pause.h"
#include "../FrontEnd/SaveLoad.h"
#include "../FrontEnd/Achievements.h"


using namespace cocos2d;
using namespace CocosDenshion;

CrashOverlay::CrashOverlay(float time, int peanuts, int points)
{
    CCTextureCache::sharedTextureCache()->addImage("Tutorial.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Tutorial.plist");
    ScreenInit(time,peanuts,points);
}
CrashOverlay::~CrashOverlay()
{
    
}
void CrashOverlay::ChimpHead(float startTime)
{
    float scale = ScreenHelper::getTextureScale();
    
    CCNode *monkeyNode = CCNode::create();
    addChild(monkeyNode,1);
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Tut_Rays.png");
    sprite->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f,150)));
    sprite->runAction(CCSequence::create(
                                         CCDelayTime::create(startTime+0.3f),
                                         CCScaleTo::create(0.1f,0.75f),NULL));
    monkeyNode->addChild(sprite);
    sprite = CCSprite::createWithSpriteFrameName("ctm_Tut_Rays.png");
    sprite->runAction(CCRepeatForever::create(CCRotateBy::create(1.0f,-150)));
    sprite->runAction(CCSequence::create(
                                         CCDelayTime::create(startTime+0.3f),
                                         CCScaleTo::create(0.1f,0.75f),NULL));
    sprite->setRotation(22.5f);
    monkeyNode->addChild(sprite);
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_Char_BGPanel.png");
    monkeyNode->addChild(sprite);
    
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_MonkeyLoss.png");
    sprite->setPosition(ccp(0,-10));
    monkeyNode->addChild(sprite);
    
    int randInt = RandomInt(0, 100);
    
    if(randInt > 66)
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_lose_Chump.png");
        sprite->setPosition(ccp(12,110));
        monkeyNode->addChild(sprite);
    }
    else if(randInt > 33)
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_lose_Chump.png");
        sprite->setPosition(ccp(12,110));
        monkeyNode->addChild(sprite);
    }
    else
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_lose_OUCH!.png");
        sprite->setPosition(ccp(12,110));
        monkeyNode->addChild(sprite);
    }
    
    monkeyNode->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    monkeyNode->setScale(0.01f);
    CCSequence *sequence = CCSequence::create(CCDelayTime::create(startTime),
                                              CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySound1)),
                                              CCScaleTo::create(0.2f,1.2f*scale),
                                              CCScaleTo::create(0.1f,0.9f*scale),
                                              CCScaleTo::create(0.09f,1.05f*scale),
                                              CCScaleTo::create(0.05f ,1.0f*scale),
                                              CCDelayTime::create(1.5f),
                                              CCScaleTo::create(0.2f,0.1f*scale),
                                              CCCallFuncN::create(monkeyNode, callfuncN_selector(CCNode::removeFromParentAndCleanup)),
                                              NULL);
    monkeyNode->runAction(sequence);
}

#define NUM_HINTS 15
static const char *s_HintText[NUM_HINTS] =
{
    "Tilt your phone back to center to stop flips!",
    "Special",
    "To reach new heights, Upgrade Turbo Strips and Trampolines in the Store!",
    "Being on Fire will increase your trick score!",
    "Crashing will bring up hints!",
    "Doing More Flips will increase your trick score!",
    "Bonus levels are all about tricks.",
    "Always look both directions before crossing the street!",
    "Upgrading your tricks will increase your trick score!",
    "Don't take any wooden peanuts!",
    "A coconut a day keeps the doctor away.",
    "Can't get a medal? Use Power Ups to make things easier!",
    "Don't make mistakes.",
    "Never end a sentence with a proposition.",
    "Want to improve your trick score? Bounce on Trampolines multiple times.",
};
void CrashOverlay::Score(float startTime)
{
    float scale = ScreenHelper::getTextureScale();
    
    CCNode *tipNode = CCNode::create();
    addChild(tipNode);
    
    tipNode->setScale(0.01f);
    CCSequence *sequence2 = CCSequence::create(
                                               CCDelayTime::create(startTime),
                                               CCScaleTo::create(0.2f ,1.2f*scale),
                                               CCScaleTo::create(0.1f ,0.9f*scale),
                                               CCScaleTo::create(0.09f ,1.05f*scale),
                                               CCScaleTo::create(0.05f ,1.0f*scale),
                                               NULL);
    tipNode->runAction(sequence2);
    CCSprite *tipBox = CCSprite::createWithSpriteFrameName("ctm_Tutorial_Text_Blank.png");
    tipNode->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 20.0f));
    tipNode->addChild(tipBox);
    
    int hintNum = SaveLoad::m_SaveData.currentHint;
    SaveLoad::m_SaveData.currentHint += 1;
    if(SaveLoad::m_SaveData.currentHint >= NUM_HINTS)
        SaveLoad::m_SaveData.currentHint = 0;
    
    CCSize dim;
    dim.width = 280.0f;
    dim.height = 75.0f;
    
    CCLabelTTF *label = CCLabelTTF::create("Hint:","Jacoby ICG Black.ttf",20,dim,kCCTextAlignmentCenter);
    label->setColor(ccc3(237,188,0));
    label->setPosition(ccp(315.0f/2.0f,85-25));
    tipBox->addChild(label);
    
    if(hintNum==1)
    {
        dim.width = 200.0f;
        label = CCLabelTTF::create("Use the Jump Button to Avoid Hazards","Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentLeft);
        label->setColor(ccc3(230,230,230));
        label->setPosition(ccp(120,65-25));
        tipBox->addChild(label);
        CCSprite *hazard = CCSprite::createWithSpriteFrameName("ctm_Barrel.png");
        hazard->setScale(0.9f);
        hazard->setPosition(ccp(270,55));
        tipBox->addChild(hazard);
        
        CCSprite *porcupine = CCSprite::createWithSpriteFrameName("ctm_Porcupine.png");
        porcupine->setScale(0.3f);
        porcupine->setPosition(ccp(215,55));
        tipBox->addChild(porcupine);
    }
    else
    {
        label = CCLabelTTF::create(s_HintText[hintNum],"Jacoby ICG Black.ttf",15,dim,kCCTextAlignmentCenter);
        label->setColor(ccc3(230,230,230));
        label->setPosition(ccp(315.0f/2.0f,65-25));
        tipBox->addChild(label);
    }
}

bool CrashOverlay::Medal(float startTime)
{
    if(SaveLoad::m_SaveData.objectives[SaveLoad::ROAD_KILL]==0)
    {
        SaveLoad::m_SaveData.crashCount = SaveLoad::m_SaveData.crashCount+1;
        if(SaveLoad::m_SaveData.crashCount >= 10)
        {
            Achievements::EarnAchievement(this,SaveLoad::ROAD_KILL);
        }
    }
    return false;
}

