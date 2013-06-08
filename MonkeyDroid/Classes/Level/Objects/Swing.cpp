//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Swing.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"
#include "../../FrontEnd/SaveLoad.h"
#include "../Level.h"
#include "../../AudioManager.h"
//#import "GameHUD.h"

extern float g_DeltaTime;

using namespace cocos2d;

struct SwingDef
{
    const char *name;
    b2Vec2 colSize;//collision box size
    float swingy;//image offset
    float pivoty; //position of pivot above 0
    b2Vec2 endPos; //offset from bottom left of image
};

static SwingDef s_SwingDefs[Swing::MAX] =
{
    {"ctm_Tiki_FishSwing.png",b2Vec2(0.8f,1.2f),-150.0f,330.0f,b2Vec2(20.0f,40.0f)},
    {"ctm_Tiki_MaskSwing.png",b2Vec2(0.7f,1.0f),-110.0f,270.0f,b2Vec2(15.0f,20.0f)},
    {"ctm_City_Crate.png",b2Vec2(1.8f,1.8f),-110.0f,280.0f,b2Vec2(40.0f,32.0f)},
    {"ctm_City_Tyre.png",b2Vec2(1.5f,1.5f),-110.0f,280.0f,b2Vec2(40.0f,40.0f)},
    {"ctm_Space_Planet_swing.png",b2Vec2(1.8f,1.5f),-100.0f,240.0f,b2Vec2(65.0f,40.0f)},
    {"ctm_Space_Orb_Swing.png",b2Vec2(1.4f,1.4f),-110.0f,270.0f,b2Vec2(33.0f,35.0f)}
};

Swing::Swing(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, int type):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
    
    int bgID = 0;//[GameLevel getlevelDes]->bgID;
    if(bgID==0)//tiki
    {
        m_Type = (RandomInt(0, 100)>50?0:1);
    }
    else if(bgID==1)//city
    {
        m_Type = (RandomInt(0, 100)>50?3:3);
    }
    else if(bgID == 3)//space
    {
        m_Type = (RandomInt(0, 100)>50?4:5);
    }
    else if(bgID == 2)//tiki
    {
        m_Type = (RandomInt(0, 100)>50?3:3);
    }
    else//tiki
    {
        m_Type = (RandomInt(0, 100)>50?0:1);
    }
    
}
Swing::~Swing()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
void Swing::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
    
	box.SetAsBox(s_SwingDefs[m_Type].colSize.x, s_SwingDefs[m_Type].colSize.y);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+0.5);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	m_Exploded = false;
    
    
    m_Pivot = CCNode::create();
    m_ccLayer->addChild(m_Pivot,2);
    m_Swing = CCSprite::createWithSpriteFrameName(s_SwingDefs[m_Type].name);
    m_Swing->setPosition(ccp(0.0f,s_SwingDefs[m_Type].swingy));
    
    m_Pivot->setScale(ScreenHelper::getTextureScale());
    m_Pivot->setPosition(ccp(m_StartPos.x*PTM_RATIO*ScreenHelper::getCameraZoom(),s_SwingDefs[m_Type].pivoty*ScreenHelper::getTextureScale()*ScreenHelper::getCameraZoom()+(m_StartPos.y*PTM_RATIO*ScreenHelper::getCameraZoom())));
    m_Pivot->addChild(m_Swing,0);
    
    m_PivotImage = CCSprite::createWithSpriteFrameName("ctm_SwingPivot_Black.png");
    m_Pivot->addChild(m_PivotImage);
    
    m_Rot = 45.0f;
    m_RotVel = 0.0f;
    m_RotAcc = -40.0f;
    m_waitTime = 0.0f;
    
    m_Pivot->setRotation(m_Rot);
    
    
    m_EndSwing = CCNode::create();
    m_EndSwing->setPosition(ccp(s_SwingDefs[m_Type].endPos.x,s_SwingDefs[m_Type].endPos.y));
    m_Swing->addChild(m_EndSwing);
}
void Swing::DestroySelf()
{
	if(m_created)
	{
        m_Pivot->removeFromParentAndCleanup(true);
		m_world->DestroyBody(m_MainCollision);
	}
}
void Swing::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);

    if(m_created)
    {
        if(m_Rot > 0)
            m_RotAcc = -40.0f;
        else
            m_RotAcc = 40.0f;
        
        float prevRotVel = m_RotVel;
        float zoom = ScreenHelper::getCameraZoom();
        
        m_Pivot->setScale(ScreenHelper::getTextureScale()*zoom);
        m_Pivot->setPosition(ccp(m_StartPos.x*PTM_RATIO*zoom,s_SwingDefs[m_Type].pivoty*ScreenHelper::getTextureScale()*zoom+(m_StartPos.y*PTM_RATIO*zoom)));
        
        m_RotVel += m_RotAcc*g_DeltaTime;
        m_Rot += m_RotVel*g_DeltaTime;
        
        m_Pivot->setRotation(m_Rot);
        
        m_EndPosition = m_Swing->convertToWorldSpace(m_EndSwing->getPosition());
        
        b2Vec2 pos(m_EndPosition.x/(PTM_RATIO*zoom),m_EndPosition.y/(PTM_RATIO*zoom));
        m_MainCollision->SetTransform(pos, m_Rot * (-b2_pi/180.0f));
        
        if((prevRotVel<0&&m_RotVel>0) || (prevRotVel>0&&m_RotVel<0))
        {
            if(m_waitTime<=0.0f)
                m_Exploded = false;
        }
        m_waitTime -= g_DeltaTime;
    }
    
}
bool Swing::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(Rider::g_Pickups>0)
        {
//            CCParticleSystem *emitter = CCParticleSystem::create("SwingPeanutImpact.plist");
//            emitter->setPosition(ccp(m_EndPosition.x,m_EndPosition.y));  // setting emitter position
//            m_ccLayer->addChild(emitter,10);
        }
        
        if(SaveLoad::m_SaveData.peanutLockLevel==0)
            Rider::g_Pickups -= 10;
        if(SaveLoad::m_SaveData.peanutLockLevel==1)
            Rider::g_Pickups -= 20;
        if(SaveLoad::m_SaveData.peanutLockLevel==2)
            Rider::g_Pickups -= 30;
        if(SaveLoad::m_SaveData.peanutLockLevel==3)
            Rider::g_Pickups -= 50;
        
        if(Rider::g_Pickups < 0)
            Rider::g_Pickups = 0;
        
        m_waitTime = 0.75f;
        
        //void Pickup::DoPickupVFX()
        {
                        
            for(int i = 1; i <= 5; i++)
            {
                char tempName[64];
                sprintf(tempName,"ctm_impact_%04d.png",i);
                CCSprite *pop = CCSprite::createWithSpriteFrameName(tempName);
                m_ccLayer->addChild(pop,3);
                
                pop->setPosition(ccp(m_EndPosition.x,m_EndPosition.y));
                pop->setOpacity(0);
                pop->runAction(CCSequence::create(CCDelayTime::create(((float)i)*0.05), CCFadeIn::create(0.01f),CCDelayTime::create(0.04f),CCCallFuncN::create(pop, callfuncN_selector(CCNode::removeFromParentAndCleanup)), NULL));
            }
        }
        
        AudioManager::PlayEffect(AUDIO_SWING_HIT);
        AudioManager::PlayEffect(AUDIO_CHAR_PAIN);
        
        //[Options PlayEffect:AUDIO_SWING_HIT];
		m_Exploded = true;
		return false;
	}
	return false;
}