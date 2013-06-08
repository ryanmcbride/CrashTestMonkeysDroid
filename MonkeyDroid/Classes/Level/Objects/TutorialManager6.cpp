//
//  TutorialManager.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "TutorialManager6.h"
#include "../Rider/Rider.h"
#include "../Level.h"
#include "Ramp.h"
#include "Platform.h"
#include "Bridge.h"
#include "FinishLine.h"
#include "Pickup.h"
#include "Trigger.h"
#include "../../ScreenHelper.h"


using namespace cocos2d;

extern float g_DeltaTime;
#define TUTORIAL_TAG 0xbadbad

TutorialManager6::TutorialManager6(Track *track, CCNode *backLayer, b2World* world, b2Vec2 *startPos):
TrackObject(startPos->x, 10.0f)
{
    m_world = world;
	m_Track = track;
	m_StartPos = *startPos;
    m_frontLayer = NULL;
    m_State = 0;
    m_backLayer = backLayer;
    m_farWall = NULL;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Tutorial.plist","Tutorial.pvr.ccz");
}
TutorialManager6::~TutorialManager6()
{
	if(m_created)
	{
        
    }
    Trigger::TriggerFlags = 0;
}
void TutorialManager6::CreateSelf()
{
	if(m_created) return;
	m_State = 0;
}
void TutorialManager6::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;

    float scale = ScreenHelper::getTextureScale();
    
    if(m_frontLayer == NULL)
    {
        m_frontLayer = Level::getHUD();
        
        CCNode *main = CCNode::create();
        CCSize dim = CCSizeMake(280*scale, 55*scale);
        CCLabelTTF *label = CCLabelTTF::create("Move Forward","impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
        CCSprite *altText = CCSprite::createWithSpriteFrameName("ctm_Tutorial_Text_Blank.png");
        altText->setOpacity(0.0f);
        altText->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 90, 80));
        label->setPosition(ccp(315.0f/2.0f,110.0f/2.0f));
        altText->addChild(label);
        
        main->addChild(altText);

        m_frontLayer->addChild(main,10,TUTORIAL_TAG);
        
        buttonGlow = NULL;
    }
    
    if(m_State == 0 && xpos/PTM_RATIO > 160)
    {
        m_frontLayer->removeChildByTag(TUTORIAL_TAG,true);
        m_State = 1;
        
        CCNode *main = CCNode::create();
        CCSize dim = CCSizeMake(280*scale, 55*scale);
        CCLabelTTF *label = CCLabelTTF::create("Perform Trick","impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
        CCSprite *altText = CCSprite::createWithSpriteFrameName("ctm_Tutorial_Text_Blank.png");
        altText->setOpacity(0.0f);
        altText->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 90, 80));
        label->setPosition(ccp(315.0f/2.0f,110.0f/2.0f));
        altText->addChild(label);
        
        main->addChild(altText);
        
        m_trickText = altText;

        
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Tutorial_BtnGlow_ver1.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_RIGHT,-44.0f,35.0f));
        main->addChild(sprite);
        
        
        buttonGlow = sprite;
        buttonGlow->setOpacity(0);
        
        sprite = CCSprite::create("TutorialArrow.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_RIGHT,-44.0f,135.0f));
        main->addChild(sprite);
        arrowGlow = sprite;
        arrowGlow->setOpacity(0);
        
        m_frontLayer->addChild(main,10,TUTORIAL_TAG);

    }
    if(buttonGlow)
    {
        if(Rider::g_isInAir && xpos/PTM_RATIO < 360)
        {
            buttonGlow->setOpacity(255);
            arrowGlow->setOpacity(255);
            m_trickText->setVisible(true);
        }
        else
        {
            buttonGlow->setOpacity(0);
            arrowGlow->setOpacity(0);
            m_trickText->setVisible(false);
        }
        if(Rider::g_Score >= 1000)
        {
            m_frontLayer->removeChildByTag(TUTORIAL_TAG,true);
            
            CCNode *main = CCNode::create();
            CCSize dim = CCSizeMake(280*scale, 55*scale);
            CCLabelTTF *label = CCLabelTTF::create("Finish the Level","impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
            CCSprite *altText = CCSprite::createWithSpriteFrameName("ctm_Tutorial_Text_Blank.png");
            altText->setOpacity(0.0f);
            altText->setPosition(ccp(240.0f+90.0f,240.0f));
            label->setPosition(ccp(315.0f/2.0f,110.0f/2.0f));
            altText->addChild(label);
            
            main->addChild(altText);
            
            m_frontLayer->addChild(main,10,TUTORIAL_TAG);
            
            buttonGlow = NULL;
        }
    }
    

    if(Rider::g_isFinished && m_frontLayer)
    {
        m_State = 5;
        m_frontLayer->removeChildByTag(TUTORIAL_TAG,true);
        m_frontLayer = NULL;
    }
    //tutorial follows the action
    m_xpos = xpos/PTM_RATIO;    
}
void TutorialManager6::DestroySelf()
{
	if(m_created)
	{
    }
}
