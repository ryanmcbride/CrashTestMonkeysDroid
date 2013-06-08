/*
 *  Ramp.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Crate.h"
#include "TextureObject.h"
#include "../../ScreenHelper.h"
#include "../../AudioManager.h"

using namespace cocos2d;

Crate::Crate(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_Scale = scale;
    m_type = ORIGINAL;
    m_HitDelay = -1.0f;
    m_sort = 0;
}
Crate::Crate(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, Type type, int sort):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_Scale = 1.0f;
    m_type = type;
    m_beachBallTexNum = RandomInt(1,7);
    m_HitDelay = -1.0f;
    m_sort = sort;
}


Crate::~Crate()
{
	if(m_created)
	{
        if(m_type==BEACH_BALL)
        {
            m_TextureHighlight->ReleaseTexture();
            delete m_TextureHighlight;
        }
        delete (TextureObject*)m_MainCollision->GetUserData();
    }
}
void Crate::Step(float xpos)
{
    if(m_created)
    {
        m_StartPos = m_MainCollision->GetPosition();
        if(m_type==BEACH_BALL)
        {
            m_TextureHighlight->SetTexturePosition(m_MainCollision->GetPosition().x, m_MainCollision->GetPosition().y);
            m_StartPos.y -= 0.8f;
            if(m_HitDelay>=0.0f)
                m_HitDelay -= 1.0f/60.0f;
        }
        else
            m_StartPos.y -= 0.6f;
        m_xpos = m_StartPos.x;
    }
}    
void Crate::CreateSelf()
{
	if(m_created) return;
	
	b2FixtureDef fd;
	b2BodyDef bd;
	bd.type = b2_dynamicBody;
    
    if(m_type==BEACH_BALL)
    {
        b2CircleShape circle;
        circle.m_radius = 1.6f;
        fd.shape = &circle;        
    }
    else
    {
        b2PolygonShape box;
        box.SetAsBox(1.2f, 1.2f);
        fd.shape = &box;
    }
    
	fd.density = 2.0f;
	fd.friction = 0.62f;
	fd.filter.categoryBits = 0x7fff;
    fd.filter.maskBits = 0xffff;
	
	if(m_type==BEACH_BALL)
    {
        fd.restitution = 0.6f;
        bd.position.Set(m_StartPos.x, m_StartPos.y+0.8f);
    }
    else
        bd.position.Set(m_StartPos.x, m_StartPos.y+0.6f);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    
    TextureObject *tex = NULL;
    if(m_type==BEACH_BALL)
    {
        char textStr[32];
        sprintf(textStr,"ctm_Beachball_0%d.png",m_beachBallTexNum);
        tex = new TextureObject(textStr,m_ccLayer,m_sort,true,kTexture2DPixelFormat_Default);
        
        m_TextureHighlight = new TextureObject((char*)"ctm_Beachball_Highlight.png",m_ccLayer,3,true,kTexture2DPixelFormat_Default);
	}
    else
    {
        tex = new TextureObject((char*)"ctm_Crate.png",m_ccLayer,3,true,kTexture2DPixelFormat_Default);
    }
    
    tex->SetTextureScale(m_Scale,m_Scale);
	m_MainCollision->SetUserData(tex);
	
}
void Crate::DestroySelf()
{
	if(m_created)
	{
        if(m_type==BEACH_BALL)
        {
            m_TextureHighlight->ReleaseTexture();
            delete m_TextureHighlight;
        }
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
        m_world->DestroyBody(m_MainCollision);
        m_created = false;
	}
}
bool Crate::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
    
	//if(Rider::g_isCrashed) return false;
    
    if(m_HitDelay > 0.0f) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA)
	{
        if(fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(m_type==BEACH_BALL)
           AudioManager::PlayEffect(AUDIO_BEACH_BALL);
        m_HitDelay = 0.5f;
		return true;
	}
	if(myFixture == fixtureB)
	{
		if(fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
		if(m_type==BEACH_BALL)
            AudioManager::PlayEffect(AUDIO_BEACH_BALL);
        m_HitDelay = 0.5f;
		return true;
	}
	return false;
}
