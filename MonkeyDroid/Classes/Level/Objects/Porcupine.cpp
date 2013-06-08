//
//  Trampoline.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Porcupine.h"
#include "SimpleAudioEngine.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../FrontEnd/SaveLoad.h"
//#import "FinishParticle.h"
#include "../../ScreenHelper.h"
#include "../../AudioManager.h"
#include "../Rider/Monkey.h"
#include "../Level.h"

using namespace cocos2d;


Porcupine::Porcupine(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
}
Porcupine::~Porcupine()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
void Porcupine::CreateSelf()
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
	TextureObject *tex = new TextureObject((char*)"ctm_Porcupine.png",m_ccLayer,0,true);
    tex->SetTextureScale(0.5f, 0.5f);
	m_MainCollision->SetUserData(tex);
	tex->SetTexturePosition(m_StartPos.x, m_StartPos.y+1.5f);
    m_Exploded = false;
    //tex->SetTextureOffset(0.0f, -0.5f);
}
void Porcupine::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
}

bool Porcupine::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(Rider::g_isCrashed) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(myFixture == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(myFixture == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        
		if(!Rider::g_isCrashed)
		{
			Rider::g_LauchDir.x = RandomFloat(-20.0f,20.0f);
			Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
			Rider::g_LauchDir.y = 50.0f;
			Rider::g_DoLaunch = true;
			Rider::g_ForceCrash = 0.2f;
            AudioManager::PlayEffect(AUDIO_PORCUPINE);
            Monkey::s_RandomXVel = 10.0f;
            Monkey::s_RandomYVel = 10.0f;
            Level::ScreenShake(0.2f,7.0f,10.0f);
		}
		m_Exploded = true;
		return false;
	}
	return false;
}