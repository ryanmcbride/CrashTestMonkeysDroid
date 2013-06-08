//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "Pause.h"
#include "SimpleAudioEngine.h"
#include "LevelSelect.h"
#include "ScreenHelper.h"
#include "../Level/Level.h"
#include "Loading.h"
#include "../Level/HUD.h"

using namespace cocos2d;
using namespace CocosDenshion;

bool Pause::s_bIsPaused = false;
Pause *Pause::s_pPauseMenu = NULL;

Pause::Pause()
{
    setTouchEnabled( true );

    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Buttons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Buttons.plist");
    
    CCTextureCache::sharedTextureCache()->addPVRImage("ctm_Icons.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_Icons.plist");
    
    CCSprite *sprite = CCSprite::create("Pause_Menu.png");
    sprite->setScaleX(scaleX);
    sprite->setScaleY(scaleY);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,0.0f,0.0f));
    addChild(sprite);
    
    CCMenuItem *BackButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Back_Button.png"), CCSprite::createWithSpriteFrameName("ctm_Back_Button_Down.png"), this, menu_selector(Pause::backButtonTapped));
    BackButton->setScale(scale);
    BackButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_LEFT,0.0f,-50.0f));
    
    CCMenuItem *RestartButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_21.png"), CCSprite::createWithSpriteFrameName("ctm_Button_21_Down.png"), this, menu_selector(Pause::resetButtonTapped));
    RestartButton->setScale(scale);
    RestartButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_LEFT,0.0f,0.0f));
    
    CCMenuItem *LevelSelectButton = CCMenuItemSprite::create(CCSprite::createWithSpriteFrameName("ctm_Button_25.png"), CCSprite::createWithSpriteFrameName("ctm_Button_25_Down.png"), this, menu_selector(Pause::levelButtonTapped));
    LevelSelectButton->setScale(scale);
    LevelSelectButton->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,0.0f,50.0f));
    
    CCMenu* menu = CCMenu::create(BackButton, RestartButton, LevelSelectButton, NULL);
    menu->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT));
    addChild(menu,4);
    
    setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,-100.0f*scaleX,0.0f));
    CCAction *action = CCMoveTo::create(0.2f, ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,64.0f,0.0f));
    runAction(action);
}
void Pause::backButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    Pause::EndPause();
}
void Pause::resetButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    s_bIsPaused = false;
    CCDirector::sharedDirector()->replaceScene(Loading::scene());
}
void Pause::levelButtonTapped(CCObject*object)
{
    SimpleAudioEngine::sharedEngine()->playEffect("Select.wav", false);
    s_bIsPaused = false;
    CCDirector::sharedDirector()->replaceScene(LevelSelect::scene());
}

void Pause::PauseEndAnim()
{
    float scaleX = ScreenHelper::getTextureScaleX();
    
    CCCallFuncN *callRemove = CCCallFuncN::create(this, callfuncN_selector(CCNode::removeFromParentAndCleanup));
    
    CCFiniteTimeAction *action = CCMoveTo::create(0.2f, ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,-100.0f*scaleX,0.0f));
    
    CCSequence *seq = CCSequence::create(action, callRemove, NULL);
    
    runAction(seq);
    s_pPauseMenu = NULL;
    s_bIsPaused = false;
    ((HUD*)m_HUD)->m_Rider->HandlePauseChange(s_bIsPaused);

    //((CCLayer*)m_HUD)->setTouchEnabled( true );
}

Pause::~Pause()
{
    
}


void Pause::BeginPause(cocos2d::CCNode *hudNode)
{
    if(s_bIsPaused) return;
    
    Pause* layer = new Pause();
    ((CCLayer*)hudNode)->setTouchEnabled( false );
    hudNode->getParent()->addChild(layer);
    s_pPauseMenu = layer;
    s_bIsPaused = true;
    s_pPauseMenu->m_HUD = hudNode;
    
    ((HUD*)hudNode)->m_Rider->HandlePauseChange(s_bIsPaused);
}
void Pause::EndPause()
{
    s_pPauseMenu->PauseEndAnim();
}


