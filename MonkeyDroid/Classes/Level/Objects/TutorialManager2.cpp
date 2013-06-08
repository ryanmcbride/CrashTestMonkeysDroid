//
//  TutorialManager.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "TutorialManager2.h"
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

TutorialManager2::TutorialManager2(Track *track, CCNode *backLayer, b2World* world, b2Vec2 *startPos):
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
TutorialManager2::~TutorialManager2()
{
	if(m_created)
	{
        
    }
    Trigger::TriggerFlags = 0;
}
void TutorialManager2::CreateSelf()
{
	if(m_created) return;
	m_State = 0;
}
void TutorialManager2::Update(float xpos,float ypos)
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
        
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Tutorial_BtnGlow_ver1.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,115.0f,35.0f));
        main->addChild(sprite);
        
        m_frontLayer->addChild(main,10,TUTORIAL_TAG);

    }
    if(m_State == 0 && (Trigger::TriggerFlags & 1))
    {
        m_frontLayer->removeChildByTag(TUTORIAL_TAG,true);
        
        CCNode *main = CCNode::create();
        CCSize dim = CCSizeMake(280*scale, 55*scale);
        CCLabelTTF *label = CCLabelTTF::create("Move Backward","impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
        CCSprite *altText = CCSprite::createWithSpriteFrameName("ctm_Tutorial_Text_Blank.png");
        altText->setOpacity(0.0f);
        altText->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 90, 80));
        label->setPosition(ccp(315.0f/2.0f,110.0f/2.0f));
        altText->addChild(label);
        
        main->addChild(altText);
        
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Tutorial_BtnGlow_ver1.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,45.0f,35.0f));
        main->addChild(sprite);
        
        m_frontLayer->addChild(main,10,TUTORIAL_TAG);
        m_State = 1;
    }
    
    if(m_State == 1 && (Trigger::TriggerFlags & 2))
    {
        m_frontLayer->removeChildByTag(TUTORIAL_TAG,true);
        
        CCNode *main = CCNode::create();
        CCSize dim = CCSizeMake(280*scale, 55*scale);
        CCLabelTTF *label = CCLabelTTF::create("Move Forward","impact.ttf",32*scale,dim,kCCTextAlignmentCenter);
        CCSprite *altText = CCSprite::createWithSpriteFrameName("ctm_Tutorial_Text_Blank.png");
        altText->setOpacity(0.0f);
        altText->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 90, 80));
        label->setPosition(ccp(315.0f/2.0f,110.0f/2.0f));
        altText->addChild(label);
        
        main->addChild(altText);
        
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Tutorial_BtnGlow_ver1.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT,115.0f,35.0f));
        main->addChild(sprite);
        
        m_frontLayer->addChild(main,10,TUTORIAL_TAG);
        m_State = 2;
    }
    
    if(Rider::g_isFinished && m_frontLayer)
    {
        m_frontLayer->removeChildByTag(TUTORIAL_TAG,true);
        m_frontLayer = NULL;
    }
    //tutorial follows the action
    m_xpos = xpos/PTM_RATIO;    
}
void TutorialManager2::DestroySelf()
{
	if(m_created)
	{
    }
}
