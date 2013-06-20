//
//  Trampoline.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Trampoline.h"
#include "SimpleAudioEngine.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../FrontEnd/Achievements.h"
#include "../../FrontEnd/SaveLoad.h"
//#import "FinishParticle.h"
#include "../../AudioManager.h"
#include "../../ScreenHelper.h"
//#import "GameHUD.h"

using namespace cocos2d;

static void* s_TrampolineHits[2];
static int s_trampImageNumber = 1050505;

void createTrampVFX(CCNode *ccLayer, float x,float y, const char *name)
{
    CCParticleSystemQuad *emitter = CCParticleSystemQuad::create(name);
    ccLayer->addChild(emitter);
    emitter->setPosition(ccp(x*ScreenHelper::getCameraZoom(),y*ScreenHelper::getCameraZoom()));
}

Trampoline::Trampoline(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale, int forceVersion):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
    m_BounceDelay = 0.0f;
    m_BouncedCount = 0;
    m_forceVersion = forceVersion;
}
Trampoline::~Trampoline()
{
	if(m_created && SaveLoad::m_SaveData.trampLockLevel)
		delete (TextureObject*)m_MainCollision->GetUserData();
}
void Trampoline::CreateSelf()
{
	if(m_created) return;
    if(!(SaveLoad::m_SaveData.trampLockLevel||m_forceVersion))return;
    
	int trampVersion = SaveLoad::m_SaveData.trampLockLevel-1;
    
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
    TextureObject *tex;
    
    if(m_forceVersion)
        trampVersion = m_forceVersion-1;
    
    if(m_BounceDelay <= 0.0f)
    {
        if(trampVersion==0)
            tex = new TextureObject((char*)"ctm_Armadillo1.png",m_ccLayer,1,true);
        else if(trampVersion==1)
            tex = new TextureObject((char*)"ctm_Armadillo2.png",m_ccLayer,1,true);
        else
            tex = new TextureObject((char*)"ctm_Armadillo3.png",m_ccLayer,1,true);
        tex->SetTextureScale(0.5f,0.5f);
        m_BouncedCount = 0;
    }
    else
    {
        if(trampVersion==0)
            tex = new TextureObject((char*)"ctm_Armadillo1_OFF.png",m_ccLayer,1,true);
        else if(trampVersion==1)
            tex = new TextureObject((char*)"ctm_Armadillo2_OFF.png",m_ccLayer,1,true);
        else
            tex = new TextureObject((char*)"ctm_Armadillo3_OFF.png",m_ccLayer,1,true);
        tex->SetTextureScale(0.5f,0.5f);
        tex->SetTextureOffset(0.0f, 10.0f/PTM_RATIO);
    }
    
    m_MainCollision->SetUserData(tex);
	tex->SetTexturePosition(m_StartPos.x, m_StartPos.y+1.5f);
    
    m_Texture = tex;
    
    m_LauchDelay = 0.0f;
    
    m_nodeNumbers[0] = m_nodeNumbers[1] = m_nodeNumbers[2] = -1;
    
}
void Trampoline::DestroySelf()
{
	if(m_created && (SaveLoad::m_SaveData.trampLockLevel || m_forceVersion))
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
	}
}
void Trampoline::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
    if(!(SaveLoad::m_SaveData.trampLockLevel||m_forceVersion))return;
    
    if(m_BounceDelay>0.0f)
    {
        m_BounceDelay -= (1.0f/60.0f)/3.0f;
    }
	if(!m_created)return;
    
    if(SaveLoad::m_SaveData.objectives[SaveLoad::TRIPLE_LINDY]==0)
    {
        if(Rider::s_bWheelsTouch && s_TrampolineHits[0])
        {
            s_TrampolineHits[0] = NULL;
            s_TrampolineHits[1] = NULL;
        }
    }
    
    if(m_LauchDelay >= 0.0f)
        m_LauchDelay -= 1.0f/60.0f;
    
    
    float zoom = ScreenHelper::getCameraZoom();
    float scale = ScreenHelper::getTextureScale();
    CCPoint newPoint = ccp(m_StartPos.x*PTM_RATIO*zoom, (m_StartPos.y+1.5f)*PTM_RATIO*zoom);
    for(int i = 0; i < 3; i++)
    {
        if(m_nodeNumbers[i] != -1)
        {
            CCNode *child = m_ccLayer->getChildByTag(m_nodeNumbers[i]);
            if(child)
            {
                child->setPosition(newPoint);
                child->setScale(0.5f*scale*zoom);
            }
        }
    }
}
void Trampoline::DoBounceCurl()
{
    
    int trampVersion = SaveLoad::m_SaveData.trampLockLevel-1;
    if(m_forceVersion)
    {
        m_BouncedCount = 0;
        trampVersion = m_forceVersion-1;
    }
    
    m_BouncedCount++;
    if(m_BouncedCount>=3)
    {
        m_BounceDelay = 10.0f;
        m_Texture->GetSprite()->setOpacity(0);
        CCSprite *curl = NULL;
        if(trampVersion==0)
            curl = CCSprite::createWithSpriteFrameName("ctm_Armadillo1_OFF.png");
        else if(trampVersion==1)
            curl = CCSprite::createWithSpriteFrameName("ctm_Armadillo2_OFF.png");
        else
            curl = CCSprite::createWithSpriteFrameName("ctm_Armadillo3_OFF.png");
        curl->setPosition(ccp(128,128+20));
        m_Texture->GetSprite()->addChild(curl);
    }
    else
    {
        int armNumber = 3;
        if(trampVersion==0)
            armNumber = 1;
        else if(trampVersion==1)
            armNumber = 2;
        
        CCSprite *bounce[3];
        char bounceName[64];
        sprintf(bounceName,"ctm_Armadillo%d_a.png",armNumber);
        bounce[0] = CCSprite::createWithSpriteFrameName(bounceName);
        sprintf(bounceName,"ctm_Armadillo%d_b.png",armNumber);
        bounce[1] = CCSprite::createWithSpriteFrameName(bounceName);
        sprintf(bounceName,"ctm_Armadillo%d_c.png",armNumber);
        bounce[2] = CCSprite::createWithSpriteFrameName(bounceName);
        
        m_Texture->GetSprite()->setOpacity(0);
        
        m_Texture->GetSprite()->runAction(CCSequence::create(CCDelayTime::create(8.0f/24.0f), CCFadeIn::create(0), NULL));
        
        float zoom = ScreenHelper::getCameraZoom();
        float scale = ScreenHelper::getTextureScale();
		
        m_nodeNumbers[0] = s_trampImageNumber++;
        m_nodeNumbers[1] = s_trampImageNumber++;
        m_nodeNumbers[2] = s_trampImageNumber++;
        
        m_ccLayer->addChild(bounce[0],2,m_nodeNumbers[0]);
        bounce[0]->setPosition(ccp(m_StartPos.x*PTM_RATIO*zoom, (m_StartPos.y+1.5f)*PTM_RATIO*zoom));
        bounce[0]->setScale(0.5f*scale*zoom);
        bounce[0]->runAction(CCSequence::create(CCDelayTime::create(2.0f/24.0f),CCFadeOut::create(0),CCCallFuncN::create(bounce[0], callfuncN_selector(CCNode::removeFromParentAndCleanup)), NULL));
        
        bounce[1]->setOpacity(0);
        m_ccLayer->addChild(bounce[1],2,m_nodeNumbers[1]);
        bounce[1]->setScale(0.5f*scale*zoom);
        bounce[1]->setPosition(bounce[0]->getPosition());
        bounce[1]->runAction(CCSequence::create(CCDelayTime::create(2.0f/24.0f),CCFadeIn::create(0),CCDelayTime::create(3.0f/24.0f),CCFadeOut::create(0),CCCallFuncN::create(bounce[1], callfuncN_selector(CCNode::removeFromParentAndCleanup)), NULL));
        
        bounce[2]->setOpacity(0);
        m_ccLayer->addChild(bounce[2],2,m_nodeNumbers[2]);
        bounce[2]->setPosition(bounce[0]->getPosition());
        bounce[2]->setScale(0.5f*scale*zoom);
        bounce[2]->runAction(CCSequence::create(CCDelayTime::create(5.0f/24.0f),CCFadeIn::create(0),CCDelayTime::create(3.0f/24.0f),CCFadeOut::create(0),CCCallFuncN::create(bounce[2], callfuncN_selector(CCNode::removeFromParentAndCleanup)), NULL));
    }
    
    
    if(SaveLoad::m_SaveData.objectives[SaveLoad::TRIPLE_LINDY]==0)
    {
        if(s_TrampolineHits[0] == NULL)
            s_TrampolineHits[0] = this;
        else
        {
            if(s_TrampolineHits[1] == NULL)
            {
                if(s_TrampolineHits[0] != this)
                    s_TrampolineHits[1] = this;
            }
            else
            {
                if(s_TrampolineHits[0] != this && s_TrampolineHits[1] != this)
                {
                    Achievements::EarnAchievement(Level::getHUD()->getParent(),SaveLoad::TRIPLE_LINDY);
                }
            }
        }
    }
}

bool Trampoline::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
    
	if(Rider::g_isCrashed) return false;
    
    if(m_LauchDelay > 0.0f) return false;
    
    if(!(SaveLoad::m_SaveData.trampLockLevel||m_forceVersion))return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
    
    int trampVersion = SaveLoad::m_SaveData.trampLockLevel-1;
    if(m_forceVersion)
        trampVersion = m_forceVersion-1;
    
	if(myFixture == fixtureA)
	{
        if(fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(m_BouncedCount>=3)
            return false;

		float yvel = fixtureB->GetBody()->GetLinearVelocity().y;
		Rider::g_LauchDir.x = 0.0f;
        
		if(trampVersion==0)
        {
            Rider::g_LauchDir.y = 35.0f - yvel/2.0f;
            AudioManager::PlayEffect(AUDIO_ARMADILLO1);
            //[Options PlayEffect:AUDIO_ARMADILLO_FB];
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Blue.plist");
        }
        else if(trampVersion==1)
        {
            Rider::g_LauchDir.y = 50.0f - yvel/2.0f;
            AudioManager::PlayEffect(AUDIO_ARMADILLO2);
            //[Options PlayEffect:AUDIO_ARMADILLO_SB];
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Purple.plist");
        }
        else if (trampVersion==2)
        {
            Rider::g_LauchDir.y = 60.0f - yvel/2.0f;
            AudioManager::PlayEffect(AUDIO_ARMADILLO3);
            //[Options PlayEffect:AUDIO_ARMADILLO_TB];
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Red.plist");
        }
        else
        {
            Rider::g_LauchDir.y = 60.0f - yvel/2.0f;
            Rider::g_OnFire = 5.0f;
            AudioManager::PlayEffect(AUDIO_ARMADILLO3);
            //[Options PlayEffect:AUDIO_ARMADILLO_TB];
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Red.plist");
        }
		Rider::g_DoLaunch = true;
        m_LauchDelay = 0.5f;
        DoBounceCurl();
            
		return true;
	}
	if(myFixture == fixtureB)
	{
		if(fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(m_BouncedCount>=3)
            return false;
        
		float yvel = fixtureA->GetBody()->GetLinearVelocity().y;
		Rider::g_LauchDir.x = 0.0f;
		
        if(trampVersion==0)
        {
            Rider::g_LauchDir.y = 35.0f - yvel/2.0f;
            AudioManager::PlayEffect(AUDIO_ARMADILLO1);
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Blue.plist");
        }
        else if(trampVersion==1)
        {
            AudioManager::PlayEffect(AUDIO_ARMADILLO2);
            Rider::g_LauchDir.y = 50.0f - yvel/2.0f;
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Purple.plist");
        }
        else if (trampVersion==2)
        {
            AudioManager::PlayEffect(AUDIO_ARMADILLO3);
            Rider::g_LauchDir.y = 60.0f - yvel/2.0f;
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Red.plist");
        }
        else
        {
            AudioManager::PlayEffect(AUDIO_ARMADILLO3);
            Rider::g_LauchDir.y = 60.0f - yvel/2.0f;
            Rider::g_OnFire = 5.0f;
            createTrampVFX(m_ccLayer->getParent(),m_StartPos.x*PTM_RATIO,m_StartPos.y*PTM_RATIO,"Armadillo_Red.plist");
        }
        
		Rider::g_DoLaunch = true;
        m_LauchDelay = 0.5f;
        DoBounceCurl();
        return true;
	}
	return false;
}