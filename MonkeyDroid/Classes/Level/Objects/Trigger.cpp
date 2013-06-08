//
//  Trampoline.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Trigger.h"
#include "SimpleAudioEngine.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../FrontEnd/SaveLoad.h"
//#import "FinishParticle.h"
#include "../../AudioManager.h"

USING_NS_CC;

int Trigger::TriggerFlags = 0;

Trigger::Trigger(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, int triggerFlag):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
    m_Flag = triggerFlag;
    m_isTriggered = false;
}
Trigger::~Trigger()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
    
    TriggerFlags &= ~m_Flag;
 
}
void Trigger::CreateSelf()
{
	if(m_created) return;
    
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(1.5f, 1.0f);

	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.0);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    if(m_StartPos.y <= 0.1f)
    {
        TextureObject *tex = new TextureObject((char*)"ctm_Trigger_OFF.png",m_ccLayer,0,true,kTexture2DPixelFormat_Default);
        m_MainCollision->SetUserData(tex);
        tex->SetTextureOffset(0.0f,2.0f);
        
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Trigger_ON.png");
        sprite->setPosition(ccp(59,64));
        sprite->setOpacity(0);
        tex->GetSprite()->addChild(sprite,0,1);
        
        if(m_isTriggered)
        {
            tex->GetSprite()->setOpacity(0);
            sprite->setOpacity(255);
        }
    }
    else
    {
        TextureObject *tex = new TextureObject((char*)"ctm_AirTrigger_OFF.png",m_ccLayer,0,true,kTexture2DPixelFormat_Default);
        m_MainCollision->SetUserData(tex);
        tex->SetTextureOffset(0.0f,0.5f);
        
        CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_AirTrigger_ON.png");
        sprite->setPosition(ccp(32,32));
        sprite->setOpacity(0);
        tex->GetSprite()->addChild(sprite,0,1);
        
        if(m_isTriggered)
        {
            tex->GetSprite()->setOpacity(0);
            sprite->setOpacity(255);
        }
    }
   
}
void Trigger::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
 
}
bool Trigger::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
    
	if(Rider::g_isCrashed) return false;
    if(m_isTriggered) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA  || myFixture == fixtureB)
	{
        if(fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;

        TriggerFlags |= m_Flag;
        
		
        if(!m_isTriggered)
        {
            TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
            texObject->GetSprite()->setOpacity(0);
            ((CCSprite*)texObject->GetSprite()->getChildByTag(1))->setOpacity(255);
            
            AudioManager::PlayEffect(AUDIO_TRIGGER);
        }
        m_isTriggered = true;
		return true;
	}
	
    
	return false;
}