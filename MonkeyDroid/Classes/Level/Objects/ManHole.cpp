//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "ManHole.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"
#include "../Level.h"

extern float g_DeltaTime;

using namespace cocos2d;

ManHole::ManHole(b2World *world, CCNode *ccLayer, CCNode* frontLayer, b2Vec2 *startPos):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
    m_frontLayer = frontLayer;
	m_StartPos = *startPos;
}
ManHole::~ManHole()
{
	if(m_created)
	{
        delete (TextureObject*)m_MainCollision->GetUserData();
        m_Spikes->removeFromParentAndCleanup(true);
    }
}
void ManHole::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	box.SetAsBox(4.0f, 1.0f);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.0);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    
    
	TextureObject *tex = NULL;
    tex = new TextureObject((char*)"ctm_Manhole_Base.png",m_ccLayer,0,true,kTexture2DPixelFormat_Default);
    m_MainCollision->SetUserData(tex);
    //tex->SetTextureOffset(0.0f, 0.0f);
    
    int bgID = 0;//[GameLevel getlevelDes]->bgID;
    if(bgID==0)//tiki
    {
        m_Spikes = CCSprite::createWithSpriteFrameName("ctm_Manhole_Tiki.png");
    }
    else if(bgID == 3)//space
    {
        m_Spikes = CCSprite::createWithSpriteFrameName("ctm_Manhole_Space.png");
    }
    else//city
    {
        m_Spikes = CCSprite::createWithSpriteFrameName("ctm_Manhole_City.png");
    }
    
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    
    m_Spikes->setPosition(ccp(zoom*PTM_RATIO*m_StartPos.x,zoom*PTM_RATIO*(m_StartPos.y+1.0f)));
    m_Spikes->setScale(zoom*scale);
    m_frontLayer->addChild(m_Spikes,0);
    
    m_Exploded = false;
    m_LastJump = 10.0f;
}
void ManHole::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    
    m_Spikes->setPosition(ccp(zoom*PTM_RATIO*m_StartPos.x,zoom*PTM_RATIO*(m_StartPos.y+1.0f)));
    m_Spikes->setScale(zoom*scale);
    
    float width = 4.0f;
    
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
                    }
                    m_Exploded = true;
                }
            }
        }
        else
        {
            m_Exploded = false;
        }
    }
    
}
void ManHole::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
        m_Spikes->removeFromParentAndCleanup(true);
	}
}

bool ManHole::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
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
		return false;
	}
	return false;
}