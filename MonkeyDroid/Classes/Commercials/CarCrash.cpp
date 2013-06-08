//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "CarCrash.h"
#include "SimpleAudioEngine.h"
#include "../ScreenHelper.h"
#include "../AudioManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

CarCrash::CarCrash()
{
    
    float scale = ScreenHelper::getTextureScale();
    CCSprite *sprite = CCSprite::create("ctm_CraCrashians.png");
    
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(sprite);
    sprite->setScale(scale);
    
    CCSize dim;
    dim.width = 300*scale;
    dim.height = 50*scale;
    CCLabelTTF *weak = CCLabelTTF::create("Weak Nights!","impact.ttf",42*scale);
    weak->setColor(ccc3(237,188,0));
    weak->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_RIGHT, -100, -100));
    weak->setRotation(45);
    weak->setOpacity(0);
    weak->setScale(3.0f);
    weak->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCFadeIn::create(0.1f),NULL));
    weak->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCScaleTo::create(0.1f,1.0f),NULL));
    
    
    CCLabelTTF *weakShadow = CCLabelTTF::create("Weak Nights!","impact.ttf",42*scale);
    weakShadow->setColor(ccc3(0,0,0));
    weakShadow->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_TOP_RIGHT, -100, -97));
    weakShadow->setRotation(45);
    weakShadow->setOpacity(0);
    weakShadow->setScale(3.0f);
    weakShadow->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCFadeIn::create(0.1f),NULL));
    weakShadow->runAction(CCSequence::create(CCDelayTime::create(2.0f),CCScaleTo::create(0.1f,1.0f),NULL));
    
    
    addChild(weakShadow);
    addChild(weak);
    
    m_TimeOut = 5.0f;
    
}
void CarCrash::update(float dt)
{
    Commercial::update(dt);
    if(m_TimeOut <= 3.0f)
    {
        if(m_TimeOut+dt > 3.0f)
        {
            AudioManager::PlayEffect(AUDIO_CHAR_PAIN);
        }
    }
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CTMCarcrashiansMusic.3gp", true);
    
}
CarCrash::~CarCrash()
{
    
}
