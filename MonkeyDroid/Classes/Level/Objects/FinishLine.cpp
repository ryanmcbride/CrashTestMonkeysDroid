//
//  FinishLine.mm
//  CTM
//
//  Created by Ryan McBride on 5/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "FinishLine.h"
#include "../Rider/Rider.h"
//#import "../Particles/FinishParticle.h"
#include "../../ScreenHelper.h"
#include "AudioManager.h"

using namespace cocos2d;

extern bool g_is60;

FinishLine::FinishLine(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
    m_FireWorks = 0;
    m_FireWorksDelay = -1.0f;
}
FinishLine::~FinishLine()
{
	if(m_created)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
void FinishLine::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
    float deltaTime = 1.0f/30.0f;
    if(g_is60)
        deltaTime = 1.0f/60.0f;
    
    if(m_FireWorksDelay >= 0.0f)
    {
        if(m_FireWorksDelay > 0.0f && (m_FireWorksDelay-deltaTime <= 0.0f) && m_FireWorks > 0)
        {
            //createFireWorks([m_ccLayer parent],m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO);
            m_FireWorks--;
            m_FireWorksDelay = RandomFloat(3.0f/30.0f,10.0f/30.0f);
        }
        m_FireWorksDelay-=deltaTime;
    }
}
bool FinishLine::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(Rider::g_isFinished) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
		//do finish stuff here
		m_FireWorks = 10;
        m_FireWorksDelay = 0.01f;
        Rider::g_isFinished = true;
        AudioManager::PlayEffect(AUDIO_FINISH_LINE);
        AudioManager::PlayEffect(AUDIO_FIREWORKS);
        AudioManager::PlayEffect(AUDIO_CHAR_FINISH);
        Rider::g_BikeAudio->PushState(BikeAudio::OFF);
		return false;
	}
	return false;
}
void FinishLine::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(64/PTM_RATIO, 128/PTM_RATIO);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = 0x0011;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+128/PTM_RATIO);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	TextureObject *tex = new TextureObject((char*)"ctm_FinishLine.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
    tex->SetTextureOffset(0.0f, -128/PTM_RATIO);
	m_MainCollision->SetUserData(tex);	
}
void FinishLine::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
}
