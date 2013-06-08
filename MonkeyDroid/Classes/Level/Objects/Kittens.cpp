//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "Kittens.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"
#include "../../AudioManager.h"

extern float g_DeltaTime;

using namespace cocos2d;

Kittens::Kittens(b2World *world, CCNode *ccLayer, CCNode* frontLayer, b2Vec2 *startPos, int type):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
    m_frontLayer = frontLayer;
	m_StartPos = *startPos;
    m_Type = type;
}
Kittens::~Kittens()
{
	if(m_created)
	{
        delete (TextureObject*)m_MainCollision->GetUserData();
        if(m_Exploded)
        {
            m_censorBar->removeFromParentAndCleanup(true);
        }
    }
}
void Kittens::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
    switch(m_Type)
    {
        default:
        case KITTENS:
            box.SetAsBox(6.5f, 1.0f);
            break;
        case COWS:
            box.SetAsBox(8.0f, 1.0f);
            break;
        case CHICKENS:
            box.SetAsBox(8.0f, 1.0f);
            break;
    }
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.0);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    
    
	TextureObject *tex = NULL;
    
    switch(m_Type)
    {
        default:
        case KITTENS:
            tex = new TextureObject((char*)"ctm_AllLevels_Cats.png",m_ccLayer,0,true,kTexture2DPixelFormat_Default);
            m_MainCollision->SetUserData(tex);
            tex->SetTextureOffset(0.0f, 0.5f);
            tex->SetTextureScale(0.8f, 0.8f);
            break;
        case COWS:
            tex = new TextureObject((char*)"ctm_AllLevels_Cows.png",m_ccLayer,0,true,kTexture2DPixelFormat_Default);
            m_MainCollision->SetUserData(tex);
            tex->SetTextureOffset(0.0f, 0.5f);
            break;
        case CHICKENS:
            tex = new TextureObject((char*)"ctm_AllLevels_Chickens.png",m_ccLayer,0,true,kTexture2DPixelFormat_Default);
            m_MainCollision->SetUserData(tex);
            tex->SetTextureOffset(0.0f, 0.5f);
            break;
    }
    
    m_Exploded = false;
    m_LastJump = 10.0f;
    m_censorBar = NULL;
}
void Kittens::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    float width = 8.0f;
    switch(m_Type)
    {
        default:
        case KITTENS:
            width = 6.5f;
            break;
        case COWS:
            width = 8.0f;
            break;
        case CHICKENS:
            width = 8.0f;
            break;
    }
    if(m_censorBar)
    {
        TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
        m_censorBar->setPosition(texObject->GetSprite()->getPosition());
        m_censorBar->setScale(ScreenHelper::getCameraZoom()*ScreenHelper::getTextureScale());
    }
    
    if(m_Exploded && Rider::g_MainBody->GetPosition().y < (m_StartPos.y+4.0f))
    {
        if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x-width))
        {
            if(Rider::g_MainBody->GetPosition().x < (m_StartPos.x+width))
            {
                m_LastJump -= g_DeltaTime;
                if(m_LastJump <= 0.0f)
                {
                    Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
                    Rider::g_LauchDir.y = 15.0f;
                    Rider::g_DoLaunch = true;
                    m_LastJump = 1.0f;
                    Rider::g_ScoreManager->AddScore(-100);
                }
            }
        }
    }
    
}
void Kittens::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
        if(m_Exploded)
        {
            m_censorBar->removeFromParentAndCleanup(true);
            m_censorBar = NULL;
        }
	}
}

bool Kittens::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        
        switch(m_Type)
        {
            default:
            case KITTENS:
                if(m_censorBar == NULL)
                {
                    m_censorBar = CCSprite::createWithSpriteFrameName("ctm_Censored_03.png");
                    AudioManager::PlayEffect(AUDIO_CENSORED);
                    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
                    m_censorBar->setPosition(texObject->GetSprite()->getPosition());
                    m_frontLayer->addChild(m_censorBar,4);
                }
                break;
            case COWS:
                if(m_censorBar == NULL)
                {
                    m_censorBar = CCSprite::createWithSpriteFrameName("ctm_Censored_03.png");
                    AudioManager::PlayEffect(AUDIO_CENSORED);
                    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
                    m_censorBar->setPosition(texObject->GetSprite()->getPosition());
                    m_frontLayer->addChild(m_censorBar,4);
                }
                AudioManager::PlayEffect(AUDIO_COWS);
                break;
            case CHICKENS:
                if(m_censorBar == NULL)
                {
                    m_censorBar = CCSprite::createWithSpriteFrameName("ctm_Censored_03.png");
                    AudioManager::PlayEffect(AUDIO_CENSORED);
                    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
                    m_censorBar->setPosition(texObject->GetSprite()->getPosition());
                    m_frontLayer->addChild(m_censorBar,4);
                }
                AudioManager::PlayEffect(AUDIO_CHICKENS);
                break;
        }
		m_censorBar->setScale(ScreenHelper::getCameraZoom()*ScreenHelper::getTextureScale());
		
		m_Exploded = true;
        
        Rider::g_MainBody->ApplyTorque(RandomFloat(40000.0f,50000.0f));
        Rider::g_LauchDir.x = 0.0f;
        Rider::g_LauchDir.y = 15.0f;
        Rider::g_DoLaunch = true;
        m_LastJump = 1.0f;
        Rider::g_BikeAudio->PushState(BikeAudio::ROUGH);
        Rider::g_ScoreManager->AddScore(-100);
		return false;
	}
	return false;
}