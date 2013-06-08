//
//  TurboStrip.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TurboStrip.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../FrontEnd/SaveLoad.h"
#include "../../AudioManager.h"
#include "../../ScreenHelper.h"

USING_NS_CC;

TurboStrip::TurboStrip(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale, bool bReverse):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
    m_bReverse = bReverse;
    m_LauchDelay = -1.0f;
    tex = NULL;
}
TurboStrip::~TurboStrip()
{
	if(tex)
	{
		delete tex;
        tex = NULL;
	}
}
bool TurboStrip::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
    if(SaveLoad::m_SaveData.turboLockLevel==0) return false;
    if(m_LauchDelay > 0.0f) return false;
    
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        if(myFixture == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(myFixture == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        
		b2Vec2 vel = Rider::g_MainBody->GetLinearVelocity();
        float angle = Rider::g_MainBody->GetAngle();
        while(angle > b2_pi*2.0f) angle -= b2_pi*2.0f;
        while(angle < 0) angle += b2_pi*2.0f;
        
        b2Vec2 pos = Rider::g_MainBody->GetPosition();
        
        if(m_bReverse)
        {
            bool goodAngle = (angle < 0.15f || angle > (b2_pi*2.0f-0.05f));
            bool goodY = (pos.y < (m_StartPos.y+3.75f) && pos.y > (m_StartPos.y+1.25f));
            
            if(vel.x < -5.0f && goodAngle && goodY)
            {
                if(SaveLoad::m_SaveData.turboLockLevel==1)
                    Rider::g_LauchDir.x = -40.0f;
                else if(SaveLoad::m_SaveData.turboLockLevel==2)
                    Rider::g_LauchDir.x = -55.0f;
                else if(SaveLoad::m_SaveData.turboLockLevel==3)
                    Rider::g_LauchDir.x = -65.0f;
                else
                {
                    Rider::g_LauchDir.x = -65.0f;
                    Rider::g_OnFire = 5.0f;
                }
                
                Rider::g_LauchDir.y = 0.0f;
                Rider::g_DoLaunch = true;
                m_LauchDelay = 0.5f;
                Rider::g_BikeAudio->PushState(BikeAudio::TURBO1);
                AudioManager::PlayEffect(AUDIO_TURBO_STRIP);
                return true;
            }
   
        }
        else
        {
            bool goodAngle = (angle < 0.05f || angle > (b2_pi*2.0f-0.15f));
            bool goodY = (pos.y < (m_StartPos.y+3.75f) && pos.y > (m_StartPos.y+1.25f));
            
            if(vel.x > 5.0f && goodAngle && goodY)
            {
                if(SaveLoad::m_SaveData.turboLockLevel==1)
                    Rider::g_LauchDir.x = 40.0f;
                else if(SaveLoad::m_SaveData.turboLockLevel==2)
                    Rider::g_LauchDir.x = 55.0f;
                else if(SaveLoad::m_SaveData.turboLockLevel==3)
                    Rider::g_LauchDir.x = 65.0f;
                else
                {
                    Rider::g_LauchDir.x = 65.0f;
                    Rider::g_OnFire = 5.0f;
                }
                
                Rider::g_LauchDir.y = 0.0f;
                Rider::g_DoLaunch = true;
                m_LauchDelay = 0.5f;
                
                Rider::g_BikeAudio->PushState(BikeAudio::TURBO1);
                AudioManager::PlayEffect(AUDIO_TURBO_STRIP);
                return true;
            }
        }
	}
	return false;
}
void TurboStrip::CreateSelf()
{
	if(m_created) return;

    if(SaveLoad::m_SaveData.turboLockLevel==0) return;
    
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(4.0f, 1.0f);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = 0x0011;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+1.0f);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
    
    tex = NULL;
    
	if(m_StartPos.y <= 0.1f)
    {
        float waitTime = 0.3f;
        if(SaveLoad::m_SaveData.turboLockLevel>=3)
        {
            waitTime = 0.1f;
        }
        else if(SaveLoad::m_SaveData.turboLockLevel==2)
        {
            waitTime = 0.2f;
        }
        const char *strip = NULL;
        const char *stripe1 = NULL;
        const char *stripe2 = NULL;
        if(SaveLoad::m_SaveData.turboLockLevel==1)
        {
            strip = "ctm_turboStrip_Blue.png";
            stripe1 = "ctm_Turbo_stripe_Blue_01.png";
            stripe2 = "ctm_Turbo_stripe_Blue_02.png";
        }
        else if(SaveLoad::m_SaveData.turboLockLevel==2)
        {
            strip = "ctm_turboStrip_Purple.png";
            stripe1 = "ctm_Turbo_stripe_Purple_01.png";
            stripe2 = "ctm_Turbo_stripe_Purple_02.png";
        }
        else
        {
            strip = "ctm_turboStrip.png";
            stripe1 = "ctm_Turbo_stripe_01.png";
            stripe2 = "ctm_Turbo_stripe_02.png";            
        }
        
        tex = new TextureObject((char*)strip,m_ccLayer,0,true,kTexture2DPixelFormat_Default);

 /*       CCSprite *glow1 = [CCSprite spriteWithSpriteFrameName:stripe1];
        glow1.position = ccp(224/2,72/2);
        [glow1 runAction:[CCRepeatForever actionWithAction:[CCSequence actions:[CCFadeIn actionWithDuration:0.05], [CCDelayTime actionWithDuration:waitTime], [CCFadeOut actionWithDuration:0.05f], [CCDelayTime actionWithDuration:waitTime],nil]]];
        [tex->GetSprite() addChild:glow1];
        CCSprite *glow2 = [CCSprite spriteWithSpriteFrameName:stripe2];
        [glow2 runAction:[CCRepeatForever actionWithAction:[CCSequence actions:[CCFadeOut actionWithDuration:0.05],[CCDelayTime actionWithDuration:waitTime], [CCFadeIn actionWithDuration:0.05f], [CCDelayTime actionWithDuration:waitTime],nil]]];
        glow2.position = ccp(224/2,72/2);
        [tex->GetSprite() addChild:glow2];*/
        tex->SetTextureOffset(0.0f, -1.0f);
        if(m_bReverse)
            tex->SetTextureScale(-1.0f, 1.0f);
    }
    else
    {
        
        
        float waitTime = 0.3f;
        if(SaveLoad::m_SaveData.turboLockLevel>=3)
        {
            waitTime = 0.1f;
        }
        else if(SaveLoad::m_SaveData.turboLockLevel==2)
        {
            waitTime = 0.2f;
        }
        const char *strip = NULL;
        const char *stripe1 = NULL;
        const char *stripe2 = NULL;
        if(SaveLoad::m_SaveData.turboLockLevel==1)
        {
            strip = "ctm_Upper_turboStrip_Blue.png";
            stripe1 = "ctm_Upper_turboStrip_Blue_01.png";
            stripe2 = "ctm_Upper_turboStrip_Blue_02.png";
        }
        else if(SaveLoad::m_SaveData.turboLockLevel==2)
        {
            strip = "ctm_Upper_turboStrip_Purple.png";
            stripe1 = "ctm_Upper_turboStrip_Purple_01.png";
            stripe2 = "ctm_Upper_turboStrip_Purple_02.png";
        }
        else
        {
            strip = "ctm_Upper_turboStrip.png";
            stripe1 = "ctm_Upper_turboStrip_01.png";
            stripe2 = "ctm_Upper_turboStrip_02.png";
        }
        
        tex = new TextureObject((char*)strip,m_ccLayer,1,true,kTexture2DPixelFormat_Default);
        
/*        CCSprite *glow1 = [CCSprite spriteWithSpriteFrameName:stripe1];
        glow1.position = ccp(256/2,32/2);
        [glow1 runAction:[CCRepeatForever actionWithAction:[CCSequence actions:[CCFadeIn actionWithDuration:0.05], [CCDelayTime actionWithDuration:waitTime], [CCFadeOut actionWithDuration:0.05f], [CCDelayTime actionWithDuration:waitTime],nil]]];
        [tex->GetSprite() addChild:glow1];
        CCSprite *glow2 = [CCSprite spriteWithSpriteFrameName:stripe2];
        [glow2 runAction:[CCRepeatForever actionWithAction:[CCSequence actions:[CCFadeOut actionWithDuration:0.05],[CCDelayTime actionWithDuration:waitTime], [CCFadeIn actionWithDuration:0.05f], [CCDelayTime actionWithDuration:waitTime],nil]]];
        glow2.position = ccp(256/2,32/2);
        [tex->GetSprite() addChild:glow2];*/
        
        
        tex->SetTextureOffset(0.0f, -1.80f);
        if(m_bReverse)
            tex->SetTextureScale(-1.0f, 1.0f);
        
//        tex = new TextureObject((char*)"ctm_Platform_New_Long_SpeedBoost.png",m_ccLayer,1,true,kTexture2DPixelFormat_Default);
//        tex->SetTextureOffset(0.0f, -1.75f);
//        tex->SetTextureScale(0.8, 1.0f);
//        if(m_bReverse)
//            tex->SetTextureScale(-0.8f, 1.0f);
    }
	m_MainCollision->SetUserData(tex);
    
    m_LauchDelay = 0.0f;
}
void TurboStrip::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    if(m_LauchDelay >= 0.0f)
        m_LauchDelay -= 1.0f/60.0f;
}
void TurboStrip::DestroySelf()
{
	if(m_created && SaveLoad::m_SaveData.turboLockLevel)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
        tex = NULL;
		m_world->DestroyBody(m_MainCollision);
	}
}
