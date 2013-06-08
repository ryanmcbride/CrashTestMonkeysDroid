//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Barrier.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"
#include "../../AudioManager.h"

using namespace cocos2d;

extern float g_DeltaTime;

Barrier::Barrier(b2World *world, CCNode *ccLayer, CCNode* frontLayer, b2Vec2 *startPos, bool unbreakable):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
    m_frontLayer = frontLayer;
	m_StartPos = *startPos;
    m_Exploded = false;
    m_unbreakable = unbreakable;
}
Barrier::~Barrier()
{
	if(m_created)
	{
        delete (TextureObject*)m_MainCollision->GetUserData();
    }
}
void Barrier::CreateSelf()
{
	if(m_created) return;
	if(m_Exploded) return;
    
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	box.SetAsBox(0.5f, 1.25f);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.25);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    
    
	TextureObject *tex = NULL;
    tex = new TextureObject((char*)"ctm_City_Barrier_Small.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
    m_MainCollision->SetUserData(tex);
    tex->SetTextureOffset(0.75f, 1.0f);
    
    m_Lights = CCSprite::createWithSpriteFrameName("ctm_City_Barrier_Small_Lights.png");
    //m_Lights->setPosition = ccp(PTM_RATIO*(m_StartPos.x+0.75),PTM_RATIO*(m_StartPos.y+2.5f));
    tex->GetSprite()->addChild(m_Lights,2);
    
    m_Exploded = false;
    m_created = true;
    m_LastFlicker = 0.2f;
    m_waitTime = 0.0f;
}
void Barrier::Update(float xpos,float ypos)
{
    if(!m_created && InRange(xpos))
	{
		CreateSelf();
		return;
	}
	
    if(m_created && !InRange(xpos))
    {
		DestroySelf();
		m_created = false;
	    return;
	}
    else
    {
        if(!m_created) return;
        if(m_Exploded) return;
        
        if(m_waitTime>0.0f)
            m_waitTime -= g_DeltaTime;
        
        //do lights
        m_LastFlicker -= g_DeltaTime;
        if(m_LastFlicker <= 0.0f)
        {
            m_Lights->setVisible(!m_Lights->isVisible());
            m_LastFlicker = 0.2f;
        }
    }
}
void Barrier::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
        //[m_Lights removeFromParentAndCleanup:YES];
	}
}

bool Barrier::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(myFixture == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
        {
            b2Vec2 impulse = -fixtureB->GetBody()->GetLinearVelocity();
            impulse.y = RandomFloat(2.0f,10.0f);
            impulse *= fixtureB->GetBody()->GetMass()*1.5f;
            fixtureB->GetBody()->ApplyLinearImpulse(impulse,fixtureB->GetBody()->GetWorldCenter());
                        
            if(fixtureB->GetBody()->GetAngularVelocity()<0.0f)
                fixtureB->GetBody()->ApplyTorque(RandomFloat(30000.0f,35000.0f));
            else
                fixtureB->GetBody()->ApplyTorque(RandomFloat(-35000.0f,-30000.0f));
        }
        else if(myFixture == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
        {
            b2Vec2 impulse = -fixtureA->GetBody()->GetLinearVelocity();
            impulse.y = RandomFloat(2.0f,10.0f);
            impulse *= fixtureA->GetBody()->GetMass()*1.5f;
            fixtureA->GetBody()->ApplyLinearImpulse(impulse,fixtureA->GetBody()->GetWorldCenter());
            
            if(fixtureA->GetBody()->GetAngularVelocity()<0.0f)
                fixtureA->GetBody()->ApplyTorque(RandomFloat(30000.0f,35000.0f));
            else
                fixtureA->GetBody()->ApplyTorque(RandomFloat(-35000.0f,-30000.0f));
        }
        else if(m_waitTime<=0.0f)
        {
            if(RandomInt(0,100)>50)
                Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
            else
                Rider::g_MainBody->ApplyTorque(RandomFloat(-50000.0f,-40000.0f));
            
            
            if(m_unbreakable)
            {
                Rider::g_LauchDir.y = 1.0f;
                Rider::g_LauchDir.x = Rider::g_MainBody->GetLinearVelocity().x>0.0f?-40.0f:40.0f;
                Rider::g_BikeAudio->PushState(BikeAudio::ROUGH);
            }
            else
            {
                Rider::g_LauchDir.y = 10.0f;
                Rider::g_LauchDir.x = -Rider::g_MainBody->GetLinearVelocity().x/1.1f;
            }
            Rider::g_DoLaunch = true;
            //m_waitTime = 0.5f;
        }
        AudioManager::PlayEffect(AUDIO_BIKE_HARD_IMPACT);
        
        if(!m_unbreakable)
        {
            m_Exploded = true;
            TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
            texObject->GetSprite()->setVisible(false);
            //m_Lights.visible = NO;
        }
		return false;
	}
	return false;
}