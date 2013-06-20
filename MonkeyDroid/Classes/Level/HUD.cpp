//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "HUD.h"
#include "SimpleAudioEngine.h"
#include "../FrontEnd/MainMenu.h"
#include "../ScreenHelper.h"
#include "../AudioManager.h"
#include "../FrontEnd/LevelSelect.h"
#include "../FrontEnd/Pause.h"
#include "../FrontEnd/SaveLoad.h"
#include "CrashOverlay.h"
#include "ScoreManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

extern bool g_isTrickLevel;
extern bool g_SlowClock;

class TrickButtonMenuItem : public CCMenuItemSprite
{
public:
    TrickButtonMenuItem()
    {
        m_ButtonIsDown = false;
    }
    virtual void selected()
    {
        m_ButtonIsDown = true;
        CCMenuItemSprite::selected();
    }
    virtual void unselected()
    {
        m_ButtonIsDown = false;
        CCMenuItemSprite::unselected();
    }
    bool m_ButtonIsDown;    
};

HUD::HUD()
{
    setTouchEnabled( true );
    setAccelerometerEnabled(true);
    
    int currentLevel = LevelSelect::getCurrentLevel();
    float scale = ScreenHelper::getTextureScale();
    //float scaleX = ScreenHelper::getTextureScaleX();
    //float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
    
    m_startPrompt = CCNode::create();
    addChild(m_startPrompt,2);
    
    CCLabelTTF *label;
    if(currentLevel==4)
    {
        label = CCLabelTTF::create("Finish the level in less\nthan 30 seconds", "impact.ttf", 25*scale);
        m_startPrompt->addChild(label, 2);
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,58.0f));
        
        
        label = CCLabelTTF::create("Move Forward to Start", "impact.ttf", 35*scale);
        m_startPrompt->addChild(label, 2);
        label->setColor(ccc3(0,0,0));
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,8.0f));
        
        label = CCLabelTTF::create("Move Forward to Start", "impact.ttf", 35*scale);
        m_startPrompt->addChild(label, 2);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,10.0f));
    }
    else if(currentLevel==5)
    {
        label = CCLabelTTF::create("Finish the level in less\nthan 30 seconds\nAnd with 300 points\nto earn a medal", "impact.ttf", 25*scale);
        m_startPrompt->addChild(label, 2);
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,73.0f));
        
        
        label = CCLabelTTF::create("Move Forward to Start", "impact.ttf", 35*scale);
        m_startPrompt->addChild(label, 2);
        label->setColor(ccc3(0,0,0));
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,-12.0f));
        
        label = CCLabelTTF::create("Move Forward to Start", "impact.ttf", 35*scale);
        m_startPrompt->addChild(label, 2);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,-10.0f));
    }
    else if(currentLevel > 5)
    {
        label = CCLabelTTF::create("Move Forward to Start", "impact.ttf", 35*scale);
        m_startPrompt->addChild(label, 2);
        label->setColor(ccc3(0,0,0));
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,2.0f,38.0f));
        
        label = CCLabelTTF::create("Move Forward to Start", "impact.ttf", 35*scale);
        m_startPrompt->addChild(label, 2);
        label->setColor(ccc3(237,188,0));
        label->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,40.0f));
        
        
        if(currentLevel==8 && !(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::HINT_DISPLAY))
        {
            CCTextureCache::sharedTextureCache()->addPVRImage("Hints.pvr.ccz");
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Hints.plist");
            CCSprite *hintsprite = CCSprite::createWithSpriteFrameName("Hints_EarnMedals_Tiki.png");
            hintsprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            hintsprite->setScale(2.0f);
            addChild(hintsprite,10);
            hintsprite->runAction(CCSequence::create(CCDelayTime::create(5.0f),CCCallFuncN::create(hintsprite, callfuncN_selector(CCNode::removeFromParentAndCleanup)),NULL));
            //SaveLoad::m_SaveData.levelflags[currentLevel] |= SaveLoad::HINT_DISPLAY;
        }
        if(currentLevel==16 && !(SaveLoad::m_SaveData.levelflags[currentLevel] & SaveLoad::HINT_DISPLAY))
        {
            CCTextureCache::sharedTextureCache()->addPVRImage("Hints.pvr.ccz");
            CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Hints.plist");
            CCSprite *hintsprite = CCSprite::createWithSpriteFrameName("Hints_EarnMedals_City.png");
            hintsprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
            hintsprite->setScale(2.0f);
            addChild(hintsprite,10);
            hintsprite->runAction(CCSequence::create(CCDelayTime::create(5.0f),CCCallFuncN::create(hintsprite, callfuncN_selector(CCNode::removeFromParentAndCleanup)),NULL));
            //SaveLoad::m_SaveData.levelflags[currentLevel] |= SaveLoad::HINT_DISPLAY;
        }
    }
    
    
    CCMenuItem *PauseButton = CCMenuItemSprite::create(CCSprite::create("ctm_UI_Pause_Btn_ver1.png"), CCSprite::create("ctm_UI_Pause_Btn_ver1_down.png"), this, menu_selector(HUD::pauseButtonTapped));
    PauseButton->setScale(scale);
    PauseButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,30.0f,-30.0f));
    
    CCMenuItem *FWDButton = CCMenuItemSprite::create(CCSprite::create("ctm_UI_Forward_Btn_ver1.png"), CCSprite::create("ctm_UI_Forward_Btn_ver1_down.png"), this, menu_selector(HUD::fwdButtonTapped));
    FWDButton->setScale(scale);
    FWDButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,120.0f,30.0f));
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::create("ctm_UI_Backward_Btn_ver1.png"), CCSprite::create("ctm_UI_Backward_Btn_ver1_down.png"), this, menu_selector(HUD::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,50.0f,30.0f));
    
     
    TrickButtonMenuItem *JumpButton = new TrickButtonMenuItem();
    JumpButton->initWithNormalSprite(CCSprite::create("ctm_UI_Jump_Btn_ver1.png"), CCSprite::create("ctm_UI_Jump_Btn_ver1_down.png"), NULL, this, menu_selector(HUD::jumpButtonTapped));
    JumpButton->autorelease();
    JumpButton->setScale(scale);
    JumpButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,-50.0f,30.0f));
    
    
    /*CCMenuItemFont *crash = CCMenuItemFont::create("crash", this, menu_selector(HUD::crashButtonTapped));
    crash->setScale(scale);
    crash->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-50.0f,30.0f));

    CCMenuItemFont *finish = CCMenuItemFont::create("finish", this, menu_selector(HUD::finishButtonTapped));
    finish->setScale(scale);
    finish->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,50.0f,-30.0f));
*/
    
    CCMenu* menu = CCMenu::create(PauseButton, FWDButton, BackButton, /*crash, finish,*/ NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    menu->setContentSize(CCSizeMake(10,10));
    
    CCMenu* jumpmenu = CCMenu::create(JumpButton, NULL);
    jumpmenu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_RIGHT));
    addChild(jumpmenu,4);
    jumpmenu->setContentSize(CCSizeMake(10,10));
    
    m_ForwardButton = FWDButton;
    m_BackwardButton = BackButton;
    m_JumpButton = JumpButton;
    
    m_fTrickButtonDelay = -1.0f;
    
    m_bIsInFinishSequence = false;
    
    
    
    CCLabelBMFont *time = CCLabelBMFont::create("Time:","JacobyICGBlack18pnt.fnt");
    time->setScale(scale);
    if(g_SlowClock)
        time->setColor(ccc3(170,220,170));
    else
        time->setColor(ccc3(237,188,0));
    time->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT, 80, -20.0f));
    addChild(time);
    
    
    if(currentLevel == BONUS_LEVELSTART)
        m_Time = 45.0f;
    if(currentLevel == BONUS_LEVELSTART+1)
        m_Time = 60.0f;
    if(currentLevel == BONUS_LEVELSTART+2)
        m_Time = 75.0f;
    if(currentLevel == BONUS_LEVELSTART+3)
        m_Time = 90.0f;
    else
        m_Time = 0.0f;
    
    char timeChar[16];
    sprintf(timeChar,"%.2f",m_Time);
    m_TimeString = CCLabelBMFont::create(timeChar,"JacobyICGBlack18pnt.fnt",70,kCCTextAlignmentLeft);
    m_TimeString->setScale(scale);
    m_TimeString->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT, 125, -20.0f));
    if(g_SlowClock)
        m_TimeString->setColor(ccc3(190,240,190));
    addChild(m_TimeString);
    
    
    
    CCLabelBMFont *peanuts = CCLabelBMFont::create("Peanuts:","JacobyICGBlack18pnt.fnt");
    peanuts->setScale(scale);
    peanuts->setColor(ccc3(237,188,0));
    peanuts->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER, -10, -20.0f));
    addChild(peanuts);
    char nutChar[16];
    sprintf(nutChar,"%d",Rider::g_Pickups);
    m_PeanutString = CCLabelBMFont::create(nutChar,"JacobyICGBlack18pnt.fnt",70,kCCTextAlignmentLeft);
    m_PeanutString->setScale(scale);
    m_PeanutString->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_CENTER, 35, -20.0f));
    addChild(m_PeanutString);
    
    
    
    CCLabelBMFont *points = CCLabelBMFont::create("Points:","JacobyICGBlack18pnt.fnt");
    points->setScale(scale);
    points->setColor(ccc3(237,188,0));
    points->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_RIGHT, -120, -20.0f));
    addChild(points);
    char pointChar[16];
    sprintf(pointChar,"%d",Rider::g_Score);
    m_PointString = CCLabelBMFont::create(pointChar,"JacobyICGBlack18pnt.fnt",70,kCCTextAlignmentLeft);
    m_PointString->setScale(scale);
    m_PointString->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_RIGHT, -85, -20.0f));
    addChild(m_PointString);
    
    if(currentLevel < 3)
    {
        points->setVisible(false);
        m_PointString->setVisible(false);
    }
    if(currentLevel < 2)
    {
        m_PeanutString->setVisible(false);
        peanuts->setVisible(false);
    }
    if(currentLevel < 4)
    {
        time->setVisible(false);
        m_TimeString->setVisible(false);        
    }
    
    
    Rider::g_ScoreManager = new ScoreManager();
    addChild(Rider::g_ScoreManager,11);
    Rider::g_ScoreManager->autorelease();
    
    scheduleUpdate();
}

void HUD::update(float dt)
{
    if(m_ForwardButton->isSelected())
    {
        m_Rider->GasAndBrake(1.0f);
        if(m_startPrompt)
        {
            m_startPrompt->removeFromParentAndCleanup(true);
            m_startPrompt = NULL;
        }
	}
    else if(m_BackwardButton->isSelected())
    {
        m_Rider->GasAndBrake(-1.0f);
        if(m_startPrompt)
        {
            m_startPrompt->removeFromParentAndCleanup(true);
            m_startPrompt = NULL;
        }
    }
    else
    {
        m_Rider->GasAndBrake(0.0f);
    }
    
    if(m_fTrickButtonDelay>=0.0f)
        m_fTrickButtonDelay -= dt;
    
    if(((TrickButtonMenuItem *)m_JumpButton)->m_ButtonIsDown)
    {
        if(m_fTrickButtonDelay < 0.0f && Rider::s_bWheelsTouch && !Rider::g_isInAir && !Rider::g_inLoop )
        {
            Rider::s_bWheelsTouch = false;
            float xvel = Rider::g_MainBody->GetLinearVelocity().x;
            Rider::g_LauchDir.x = xvel;
            Rider::g_LauchDir.y = 20.0f;
            Rider::g_DoLaunch = true;
            AudioManager::PlayEffect(AUDIO_CHAR_JUMP,0.33f);
            m_fTrickButtonDelay = 0.5f;
        }
        else
        {
            //if(!g_TutorialState || g_TutorialState > 5)
            //    [((GameLevel*)m_GameLayer) doTrick];
            
            m_Rider->Trick((int)((CCRANDOM_0_1()*29)+10.0f)/10);
        }
        ((TrickButtonMenuItem *)m_JumpButton)->m_ButtonIsDown = false;
    }
    
    if(!m_startPrompt)
    {
        if(!Pause::s_bIsPaused)
        {
            if(g_isTrickLevel)
            {
                if(g_SlowClock)
                    m_Time -= (dt*0.75f);
                else
                    m_Time -= dt;
            }
            else
            {
                if(g_SlowClock)
                    m_Time += (dt*0.75f);
                else
                    m_Time += dt;
            }
        }
        char timeChar[16];
        sprintf(timeChar,"%.2f",m_Time);
        m_TimeString->setString(timeChar,true);
    }
    char nutChar[16];
    sprintf(nutChar,"%d",Rider::g_Pickups);
    m_PeanutString->setString(nutChar,true);
    
    char pointChar[16];
    sprintf(pointChar,"%d",Rider::g_Score);
    m_PointString->setString(pointChar,true);
}

void HUD::pauseButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    //CCDirector::sharedDirector()->replaceScene(LevelSelect::scene());
    if(!Pause::s_bIsPaused)
        Pause::BeginPause(this);
    else
        Pause::EndPause();
}

void HUD::fwdButtonTapped(CCObject*object)
{
    if(!this->isTouchEnabled())return;
}
void HUD::backButtonTapped(CCObject*object)
{
    if(!this->isTouchEnabled())return;
}
void HUD::jumpButtonTapped(CCObject*object)
{
    if(!this->isTouchEnabled())return;
}

void HUD::finishButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}
void HUD::crashButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
}

void HUD::didAccelerate(cocos2d::CCAcceleration* pAccelerationValue)
{
    m_Rider->AirSpin(-pAccelerationValue->x);
    
}

void HUD::startCrashSequence()
{
    if(m_bIsInFinishSequence)return;
    m_bIsInFinishSequence = true;
    this->setVisible(false);
    CrashOverlay *overlay = new CrashOverlay(m_Time,Rider::g_Pickups,Rider::g_Score);
    this->getParent()->addChild(overlay);
}
void HUD::startFinishSequence()
{
    if(m_bIsInFinishSequence)return;
    m_bIsInFinishSequence = true;
    this->setVisible(false);
    this->getParent()->addChild(FinishOverlay::createFinish(m_Time,Rider::g_Pickups,Rider::g_Score));
}


HUD::~HUD()
{
    
}

