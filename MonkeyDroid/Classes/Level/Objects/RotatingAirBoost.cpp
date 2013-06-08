//
//  Trampoline.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "RotatingAirBoost.h"
#include "SimpleAudioEngine.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../FrontEnd/SaveLoad.h"
//#import "FinishParticle.h"
#include "../../AudioManager.h"

using namespace cocos2d;

RotatingAirBoost::RotatingAirBoost(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float minrotation, float maxrotation, float rotspeed):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
    m_Rotation = minrotation;
    m_MinRot = minrotation;
    m_MaxRot = maxrotation;
    m_RotationSpeed = rotspeed;
}
RotatingAirBoost::~RotatingAirBoost()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
void RotatingAirBoost::CreateSelf()
{
	if(m_created) return;
    
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(1.5f, 1.5f);

	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.5);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	TextureObject *tex = new TextureObject((char*)"ctm_AirBoost.png",m_ccLayer,0,true,kTexture2DPixelFormat_RGBA4444);
	m_MainCollision->SetUserData(tex);
	tex->SetTexturePosition(m_StartPos.x, m_StartPos.y+1.5f);
    m_LauchDelay = 0.0f;
    
    m_MainCollision->SetTransform(bd.position, m_Rotation);
}
void RotatingAirBoost::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
}
void RotatingAirBoost::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    if(m_LauchDelay >= 0.0f)
        m_LauchDelay -= 1.0f/60.0f;
    
    
    float dt = 1.0f/60.0f;
    m_Rotation += m_RotationSpeed * dt;
    if(m_Rotation <= m_MinRot)
    {
        m_Rotation = m_MinRot;
        m_RotationSpeed = -m_RotationSpeed;
    }
    if(m_Rotation >= m_MaxRot)
    {
        m_Rotation = m_MaxRot;
        m_RotationSpeed = -m_RotationSpeed;
    }
    m_MainCollision->SetTransform(b2Vec2(m_StartPos.x, m_StartPos.y+1.5), m_Rotation);
}
bool RotatingAirBoost::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
    
	if(Rider::g_isCrashed) return false;
    
    if(m_LauchDelay > 0.0f) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA  || myFixture == fixtureB)
	{
        if(fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;

		//float yvel = fixtureB->GetBody()->GetLinearVelocity().y;
		Rider::g_LauchDir.x = 60.0f*sinf(b2_pi/2.0f-m_Rotation);
        Rider::g_LauchDir.y = 60.0f*cosf(b2_pi/2.0f-
                                         m_Rotation);
        
		AudioManager::PlayEffect(AUDIO_TURBO_STRIP);
        //createTrampVFX(m_ccLayer.parent,m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO);
		Rider::g_DoLaunch = true;

        m_LauchDelay = 0.5f;
		return true;
	}
	return false;
}