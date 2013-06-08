//
//  CrashOverlay.mm
//  CTM
//
//  Created by Ryan McBride on 6/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "ScoreManager.h"
#include "Rider/Rider.h"
#include "../FrontEnd/SaveLoad.h"
#include "HUD.h"
#include "../AudioManager.h"
#include "../ScreenHelper.h"
#include "../FrontEnd/Achievements.h"

extern bool g_is60;
extern bool g_PermanentFire;
extern int g_TutorialState;

using namespace cocos2d;

ScoreManager::ScoreManager()
{
    m_flamingLabel = NULL;
    m_trickLabel = NULL;
    m_flipLabel = NULL;
    m_ofFireLabel = NULL;
    
    m_bFlaming = false;
    m_iTrick = 0;
    m_iFlips = 0;
    m_iLoops = 0;
    m_bOfFire = false;
    
    m_time = -1.0f;
    trickReady = true;
    
    trickString[0] = '\0';
    
    m_TrickNode = CCNode::create();
    
    m_TrickNode->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER, 0.0f, 70.0f));
    addChild(m_TrickNode);
    scheduleUpdate();
}
ScoreManager::~ScoreManager()
{
}

int ScoreManager::GetTrick()
{
    return m_iTrick;
}
int ScoreManager::GetFlips()
{
    return m_iFlips;
}

void ScoreManager::SetTrick(int tricknum)
{
    //if(!trickReady) return;
    //trickReady = false;

    if(m_time > 0.0f) return;
    
    float scale = ScreenHelper::getTextureScale();
    
    if(m_iTrick < 3)
    {
        if(m_iTrick==0)
            trickString[0] = '\0';
        else
            strcat(trickString, "+");
        switch(tricknum)
        { 
            case 1:
                if(SaveLoad::m_SaveData.trickLockLevel == 3 )
                    strcat(trickString,"Bowling");
                else if(SaveLoad::m_SaveData.trickLockLevel == 2 )
                    strcat(trickString,"Disco");
                else if(SaveLoad::m_SaveData.trickLockLevel == 1)
                    strcat(trickString,"Banana Split");
                else
                    strcat(trickString,"Flying Monkey");
                break;
            case 2:
                if(SaveLoad::m_SaveData.trickLockLevel == 3 )
                    strcat(trickString,"SuperMonkey");
                else if(SaveLoad::m_SaveData.trickLockLevel == 2)
                    strcat(trickString,"Seat Grab");
                else if(SaveLoad::m_SaveData.trickLockLevel == 1)
                    strcat(trickString,"Hand Stand");
                else
                    strcat(trickString,"No Seat");
                break;
            case 3:
                if(SaveLoad::m_SaveData.trickLockLevel == 3 )
                    strcat(trickString,"Jelly Roll");
                else if(SaveLoad::m_SaveData.trickLockLevel == 2)
                    strcat(trickString,"Bowling");
                else if(SaveLoad::m_SaveData.trickLockLevel == 1)
                    strcat(trickString,"Disco");
                else
                    strcat(trickString,"Banana Split");
                break;
        }
        if(m_iTrick==0)
        {
            CCSize dim;
            dim.width = 400.0f*scale;
            dim.height = 25.0f*scale;
            m_trickLabel = CCLabelTTF::create(trickString, "Jacoby ICG Black.ttf", 20*scale,dim,kCCTextAlignmentCenter);
            m_trickLabel->setColor(ccc3(230,230,230));
            m_trickLabel->setPosition(ccp(0.0f,10.0f*scale));
            m_TrickNode->addChild(m_trickLabel);
        }
        else
        {
            m_trickLabel->setString(trickString);
        }
        
        m_iTrick++;
        
        if(m_iFlips>0)
            AudioManager::PlayEffect(AUDIO_CHAR_TRICK_FLIP);
        else
            AudioManager::PlayEffect(AUDIO_CHAR_TRICK_NO_FLIP);
        
        SetFire();
    }
    else if(m_iTrick == 3)
    {
        sprintf(trickString,"SuperTrick");
        m_trickLabel->setString(trickString);
        m_iTrick++;
    }
}
void ScoreManager::SetFlips(int flips)
{
    if(m_time > 0.0f) return;

    float scale = ScreenHelper::getTextureScale();
    
    ccColor3B rgb;
    rgb.r = 0;
    rgb.g = 188;
    rgb.b = 237;
    const char *flipString;
    switch(flips)
    {
        default:
            flipString = "UltraFlip";
            break;
        case 1:
            flipString = "Flip";
            break;
        case 2:
            flipString = "2XFlip";
            rgb.g = 40;
            break;
        case 3:
            flipString = "3XFlip";
            break;
        case 4:
            flipString = "4XFlip";
            rgb.g = 40;
            break;
        case 5:
            flipString = "5XFlip";
            break;
        case 6:
            flipString = "6XFlip";
            rgb.g = 40;
            break;
        case 7:
            flipString = "7XFlip";
            break;
        case 8:
            flipString = "8XFlip";
            rgb.g = 40;
            break;
    }
    if(m_flipLabel != NULL)
    {
        m_flipLabel->removeFromParentAndCleanup(true);
    }
    //else
    {
        CCSize dim;
        dim.width = 200.0f*scale;
        dim.height = 25.0f*scale;
        m_flipLabel = CCLabelTTF::create(flipString,"Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentCenter);
        m_flipLabel->setColor(ccc3(rgb.r,rgb.g,rgb.b));
        m_flipLabel->setPosition(ccp(0.0f,-10.0f*scale));
        m_TrickNode->addChild(m_flipLabel);
    }
    if(flips <= 9)
        m_iFlips = flips;
    
    SetFire();
}
void ScoreManager::SetLoops(int loops)
{
    if(m_time > 0.0f) return;

    float scale = ScreenHelper::getTextureScale();
    
    if(m_flipLabel != NULL)
        m_flipLabel->removeFromParentAndCleanup(true);
    
    
    const char *flipString = NULL;
    if(loops == 3)
        flipString = "Triple Loop";
    else if(loops == 2)
        flipString = "Double Loop";
    else
        flipString = "Loop";
    
    CCSize dim;
    dim.width = 200.0f*scale;
    dim.height = 25.0f*scale;
    m_flipLabel  = CCLabelTTF::create(flipString,"Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentCenter);
    m_flipLabel->setColor(ccc3(0,188,237));
    m_flipLabel->setPosition(ccp(0.0f,-10.0f*scale));
    m_TrickNode->addChild(m_flipLabel);
    
    m_iLoops = loops;
    
    SetFire();
}
void ScoreManager::SetFire()
{
    if(m_time > 0.0f) return;

    float scale = ScreenHelper::getTextureScale();

    if(!m_bFlaming && Rider::g_OnFire>0.0f)
    {
        
        CCSize dim;
        dim.width = 200.0f*scale;
        dim.height = 25.0f*scale;
        m_flamingLabel = CCLabelTTF::create("Flaming","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentCenter);
        m_flamingLabel->setColor(ccc3(237,30,30));
        m_flamingLabel->setPosition(ccp(0.0f,30.0f*scale));
        m_TrickNode->addChild(m_flamingLabel);
        m_bFlaming = true;
    }
    
    if(!m_bOfFire && g_PermanentFire)
    {
        CCSize dim;
        dim.width = 200.0f*scale;
        dim.height = 25.0f*scale;
        m_ofFireLabel  = CCLabelTTF::create("of Fire!","Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentCenter);
        m_ofFireLabel->setColor(ccc3(237,30,30));
        m_ofFireLabel->setPosition(ccp(0.0f,-30.0f*scale));
        m_TrickNode->addChild(m_ofFireLabel);
        m_bOfFire = true;
    }
}
bool ScoreManager::DuringLockout()
{
    if(m_time > 0.0f) return true;
    return false;
}
void ScoreManager::FinishTrickGood(bool goodBad)
{
    if(goodBad)
    {
         if(m_time > 0.0f) return;
        int score = 0;
        if(m_iLoops)
        {
            if(SaveLoad::m_SaveData.trickLockLevel>=3)
                score = (m_iTrick?500*m_iTrick:50);
            else if(SaveLoad::m_SaveData.trickLockLevel>=2)
                score = (m_iTrick?300*m_iTrick:50);
            else if(SaveLoad::m_SaveData.trickLockLevel>=1)
                score = (m_iTrick?200*m_iTrick:50);
            else
                score = (m_iTrick?100*m_iTrick:50);
            
            score *= (m_bFlaming?2:1)*(m_iLoops?m_iLoops:1);
            score *= (m_bOfFire?2:1);
            AddScore(score);
        }
        else if(m_iFlips || m_iTrick)
        {
            if(SaveLoad::m_SaveData.trickLockLevel>=3)
                score = (m_iTrick?500*m_iTrick:50);
            else if(SaveLoad::m_SaveData.trickLockLevel>=2)
                score = (m_iTrick?300*m_iTrick:50);
            else if(SaveLoad::m_SaveData.trickLockLevel>=1)
                score = (m_iTrick?200*m_iTrick:50);
            else
                score = (m_iTrick?100*m_iTrick:50);
            score *= (m_bFlaming?2:1)*(m_iFlips?(m_iFlips+1):1);
            score *= (m_bOfFire?2:1);
            AddScore(score);
            
            if(m_bFlaming && m_bOfFire && m_iTrick>=4 && m_iFlips >= 9)
            {
                if(SaveLoad::m_SaveData.objectives[SaveLoad::OMGWTFBBQ_FTW]==0)
                {
                    Achievements::EarnAchievement(this->getParent(),SaveLoad::OMGWTFBBQ_FTW);
                }
            }
            if(m_iFlips >= 9)
            {
                if(SaveLoad::m_SaveData.objectives[SaveLoad::ITS_OVER_9000]==0)
                {
                    Achievements::EarnAchievement(this->getParent(),SaveLoad::ITS_OVER_9000);
                }
            }
        }
        
        if(score > 0.0f)
        {
            m_time = 0.5f;
            
            ccColor3B rgb;
            rgb.r = 237;
            rgb.g = 188;
            rgb.b = 0;
            
            if(m_flipLabel != NULL)
                m_flipLabel->setColor(ccc3(rgb.r,rgb.g,rgb.b));
            if(m_trickLabel != NULL)
            {
                float scale = ScreenHelper::getTextureScale();
                m_trickLabel->removeFromParentAndCleanup(true);
                CCSize dim;
                dim.width = 400.0f*scale;
                dim.height = 25.0f*scale;
                m_trickLabel = CCLabelTTF::create(trickString,"Jacoby ICG Black.ttf",20*scale,dim,kCCTextAlignmentCenter);
                m_trickLabel->setColor(ccc3(rgb.r,rgb.g,rgb.b));
                m_trickLabel->setPosition(ccp(0.0f,10.0f));
                m_TrickNode->addChild(m_trickLabel);
            }
            if(m_flamingLabel != NULL)
                m_flamingLabel->setColor(ccc3(rgb.r,rgb.g,rgb.b));
            if(m_ofFireLabel != NULL)
                m_ofFireLabel->setColor(ccc3(rgb.r,rgb.g,rgb.b));
        }
        else
        {
            if(m_flipLabel != NULL)
                m_flipLabel->removeFromParentAndCleanup(true);
            if(m_trickLabel != NULL)
                m_trickLabel->removeFromParentAndCleanup(true);
            if(m_flamingLabel != NULL)
                m_flamingLabel->removeFromParentAndCleanup(true);
            if(m_ofFireLabel != NULL)
                m_ofFireLabel->removeFromParentAndCleanup(true);
            
            m_flipLabel = NULL;
            m_trickLabel = NULL;
            m_flamingLabel = NULL;
            m_ofFireLabel = NULL;
            
            m_bFlaming = false;
            m_bOfFire = false;
            m_iFlips = 0;
            m_iTrick = 0;
            m_iLoops = 0;
        }
    }
    else
    {
        if(m_flipLabel != NULL)
            m_flipLabel->removeFromParentAndCleanup(true);
        if(m_trickLabel != NULL)
            m_trickLabel->removeFromParentAndCleanup(true);
        if(m_flamingLabel != NULL)
            m_flamingLabel->removeFromParentAndCleanup(true);
        if(m_ofFireLabel != NULL)
            m_ofFireLabel->removeFromParentAndCleanup(true);
        
        m_flipLabel = NULL;
        m_trickLabel = NULL;
        m_flamingLabel = NULL;
        m_ofFireLabel = NULL;
        
        m_bFlaming = false;
        m_bOfFire = false;
        m_iFlips = 0;
        m_iTrick = 0;
        m_iLoops = 0;
        Rider::s_Vehicle->resetFlipCount();
    }
    
}
void ScoreManager::update(float dt)
{
    if(m_time > 0.0f)
    {
        m_time -= dt;
        if(m_time <= 0.0f)
        {
            if(m_flipLabel != NULL)
                m_flipLabel->removeFromParentAndCleanup(true);
            if(m_trickLabel != NULL)
                m_trickLabel->removeFromParentAndCleanup(true);
            if(m_flamingLabel != NULL)
                m_flamingLabel->removeFromParentAndCleanup(true);
            if(m_ofFireLabel != NULL)
                m_ofFireLabel->removeFromParentAndCleanup(true);
            
            m_flipLabel = NULL;
            m_trickLabel = NULL;
            m_flamingLabel = NULL;
            m_ofFireLabel = NULL;
            
            m_bFlaming = false;
            m_bOfFire = false;
            m_iFlips = 0;
            m_iTrick = 0;
            m_iLoops = 0;
            m_TrickNode->setScale(1.0f);
        }
    }
    //if(!trickReady && Rider::g_TrickState==0)
    //    trickReady = true;
}

void ScoreManager::AddScore(int score)
{
    if(Rider::g_isFinished) return;
    
    Rider::g_Score += score;

    float scale = ScreenHelper::getTextureScale();
    
    CCSize dim;
    dim.width = 290.0f*scale;
    dim.height = 75.0f*scale;
    ccColor3B fillColor = ccc3(237,188,0);
    if(score < 0)
    {
        FinishTrickGood(false);
        AudioManager::PlayEffect(AUDIO_CHAR_PAIN);
        fillColor = ccc3(237,30,30);
        
//RPM        if(g_TutorialState && g_TutorialState < 6)
//            fillColor.a = 0;
    }
    char temp[32];
    sprintf(temp,"%d Points!",score);
    CCLabelTTF *label = CCLabelTTF::create(temp,"Jacoby ICG Black.ttf",24*scale,dim,kCCTextAlignmentCenter);
    label->setColor(fillColor);
    label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_CENTER, 0.0f, 10.0f));
    
    CCSequence *sequence = CCSequence::create(CCDelayTime::create(0.5f),
                            CCCallFuncN::create(label, callfuncN_selector(CCNode::removeFromParentAndCleanup)),
                            NULL);
    label->runAction(sequence);
    addChild(label);
}

