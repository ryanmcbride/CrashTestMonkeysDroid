//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "FinishOverlay.h"
#include "SimpleAudioEngine.h"
#include "../FrontEnd/MainMenu.h"
#include "../FrontEnd/SaveLoad.h"
#include "../ScreenHelper.h"
#include "../AudioManager.h"
#include "../FrontEnd/Achievements.h"
#include "../FrontEnd/LevelSelect.h"
#include "../FrontEnd/Pause.h"
#include "../FrontEnd/Loading.h"
#include "../Commercials/Commercial.h"
#include "../FrontEnd/Store/Store.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern bool g_2XPeanuts;
extern bool g_PermanentFire;
extern bool g_SlowClock;


FinishOverlay::FinishOverlay()
{
}
FinishOverlay::FinishOverlay(float time, int peanuts, int points)
{
    ScreenInit(time,peanuts,points);
}

void FinishOverlay::ScreenInit(float time, int peanuts, int points)
{
    setTouchEnabled( true );
    
    m_time = time;
    m_peanuts = peanuts;
    m_points = points;
    SaveLoad::m_SaveData.currency += peanuts;
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
    CCTextureCache::sharedTextureCache()->addImage("ctm_WinScreen.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_WinScreen.pv.plist");
    
    
    this->ChimpHead(2.0f);
    this->SocialBar(5.0f);
    this->NavBar(5.0f);
    this->Store(5.3f);
    m_EarningMedal = this->Medal(8.0f);
    this->Score(5.0f);
    
    
    int currentLevel = LevelSelect::getCurrentLevel();
    if(currentLevel==TUTORIAL_LEVELSTART+5)
        SaveLoad::m_SaveData.levelflags[ISLAND_LEVELSTART] |= SaveLoad::UNLOCKED;
    else
        SaveLoad::m_SaveData.levelflags[currentLevel+1] |= SaveLoad::UNLOCKED;
    SaveLoad::Save();
}
void FinishOverlay::ChimpHead(float startTime)
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
    
    
    sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_MonkeyWin.png");
    sprite->setPosition(ccp(0,-10));
    monkeyNode->addChild(sprite);
    
    int randInt = RandomInt(0, 100);
    
    if(randInt > 66)
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_win_Chimptastic.png");
        sprite->setPosition(ccp(12,110));
        monkeyNode->addChild(sprite);
    }
    else if(randInt > 33)
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_win_Darwinning.png");
        sprite->setPosition(ccp(12,110));
        monkeyNode->addChild(sprite);
    }
    else
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_UI_winscreen_win_Unpossible.png");
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
void FinishOverlay::SocialBar(float startTime)
{
    
}
void FinishOverlay::NavBar(float startTime)
{
    float scale = ScreenHelper::getTextureScale();
    int currentLevel = LevelSelect::getCurrentLevel();
    
    CCMenuItem *RestartButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_21.png"), CCSprite::createWithSpriteFrameName("ctm_Button_21_Down.png"), this, menu_selector(FinishOverlay::restartButtonTapped));
    RestartButton->setScale(scale);
    RestartButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,-70.0f,30.0f));
    
    CCMenuItem *LevelSelectButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_25.png"), CCSprite::createWithSpriteFrameName("ctm_Button_25_Down.png"), this, menu_selector(FinishOverlay::levelSelectButtonTapped));
    LevelSelectButton->setScale(scale);
    LevelSelectButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,0.0f,30.0f));
    
    CCMenuItem *NextButton = NULL;
    if(canDoNextLevel(currentLevel))
    {
        NextButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_26.png"), CCSprite::createWithSpriteFrameName("ctm_Button_26_Down.png"),  this, menu_selector(FinishOverlay::nextLevelButtonTapped));
        NextButton->setScale(scale);
        NextButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER,70.0f,30.0f));
    }
    
    CCMenu* menu = CCMenu::create(RestartButton, LevelSelectButton, NextButton,NULL);
    menu->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,0.0f,-100.0f));
    addChild(menu,4);

    menu->runAction(CCSequence::create(CCDelayTime::create(startTime),CCMoveTo::create(0.1f,ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT)),NULL));
}
void FinishOverlay::Store(float startTime)
{
    float scale = ScreenHelper::getTextureScale();
    CCMenuItem *StoreButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_17.png"), CCSprite::createWithSpriteFrameName("ctm_Button_17_Down.png"), this, menu_selector(FinishOverlay::storeButtonTapped));
    StoreButton->setScale(scale);
    StoreButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_RIGHT,-40.0f,35.0f));
    
    CCMenu* menu = CCMenu::create(StoreButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,100.0f,0.0f));
    addChild(menu,4);
    menu->runAction(CCSequence::create(CCDelayTime::create(startTime),CCMoveTo::create(0.1f,ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT)),NULL));
}
void FinishOverlay::Score(float startTime)
{
    float scale = ScreenHelper::getTextureScale();
    int currentLevel = LevelSelect::getCurrentLevel();
    int currentMedalLevel = 0;
    if(SaveLoad::NumBronzeMedals()>=24)
        currentMedalLevel = 1;
    if(SaveLoad::NumSilverMedals()>=24)
        currentMedalLevel = 2;
    if(SaveLoad::NumGoldMedals()>=24)
        currentMedalLevel = 3;
    
    LevelGoals *goals = LevelSelect::getLevelGoals();
    bool showOutOf = true;
    if (currentMedalLevel==2)
    {
        if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::THREE_COCONUT)
        {
            showOutOf = false;
        }
    }
    else if (currentMedalLevel==1)
    {
        if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::TWO_COCONUT)
        {
            showOutOf = false;
        }
    }
    else if(currentMedalLevel==0)
    {
        if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::ONE_COCONUT)
        {
            showOutOf = false;
        }
    }

    CCNode *mainNode = NULL;
    if(showOutOf)
    {
        mainNode = CCNode::create();
        mainNode->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 50.0f,50.0f));
        mainNode->setScale(scale);
        addChild(mainNode,2);
        char tempString[64];
        
        CCSize dim;
        dim.width = 300.0f;
        dim.height = 40.0f;
        
        CCLabelTTF *pointLabel = CCLabelTTF::create("Points:","Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        pointLabel->setColor(ccc3(237,188,0));
        pointLabel->setPosition(ccp(20.0f,40.0f));
        mainNode->addChild(pointLabel);
        
        sprintf(tempString,"             %d/%d",m_points,goals->points);
        CCLabelTTF *pointLabelAmount = CCLabelTTF::create(tempString,"Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        pointLabelAmount->setPosition(ccp(20.0f,40.0f));
        
        if(m_points >= goals->points)
            pointLabelAmount->setColor(ccc3(255,255,255));
        else
            pointLabelAmount->setColor(ccc3(255,0,0));
        
        mainNode->addChild(pointLabelAmount);
        
        
        sprintf(tempString,"           %.2f/%.2f",m_time,goals->time);
        CCLabelTTF *timeLabel = CCLabelTTF::create("Time:","Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        timeLabel->setColor(ccc3(237,188,0));
        timeLabel->setPosition(ccp(20.0f,0.0f));
        mainNode->addChild(timeLabel);
        
        
        CCLabelTTF *timeLabelAmount = CCLabelTTF::create(tempString,"Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        timeLabelAmount->setPosition(ccp(20.0f,0.0f));
        
        if(m_time <= goals->time)
            timeLabelAmount->setColor(ccc3(255,255,255));
        else
            timeLabelAmount->setColor(ccc3(255,0,0));
        
        mainNode->addChild(timeLabelAmount);
        
        
        if(goals->peanuts)
        {
            CCLabelTTF *pickupLabel = CCLabelTTF::create("Peanuts:","Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
            pickupLabel->setColor(ccc3(237,188,0));
            pickupLabel->setPosition(ccp(20.0f,-40.0f));
            mainNode->addChild(pickupLabel);
            
            sprintf(tempString,"                %d/%d",m_peanuts,goals->peanuts);
            CCLabelTTF *pickupLabelAmount = CCLabelTTF::create(tempString,"Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
            pickupLabelAmount->setPosition(ccp(20.0f,-40.0f));
            
            if(m_peanuts >= goals->peanuts)
                pickupLabelAmount->setColor(ccc3(255,255,255));
            else
                pickupLabelAmount->setColor(ccc3(255,0,0));
            
            mainNode->addChild(pickupLabelAmount);
        }

    }
    else
    {
        mainNode = CCNode::create();
        mainNode->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 50.0f, 50.0f));
        mainNode->setScale(scale);
        addChild(mainNode,2);
        char tempString[64];
        
        CCSize dim;
        dim.width = 300.0f;
        dim.height = 40.0f;
        
        CCLabelTTF *pointLabel = CCLabelTTF::create("Points:","Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        pointLabel->setColor(ccc3(237,188,0));
        pointLabel->setPosition(ccp(20.0f,40.0f));
        mainNode->addChild(pointLabel);
        
        sprintf(tempString,"             %d",m_points);
        CCLabelTTF *pointLabelAmount = CCLabelTTF::create(tempString,"Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        pointLabelAmount->setPosition(ccp(20.0f,40.0f));
        pointLabelAmount->setColor(ccc3(255,255,255));
        
        mainNode->addChild(pointLabelAmount);
        
        
        sprintf(tempString,"           %.2f",m_time);
        CCLabelTTF *timeLabel = CCLabelTTF::create("Time:","Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        timeLabel->setColor(ccc3(237,188,0));
        timeLabel->setPosition(ccp(20.0f,0.0f));
        mainNode->addChild(timeLabel);
        
        
        CCLabelTTF *timeLabelAmount = CCLabelTTF::create(tempString,"Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
        timeLabelAmount->setPosition(ccp(20.0f,0.0f));
        timeLabelAmount->setColor(ccc3(255,255,255));
        
        mainNode->addChild(timeLabelAmount);
        
        
        if(goals->peanuts)
        {
            CCLabelTTF *pickupLabel = CCLabelTTF::create("Peanuts:","Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
            pickupLabel->setColor(ccc3(237,188,0));
            pickupLabel->setPosition(ccp(20.0f,-40.0f));
            mainNode->addChild(pickupLabel);
            
            sprintf(tempString,"                %d",m_peanuts);
            CCLabelTTF *pickupLabelAmount = CCLabelTTF::create(tempString,"Jacoby ICG Black.ttf",28,dim,kCCTextAlignmentLeft);
            pickupLabelAmount->setPosition(ccp(20.0f,-40.0f));
            pickupLabelAmount->setColor(ccc3(255,255,255));
            
            
            mainNode->addChild(pickupLabelAmount);
        }
    }
    if(mainNode)
    {
        mainNode->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,50.0f,0.0f));
        mainNode->setScale(0.01f);
        if(m_EarningMedal)
        {
            CCSequence *sequence = CCSequence::create(
                                                      CCDelayTime::create(startTime),
                                                      CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySound2)),
                                                      CCScaleTo::create(0.2f,1.2f*scale),
                                                      CCScaleTo::create(0.1f,0.9f*scale),
                                                      CCScaleTo::create(0.09f,1.05f*scale),
                                                      CCScaleTo::create(0.05f,1.0f*scale),
                                                      CCDelayTime::create(1.5f),
                                                      CCScaleTo::create(0.2f,0.1f*scale),
                                                      CCCallFuncN::create(mainNode, callfuncN_selector(CCNode::removeFromParentAndCleanup)),
                                                      NULL);
    
            mainNode->runAction(sequence);
        }
        else
        {
            CCSequence *sequence = CCSequence::create(
                                                      CCDelayTime::create(startTime),
                                                      CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySound2)),
                                                      CCScaleTo::create(0.2f,1.2f*scale),
                                                      CCScaleTo::create(0.1f,0.9f*scale),
                                                      CCScaleTo::create(0.09f,1.05f*scale),
                                                      CCScaleTo::create(0.05f,1.0f*scale),
                                                      NULL);
            mainNode->runAction(sequence);
        }
    }
    
    
    if(SaveLoad::m_SaveData.currency > 30000 && SaveLoad::m_SaveData.objectives[SaveLoad::MEH]==0)
    {
        Achievements::EarnAchievement(this,SaveLoad::MEH);
    }
    if(m_points < 0 && m_time < 0.0f )
    {
        if(SaveLoad::m_SaveData.objectives[SaveLoad::THE_MINUS_WORLD]==0)
        {
            Achievements::EarnAchievement(this,SaveLoad::THE_MINUS_WORLD);
        }
    }
    if(m_peanuts >= 1000)
    {
        if(SaveLoad::m_SaveData.objectives[SaveLoad::PEANUT_ENVY]==0)
        {
            Achievements::EarnAchievement(this,SaveLoad::PEANUT_ENVY);
        }
    }
    if(g_PermanentFire && g_2XPeanuts && g_SlowClock)
    {
        if(SaveLoad::m_SaveData.objectives[SaveLoad::THIS_IS_SPARTA]==0)
        {
            Achievements::EarnAchievement(this,SaveLoad::THIS_IS_SPARTA);
        }
    }
    
    
}
bool FinishOverlay::Medal(float startTime)
{
    bool returnVal = false;
    float scale = ScreenHelper::getTextureScale();
    int currentLevel = LevelSelect::getCurrentLevel();
    int currentMedalLevel = 0;
    if(SaveLoad::NumBronzeMedals()>=24)
        currentMedalLevel = 1;
    if(SaveLoad::NumSilverMedals()>=24)
        currentMedalLevel = 2;
    if(SaveLoad::NumGoldMedals()>=24)
        return returnVal;
    
    
    LevelGoals *goals = LevelSelect::getLevelGoals();
    //if(m_time <= goals->time && m_peanuts >= goals->peanuts && m_points >= goals->points)
    {
        int showMedal = 0;
        int showMessage = 0;
        if (currentMedalLevel==2)
        {
            if(m_time <= goals->time && m_peanuts >= goals->peanuts && m_points >= goals->points)
            {
                SaveLoad::m_SaveData.levelflags[currentLevel] |= SaveLoad::THREE_COCONUT;
                showMedal = 3;
            }
        }
        else if (currentMedalLevel==1)
        {
            if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::TWO_COCONUT)
            {
                showMessage = 2;
            }
            else if(m_time <= goals->time && m_peanuts >= goals->peanuts && m_points >= goals->points)
            {
                SaveLoad::m_SaveData.levelflags[currentLevel] |= SaveLoad::TWO_COCONUT;
                showMedal = 2;
            }
        }
        else if(currentMedalLevel==0)
        {
            if(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::ONE_COCONUT)
            {
                showMessage = 1;
            }
            else if(m_time <= goals->time && m_peanuts >= goals->peanuts && m_points >= goals->points)
            {
                SaveLoad::m_SaveData.levelflags[currentLevel] |= SaveLoad::ONE_COCONUT;
                showMedal = 1;
            }
        }
        
        if(SaveLoad::NumGoldMedals()>=32)
        {
            SaveLoad::m_SaveData.medalLockLevel = 3;
        }
        else if(SaveLoad::NumSilverMedals()>=32)
        {
            SaveLoad::m_SaveData.medalLockLevel = 2;
        }
        else if(SaveLoad::NumBronzeMedals()>=32)
        {
            SaveLoad::m_SaveData.medalLockLevel = 1;
        }
        
        CCLabelTTF *label = NULL;
        
        
        if(showMessage)
        {
            const char *medalStrings[3] =
            {
                "Bronze",
                "Silver",
                "Gold",
            };
            char messageStr[128];
            sprintf(messageStr,"Earn all of the %s medals\nto unlock %s medal challenges.",medalStrings[showMessage-1],medalStrings[showMessage]);
            
            label = CCLabelTTF::create(messageStr, "impact.ttf", 24*scale);
            addChild(label, 2);
            label->setColor(ccc3(255,255,255));
            label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,0.0f));
            
            label->setOpacity(0);
            CCSequence *labelSequence = CCSequence::create(
                                             CCDelayTime::create(startTime),
                                             CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySoundBronze)),
                                             CCFadeIn::create(0.1f),
                                             NULL);
            
            label->runAction(labelSequence);
            
            
            returnVal = true;
        }
        else if(showMedal)
        {
            CCNode *control = CCNode::create();
            control->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            control->setScale(scale);
            addChild(control);
            
            
            CCSprite *medalSprite;
            CCSprite *medalSpriteGlitter[3];
            CCCallFuncN *soundAction;
            
            if(showMedal==1)
            {
                soundAction = CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySoundBronze));
                medalSprite = CCSprite::createWithSpriteFrameName("ctm_Tut_Bronze_Medal.png");
                medalSpriteGlitter[0] = CCSprite::createWithSpriteFrameName("ctm_Tut_yellowStar.png");
                medalSpriteGlitter[1] = CCSprite::createWithSpriteFrameName("ctm_Tut_yellowStar.png");
                medalSpriteGlitter[2] = CCSprite::createWithSpriteFrameName("ctm_Tut_yellowStar.png");
            }
            else if(showMedal==2)
            {
                soundAction = CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySoundSilver));
                medalSprite = CCSprite::createWithSpriteFrameName("ctm_Tut_Silver_Medal.png");
                medalSpriteGlitter[0] = CCSprite::createWithSpriteFrameName("ctm_Tut_silverStar.png");
                medalSpriteGlitter[1] = CCSprite::createWithSpriteFrameName("ctm_Tut_silverStar.png");
                medalSpriteGlitter[2] = CCSprite::createWithSpriteFrameName("ctm_Tut_silverStar.png");
                
            }
            else
            {
                soundAction = CCCallFuncN::create(this,callfuncN_selector(FinishOverlay::PlaySoundGold));
                medalSprite = CCSprite::createWithSpriteFrameName("ctm_Tut_Gold_Medal.png");
                medalSpriteGlitter[0] = CCSprite::createWithSpriteFrameName("ctm_Tut_yellowStar.png");
                medalSpriteGlitter[1] = CCSprite::createWithSpriteFrameName("ctm_Tut_yellowStar.png");
                medalSpriteGlitter[2] = CCSprite::createWithSpriteFrameName("ctm_Tut_yellowStar.png");
                
            }
            
            const char *medalName = "Bronze";
            if(showMedal==2)
                medalName = "Silver";
            if(showMedal==3)
                medalName = "Gold";
            
            
            
            CCLabelTTF *bonusAmount = CCLabelTTF::create("Bonus:","Jacoby ICG Black.ttf",36);
            bonusAmount->setColor(ccc3(230,230,230));
            bonusAmount->setPosition(ccp(88.0f,260.0f));
            medalSprite->addChild(bonusAmount);
            
            CCSprite *pUp;
            int num = RandomInt(0,100);
            if(num > 66)
            {
                SaveLoad::m_SaveData.numLevelFire += 1;
                pUp = CCSprite::createWithSpriteFrameName("ctm_icon_Store_18_Fire.png");
            }
            else if (num > 33)
            {
                SaveLoad::m_SaveData.numTimeSlow += 1;
                pUp = CCSprite::createWithSpriteFrameName("ctm_icon_Store_16_Slow-Clock.png");
            }
            else
            {
                SaveLoad::m_SaveData.numDoubleNuts += 1;
                pUp = CCSprite::createWithSpriteFrameName("ctm_icon_Store_17_2X-peanuts.png");
            }
            pUp->setPosition(ccp(150,25));
            pUp->setScale(1.0f/0.75f);
            bonusAmount->addChild(pUp);
            

            CCAction *altAction = NULL;
            CCAction *altAction2 = NULL;

            if(DoFinalTrainingMessage(startTime+3.0f))
            {                
                altAction = CCDelayTime::create(3.0);
                altAction2 = CCFadeOut::create(0.03f);
            }
            
            
            medalSprite->setPosition(ccp(0.0f,-10.0f));
            control->addChild(medalSprite);
            medalSprite->setScale(0.01f);
            CCSequence *sequence3 = CCSequence::create(
                                     CCDelayTime::create(startTime),
                                     soundAction,
                                     CCScaleTo::create(0.2f ,1.2f*0.75f ,1.2f*0.75f),
                                     CCScaleTo::create(0.1f ,0.9f*0.75f ,0.9f*0.75f),
                                     CCScaleTo::create(0.09f ,1.05f*0.75f ,1.05f*0.75f),
                                     CCScaleTo::create(0.05f ,1.0f*0.75f ,1.0f*0.75f),
                                     altAction,
                                     altAction2,
                                     NULL);
            medalSprite->runAction(sequence3);
            
            medalSprite->addChild(medalSpriteGlitter[0]);
            medalSpriteGlitter[0]->setPosition(ccp(33.0f,150.0f));
            medalSpriteGlitter[0]->setScale(0.1f);
            medalSpriteGlitter[0]->setOpacity(0.0f);
            
            medalSpriteGlitter[0]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 0.5f)),
                                              CCScaleTo::create(0.3f ,2.0f ,2.0f),
                                              NULL));
            medalSpriteGlitter[0]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 0.5f)),
                                              CCRotateBy::create(0.3f , 180),
                                              NULL));
            medalSpriteGlitter[0]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 0.5f)),
                                              CCFadeIn::create(0.1f),
                                              CCDelayTime::create((0.17)),
                                              CCFadeOut::create(0.03f),
                                              NULL));
            
            
            
            medalSprite->addChild(medalSpriteGlitter[1]);
            medalSpriteGlitter[1]->setPosition(ccp(143.0f,123.0f));
            medalSpriteGlitter[1]->setScale(0.1f);
            medalSpriteGlitter[1]->setOpacity(0.0f);
            
            medalSpriteGlitter[1]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 0.75f)),
                                              CCScaleTo::create(0.3f ,2.0f ,2.0f),
                                              NULL));
            medalSpriteGlitter[1]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 0.75f)),
                                              CCRotateBy::create(0.3f , 180),
                                              NULL));
            medalSpriteGlitter[1]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 0.75f)),
                                              CCFadeIn::create(0.1f),
                                              CCDelayTime::create((0.17)),
                                              CCFadeOut::create(0.03f),
                                              NULL));
            
            
            medalSprite->addChild(medalSpriteGlitter[2]);
            medalSpriteGlitter[2]->setPosition(ccp(100.0f,225.0f));
            medalSpriteGlitter[2]->setScale(0.1f);
            medalSpriteGlitter[2]->setOpacity(0.0f);
            
            medalSpriteGlitter[2]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 1.0f)),
                                              CCScaleTo::create(0.3f ,2.0f ,2.0f),
                                              NULL));
            medalSpriteGlitter[2]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 1.0f)),
                                              CCRotateBy::create(0.3f , 180),
                                              NULL));
            medalSpriteGlitter[2]->runAction(CCSequence::create(
                                              CCDelayTime::create((startTime + 1.0f)),
                                              CCFadeIn::create(0.1f),
                                              CCDelayTime::create((0.17)),
                                              CCFadeOut::create(0.03f),
                                              NULL));
            
            
            
            
            
            if(SaveLoad::DoSpaceMedalCount()>=5)
            {
                if(SaveLoad::m_SaveData.objectives[SaveLoad::THATS_NO_MOON]==0)
                {
                    Achievements::EarnAchievement(this,SaveLoad::THATS_NO_MOON);
                }
            }
            if(SaveLoad::DoNightMedalCount()>=5)
            {
                if(SaveLoad::m_SaveData.objectives[SaveLoad::BEAT_UP_THE_BEAT]==0)
                {
                    Achievements::EarnAchievement(this,SaveLoad::BEAT_UP_THE_BEAT);
                }
            }
            
            
            returnVal = true;
        }
        
        
    }
    return returnVal;
}
bool FinishOverlay::DoFinalTrainingMessage(float startTime)
{
    int currentLevel = LevelSelect::getCurrentLevel();
    
    if(currentLevel==5)
    {        
        CCSize myDim;
        myDim.width = 350;
        myDim.height = 100;
        CCLabelTTF *CongratsTraining = CCLabelTTF::create("Congratulations!","impact.ttf",32,myDim,kCCTextAlignmentCenter);
        addChild(CongratsTraining);
        CongratsTraining->setPosition(ccp(0.0f,60.0f));
        CongratsTraining->setOpacity(0);
        CCSequence *trainingSequence = CCSequence::create(
                                                          CCDelayTime::create(startTime),
                                                          CCFadeIn::create(0.1f),
                                                          NULL);
        CongratsTraining->runAction(trainingSequence);
        
        
        CCLabelTTF *CongratsTraining2 = CCLabelTTF::create("You are now a trained Monkey.\nTime to start winning medals!","impact.ttf",32,myDim,kCCTextAlignmentCenter);
        addChild(CongratsTraining2);
        CongratsTraining2->setPosition(ccp(0.0f,10.0f));
        CongratsTraining2->setOpacity(0);
        CCSequence *trainingSequence2 = CCSequence::create(
                                                           CCDelayTime::create(startTime),
                                                           CCFadeIn::create(0.1f),
                                                           NULL);
        CongratsTraining2->runAction(trainingSequence2);
        
        
        if(SaveLoad::m_SaveData.objectives[SaveLoad::MISSION_ACCOMPLISHED]==0)
        {
            Achievements::EarnAchievement(this,SaveLoad::MISSION_ACCOMPLISHED);
        }
        return true;
    }
    return false;
}
bool FinishOverlay::canDoNextLevel(int levelNum)
{
    if(levelNum >= BONUS_LEVELSTART)
        return false;
    if(levelNum%8==7)
        return false;
    return true;
}

void FinishOverlay::restartButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(Loading::scene());
}
void FinishOverlay::levelSelectButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene());
}
void FinishOverlay::nextLevelButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    if(LevelSelect::getCurrentLevel()<8)
    {
        LevelSelect::setNextLevel();
        CCDirector::sharedDirector()->replaceScene(Loading::scene());
    }
    else
    {
        LevelSelect::setNextLevel();
        CCDirector::sharedDirector()->replaceScene(Commercial::scene());
    }
}
void FinishOverlay::storeButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    CCDirector::sharedDirector()->pushScene(Store::scene());
}
void FinishOverlay::PlaySound1(CCNode * node)
{
    AudioManager::PlayEffect(AUDIO_FEEDBACK_POSITIVE);
}
void FinishOverlay::PlaySound2(CCNode * node)
{
    AudioManager::PlayEffect(AUDIO_STATS_POPUP);
}
void FinishOverlay::PlaySoundGold(CCNode * node)
{
    AudioManager::PlayEffect(AUDIO_GOLD_MEDAL);
}
void FinishOverlay::PlaySoundSilver(CCNode * node)
{
    AudioManager::PlayEffect(AUDIO_SILVER_MEDAL);
}
void FinishOverlay::PlaySoundBronze(CCNode * node)
{
    AudioManager::PlayEffect(AUDIO_BRONZE_MEDAL);
}



FinishOverlay::~FinishOverlay()
{
    
}






class TutorialFinishOverlay : public FinishOverlay
{
public:
    virtual ~TutorialFinishOverlay(){}
    TutorialFinishOverlay(float time, int peanuts, int points)
    {
        int currentLevel = LevelSelect::getCurrentLevel();
        m_NoNext = false;
        bool noNav = false;

        float scale = ScreenHelper::getTextureScale();
        CCSize dim = CCSizeMake(280*scale, 55*scale);
        char text[128];
        if(currentLevel==2 && SaveLoad::m_SaveData.trampLockLevel==0)
        {
            SaveLoad::m_SaveData.currency = 200;
            sprintf(text,"Go to the store and\nbuy an Armadillo");
            dim.height = 70*scale;
            m_hasChanged = false;
            noNav = true;
            scheduleUpdate();
        }
        else
        {
            if(time > 30.001 && currentLevel == 4)
            {
                sprintf(text,"Try Again");
                m_NoNext = true;
            }
            else if(currentLevel == 5)
            {
                sprintf(text,"Try Again");
            }
            else
                sprintf(text,"Good Job");
        }
        CCLabelTTF *label = CCLabelTTF::create(text,"impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 30.0f));
        this->addChild(label,0,1);
        
        
        if(!noNav)
        {
            this->NavBar(5.0f);
        }
        
        
        if(currentLevel >= 2)
            this->Store(5.3f);
        
        if(currentLevel==TUTORIAL_LEVELSTART+5)
            SaveLoad::m_SaveData.levelflags[ISLAND_LEVELSTART] |= SaveLoad::UNLOCKED;
        else
            SaveLoad::m_SaveData.levelflags[currentLevel+1] |= SaveLoad::UNLOCKED;
        SaveLoad::Save();
    }
    virtual void NavBar(float startTime)
    {
        FinishOverlay::NavBar(startTime);
    }
    virtual void Store(float startTime)
    {
        FinishOverlay::Store(startTime);
    }
    
    virtual void SocialBar(float startTime){}
    virtual void ChimpHead(float startTime){}
    virtual void Score(float startTime){}
    virtual bool Medal(float startTime){return false;}
    
    void update(float dt)
    {
        if(LevelSelect::getCurrentLevel()==2 && SaveLoad::m_SaveData.trampLockLevel!=0)
        {
            if(!m_hasChanged)
            {
                float scale = ScreenHelper::getTextureScale();
                
                this->removeChildByTag(1,true);
                
                CCSize dim = CCSizeMake(280*scale, 55*scale);
                CCLabelTTF *label = CCLabelTTF::create("Good Job","impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
                label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 0.0f, 30.0f));
                this->addChild(label,0,1);
                
                
                this->NavBar(0.5f);
                
                m_hasChanged = true;
            }
        }
    }
protected:
    virtual bool canDoNextLevel(int levelNum)
    {
        if(LevelSelect::getCurrentLevel()==4)
        {
            if(m_NoNext)
                return false;
        }
        else if(LevelSelect::getCurrentLevel()==5)
        {
            return false;
        }
        return FinishOverlay::canDoNextLevel(levelNum);
    }
    bool m_hasChanged;
    bool m_NoNext;
};



CCLayer* FinishOverlay::createFinish(float time, int peanuts, int points)
{
    if(LevelSelect::getCurrentLevel()<8)
    {
        if(LevelSelect::getCurrentLevel()==5 && !(time > 30.001 || points < 300))
            return new FinishOverlay(time,peanuts,points);
        else
            return new TutorialFinishOverlay(time, peanuts, points);
    }
    else
        return new FinishOverlay(time,peanuts,points);
}


