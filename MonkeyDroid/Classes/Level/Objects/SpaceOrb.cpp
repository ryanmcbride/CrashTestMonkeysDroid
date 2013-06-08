//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "SpaceOrb.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"

extern float g_DeltaTime;

using namespace cocos2d;

SpaceOrb::SpaceOrb(b2World *world, CCNode *ccLayer, CCNode* frontLayer, b2Vec2 *startPos):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
    m_frontLayer = frontLayer;
	m_StartPos = *startPos;
}
SpaceOrb::~SpaceOrb()
{
	if(m_created)
	{
        m_Electricity->removeFromParentAndCleanup(true);
        m_LeftOrb->removeFromParentAndCleanup(true);
        m_RightOrb->removeFromParentAndCleanup(true);
        m_LeftOrbGlow->removeFromParentAndCleanup(true);
        m_RightOrbGlow->removeFromParentAndCleanup(true);
    }
}
void SpaceOrb::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	box.SetAsBox(5.5f, 1.0f);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+2.0);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    
    
    m_Electricity = CCSprite::createWithSpriteFrameName("ctm_Space_Electric_01.png");
    m_LeftOrb = CCSprite::createWithSpriteFrameName("ctm_Space_Floating_orb.png");
    m_RightOrb = CCSprite::createWithSpriteFrameName("ctm_Space_Floating_orb.png");
    m_LeftOrbGlow = CCSprite::createWithSpriteFrameName("ctm_Space_Orb_shimmer_01.png");
    m_RightOrbGlow = CCSprite::createWithSpriteFrameName("ctm_Space_Orb_shimmer_01.png");
    
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    m_Electricity->setPosition(ccp(zoom*PTM_RATIO*m_StartPos.x,zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_LeftOrb->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x-6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_RightOrb->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x+6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_LeftOrbGlow->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x-6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_RightOrbGlow->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x+6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    
    m_Electricity->setScale(zoom*scale);
    m_LeftOrb->setScale(zoom*scale);
    m_RightOrb->setScale(zoom*scale);
    m_LeftOrbGlow->setScale(zoom*scale);
    m_RightOrbGlow->setScale(zoom*scale);
    
    
    m_frontLayer->addChild(m_Electricity,2);
    m_frontLayer->addChild(m_LeftOrb,0);
    m_frontLayer->addChild(m_RightOrb,0);
    m_frontLayer->addChild(m_LeftOrbGlow,1);
    m_frontLayer->addChild(m_RightOrbGlow,1);
    
    m_Exploded = false;
    m_LastJump = 10.0f;
    m_waitCounter = 5;
}
void SpaceOrb::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    
    float width = 5.0f;
    
    if(RandomInt(0,5)==1)
    {
        int chance = RandomInt(0,100);
        if(chance<33)
        {
            m_LeftOrbGlow->setVisible(false);
        }
        else if(chance<66)
        {
            m_LeftOrbGlow->removeFromParentAndCleanup(true);
            m_LeftOrbGlow = CCSprite::createWithSpriteFrameName("ctm_Space_Orb_shimmer_01.png");
            m_LeftOrbGlow->setPosition(ccp(PTM_RATIO*(m_StartPos.x-6.0f),PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_LeftOrbGlow,1);
        }
        else
        {
            m_LeftOrbGlow->removeFromParentAndCleanup(true);
            m_LeftOrbGlow = CCSprite::createWithSpriteFrameName("ctm_Space_Orb_shimmer_02.png");
            m_LeftOrbGlow->setPosition(ccp(PTM_RATIO*(m_StartPos.x-6.0f),PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_LeftOrbGlow,1);
        }
    }
    if(RandomInt(0,5)==1)
    {
        int chance = RandomInt(0,100);
        if(chance<33)
        {
            m_RightOrbGlow->setVisible(false);
        }
        else if(chance<66)
        {
            m_RightOrbGlow->removeFromParentAndCleanup(true);
            m_RightOrbGlow = CCSprite::createWithSpriteFrameName("ctm_Space_Orb_shimmer_01.png");
            m_RightOrbGlow->setPosition(ccp(PTM_RATIO*(m_StartPos.x+6.0f),PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_RightOrbGlow ,1);
        }
        else
        {
            m_RightOrbGlow->removeFromParentAndCleanup(true);
            m_RightOrbGlow = CCSprite::createWithSpriteFrameName("ctm_Space_Orb_shimmer_02.png");
            m_RightOrbGlow->setPosition(ccp(PTM_RATIO*(m_StartPos.x+6.0f),PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_RightOrbGlow ,1);
        }
    }
    
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    
    m_waitCounter--;
    if(m_waitCounter<=0 || RandomInt(0,5)==1)
    {
        int chance = RandomInt(0,100);
        if(chance<25)
        {
            m_Electricity->setVisible(false);
        }
        else if(chance<50)
        {
            m_Electricity->removeFromParentAndCleanup(true);
            m_Electricity = CCSprite::createWithSpriteFrameName("ctm_Space_Electric_01.png");
            m_Electricity->setPosition(ccp(PTM_RATIO*m_StartPos.x,PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_Electricity,1);
        }
        else if(chance<75)
        {
            m_Electricity->removeFromParentAndCleanup(true);
            m_Electricity = CCSprite::createWithSpriteFrameName("ctm_Space_Electric_03.png");
            m_Electricity->setPosition(ccp(PTM_RATIO*m_StartPos.x,PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_Electricity,1);
        }
        else
        {
            m_Electricity->removeFromParentAndCleanup(true);
            m_Electricity = CCSprite::createWithSpriteFrameName("ctm_Space_Electric_02.png");
            m_Electricity->setPosition(ccp(PTM_RATIO*m_StartPos.x,PTM_RATIO*(m_StartPos.y+2.0f)));
            m_frontLayer->addChild(m_Electricity,1);
        }
        chance = RandomInt(0,100);
        
        if(chance<25)
        {
            m_Electricity->setScaleX(1.0f*zoom*scale);
            m_Electricity->setScaleY(1.0f*zoom*scale);
        }
        else if(chance<50)
        {
            m_Electricity->setScaleX(-1.0f*zoom*scale);
            m_Electricity->setScaleY(1.0f*zoom*scale);
        }
        else if(chance<75)
        {
            m_Electricity->setScaleX(1.0f*zoom*scale);
            m_Electricity->setScaleY(-1.0f*zoom*scale);
        }
        else
        {
            m_Electricity->setScaleX(-1.0f*zoom*scale);
            m_Electricity->setScaleY(-1.0f*zoom*scale);
        }
        m_waitCounter = 5;
    }
    
    m_Electricity->setPosition(ccp(zoom*PTM_RATIO*m_StartPos.x,zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_LeftOrb->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x-6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_RightOrb->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x+6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_LeftOrbGlow->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x-6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    m_RightOrbGlow->setPosition(ccp(zoom*PTM_RATIO*(m_StartPos.x+6.0f),zoom*PTM_RATIO*(m_StartPos.y+2.0f)));
    
    //m_Electricity->setScale(zoom*scale);
    m_LeftOrb->setScale(zoom*scale);
    m_RightOrb->setScale(zoom*scale);
    m_LeftOrbGlow->setScale(zoom*scale);
    m_RightOrbGlow->setScale(zoom*scale);
    
    if(m_Exploded)
    {
        m_Exploded = false;
        if(Rider::g_MainBody->GetPosition().y < (m_StartPos.y+4.0f))
        {
            if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x-width))
            {
                if(Rider::g_MainBody->GetPosition().x < (m_StartPos.x+width))
                {
                    m_LastJump -= g_DeltaTime;
                    if(m_LastJump <= 0.0f)
                    {
                        if(RandomInt(0,100)>50)
                            Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
                        else
                            Rider::g_MainBody->ApplyTorque(RandomFloat(-50000.0f,-40000.0f));
                        Rider::g_LauchDir.y = 10.0f;
                        Rider::g_LauchDir.x = -Rider::g_MainBody->GetLinearVelocity().x/1.1f;
                        Rider::g_DoLaunch = true;
                        m_LastJump = 0.2f;
                        Rider::g_ScoreManager->AddScore(-100);
                        Rider::g_ScoreManager->FinishTrickGood(false);
                    }
                    m_Exploded = true;
                }
            }
        }
    }
    
}
void SpaceOrb::DestroySelf()
{
	if(m_created)
	{
		m_world->DestroyBody(m_MainCollision);
        m_Electricity->removeFromParentAndCleanup(true);
        m_LeftOrb->removeFromParentAndCleanup(true);
        m_RightOrb->removeFromParentAndCleanup(true);
        m_LeftOrbGlow->removeFromParentAndCleanup(true);
        m_RightOrbGlow->removeFromParentAndCleanup(true);
	}
}

bool SpaceOrb::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
		m_Exploded = true;
        if(RandomInt(0,100)>50)
            Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
        else
            Rider::g_MainBody->ApplyTorque(RandomFloat(-50000.0f,-40000.0f));
        Rider::g_LauchDir.y = 10.0f;
        Rider::g_LauchDir.x = -Rider::g_MainBody->GetLinearVelocity().x/1.1f;
        Rider::g_DoLaunch = true;
        m_LastJump = 0.2f;
        Rider::g_BikeAudio->PushState(BikeAudio::ROUGH);
        Rider::g_ScoreManager->AddScore(-100);
        Rider::g_ScoreManager->FinishTrickGood(false);
		return false;
	}
	return false;
}