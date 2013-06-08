//
//  ExplodingBarrel.mm
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "WaterTank.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"
//#import "../Particles/FinishParticle.h"
#include "../../AudioManager.h"
#include "../../FrontEnd/SaveLoad.h"
#include "../../FrontEnd/Achievements.h"

using namespace cocos2d;

WaterTank::WaterTank(b2World *world, CCNode *ccLayer, CCNode *frontLayer, b2Vec2 *startPos, int type):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_frontLayer = frontLayer;
	m_StartPos = *startPos;
    m_Type = type;
    //emitter = nil;
}
WaterTank::~WaterTank()
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
void WaterTank::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	box.SetAsBox(9.00f, 1.0f);
	
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	fd.isSensor = true;
	
    if(m_Type==SHARK)
        bd.position.Set(m_StartPos.x, m_StartPos.y+2.0);
    if(m_Type==ACID)
        bd.position.Set(m_StartPos.x, m_StartPos.y+1.75);
    if(m_Type==SPACE)
        bd.position.Set(m_StartPos.x, m_StartPos.y+1.5);
    
    m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	
    fd.isSensor = false;
	bd.position.Set(m_StartPos.x-11.75, m_StartPos.y+1.75*1.25f);
    box.SetAsBox(0.1f, 1.75f*1.25f);
    m_LeftCollision = m_world->CreateBody(&bd);
    m_LeftCollision->CreateFixture(&fd);

    
    if(m_Type==SHARK)
    {
        bd.position.Set(m_StartPos.x+11.00, m_StartPos.y+1.75*1.25f);
        m_RightCollision = m_world->CreateBody(&bd);
        m_RightCollision->CreateFixture(&fd);

        TextureObject *tex = new TextureObject((char*)"ctm_Tiki_sharkTank_Base_Big.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
        m_MainCollision->SetUserData(tex);
        tex->SetTextureOffset(1.3f,0.5f);
        
        //emitter = [ARCH_OPTIMAL_PARTICLE_SYSTEM particleWithFile:@"TankBubbles.plist"];
        //[tex->GetSprite() addChild: emitter];
        //emitter.position = ccp(240,30);  // setting emitter position
         // adding the emitter

        
        m_Shark = CCSprite::createWithSpriteFrameName("ctm_Tiki_sharkTank_Shark.png");
        m_Front = CCSprite::createWithSpriteFrameName("ctm_Tiki_TankTop_Big.png");
        tex->GetSprite()->addChild(m_Shark);
        tex->GetSprite()->addChild(m_Front);
        
        m_Front->setPosition(ccp((m_MainCollision->GetPosition().x+1.3f)*16,(m_MainCollision->GetPosition().y+0.5f)*16));
        m_Shark->setPosition(ccp(23*16,3.5*16));
        
        //m_frontLayer->addChild(m_Front);
        CCMoveBy *moveLeft = CCMoveBy::create(3.0f,ccp(-16.5*16,0));
        CCScaleTo *flip = CCScaleTo::create(0.01f,-1.0f,1.0f);
        CCMoveBy *moveRight = CCMoveBy::create(3.0f,ccp(16.5*16,0));
        CCScaleTo *flipBack = CCScaleTo::create(0.01f,1.0f,1.0f);
        CCSequence *sequence = CCSequence::create(moveLeft,flip,moveRight,flipBack, NULL);
        m_Shark->runAction(CCRepeatForever::create(sequence));
    }
    if(m_Type==SPACE)
    {
        bd.position.Set(m_StartPos.x+11.75, m_StartPos.y+1.75*1.25f);
        m_RightCollision = m_world->CreateBody(&bd);
        m_RightCollision->CreateFixture(&fd);

        TextureObject *tex = new TextureObject((char*)"ctm_Space_Tank_base.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
        m_MainCollision->SetUserData(tex);
        tex->SetTextureOffset(1.3f,0.5f);
        //emitter = [ARCH_OPTIMAL_PARTICLE_SYSTEM particleWithFile:@"TankBubbles.plist"];
        //[tex->GetSprite() addChild: emitter];
        //emitter.position = ccp(210,20);  // setting emitter position
        
        for(int i = 0; i < 3; i++)
        {
            char alienName[64];
            sprintf(alienName,"ctm_Space_Tank_Alien%02d.png",RandomInt(0,7)+1);
            CCSprite *alien = CCSprite::createWithSpriteFrameName(alienName);
            tex->GetSprite()->addChild(alien);
            
            if(RandomInt(0,100)<50)
            {
                float alienOffset = RandomFloat(0, 6.0f);
                float timeOffset = RandomFloat(0.0f, 1.5f);
                alien->setPosition(ccp((23 - alienOffset/2.0f) *16,(RandomFloat(0.0,2.5f)+1.0f)*16));
                alien->setScaleX(-1.0f);
                CCMoveBy *moveLeft = CCMoveBy::create(1.5f+timeOffset,ccp((-16.5+alienOffset)*16,0));
                CCScaleTo *flip = CCScaleTo::create(0.01f,1.0f,1.0f);
                CCMoveBy *moveRight = CCMoveBy::create(1.5f+timeOffset,ccp((16.5-alienOffset)*16,0));
                CCScaleTo *flipBack = CCScaleTo::create(0.01f,-1.0f,1.0f);
                CCSequence *sequence = CCSequence::create(moveLeft,flip,moveRight,flipBack, NULL);
                alien->runAction(CCRepeatForever::create(sequence));
            }
            else
            {
                float alienOffset = RandomFloat(0, 6.0f);
                float timeOffset = RandomFloat(0.0f, 1.5f);
                alien->setPosition(ccp((6.5f+alienOffset/2.0f)*16,(RandomFloat(0.0,2.5f)+1.0f)*16));
                alien->setScaleX(1.0f);
                CCMoveBy *moveLeft = CCMoveBy::create(1.5f+timeOffset,ccp((-16.5+alienOffset)*16,0));
                CCScaleTo *flip = CCScaleTo::create(0.01f,1.0f,1.0f);
                CCMoveBy *moveRight = CCMoveBy::create(1.5f+timeOffset,ccp((16.5-alienOffset)*16,0));
                CCScaleTo *flipBack = CCScaleTo::create(0.01f,-1.0f,1.0f);
                CCSequence *sequence = CCSequence::create(moveRight,flipBack,moveLeft,flip, NULL);
                alien->runAction(CCRepeatForever::create(sequence));
            }
        }
        
        m_Front = CCSprite::createWithSpriteFrameName("ctm_Space_TankTop.png");
        m_Front->setPosition(ccp(14*16,3.0*16));
        tex->GetSprite()->addChild(m_Front);
    }
    if(m_Type==ACID)
    {
        bd.position.Set(m_StartPos.x+11.75, m_StartPos.y+1.75*1.25f);
        m_RightCollision = m_world->CreateBody(&bd);
        m_RightCollision->CreateFixture(&fd);

        TextureObject *tex = new TextureObject((char*)"ctm_City_TankBase.png",m_ccLayer,2,true,kTexture2DPixelFormat_Default);
        m_MainCollision->SetUserData(tex);
        tex->SetTextureOffset(1.3f,0.25f);
        //emitter = [ARCH_OPTIMAL_PARTICLE_SYSTEM particleWithFile:@"TankBubbles.plist"];
        //[tex->GetSprite() addChild: emitter];
        //emitter.position = ccp(210,20);  // setting emitter position
        CCSprite *stuff = CCSprite::createWithSpriteFrameName("ctm_City_TankStuff.png");
        stuff->setPosition(ccp(14*16,3.0*16));
        tex->GetSprite()->addChild(stuff);
        
        m_Shark = CCSprite::createWithSpriteFrameName("ctm_fishSkeleton.png");
        
        m_Front = CCSprite::createWithSpriteFrameName("ctm_City_TankTop.png");
        tex->GetSprite()->addChild(m_Shark);
        
        m_Front->setPosition(ccp(14*16,3.0*16));
        m_Shark->setPosition(ccp(21*16,2.0*16));
        
        tex->GetSprite()->addChild(m_Front);
        
        CCMoveBy *moveLeft = CCMoveBy::create(3.0f,ccp(-15.5*16,0));
        CCScaleTo *flip = CCScaleTo::create(0.01f,-1.0f,1.0f);
        CCMoveBy *moveRight = CCMoveBy::create(3.0f,ccp(15.5*16,0));
        CCScaleTo *flipBack = CCScaleTo::create(0.01f,1.0f,1.0f);
        CCSequence *sequence = CCSequence::create(moveLeft,flip,moveRight,flipBack, NULL);
        m_Shark->runAction(CCRepeatForever::create(sequence));
    }
    
    m_censorBar = NULL;
    m_Exploded = false;
    
}
void WaterTank::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
		m_world->DestroyBody(m_MainCollision);
        m_world->DestroyBody(m_LeftCollision);
        m_world->DestroyBody(m_RightCollision);
        if(m_Exploded)
        {
            m_censorBar->removeFromParentAndCleanup(true);
        }
	}
}
void WaterTank::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    
    if(m_censorBar)
    {
        TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
        m_censorBar->setPosition(ccp(censorX*ScreenHelper::getCameraZoom()*PTM_RATIO,texObject->GetSprite()->getPosition().y));
        m_censorBar->setScale(ScreenHelper::getCameraZoom()*ScreenHelper::getTextureScale());
    }
}
bool WaterTank::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	if(m_Exploded) return false;
	
	b2Fixture *myFixture = m_MainCollision->GetFixtureList();
	if(myFixture == fixtureA || myFixture == fixtureB)
	{
        Rider::g_ForceCrash = 0.2f;
        Rider::g_WaterCrash = true;
        Rider::g_OnFire = 0.0f;
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
        m_censorBar = CCSprite::createWithSpriteFrameName("ctm_Censored_03.png");
     
        float offset = Rider::g_MainBody->GetLinearVelocity().x;
        censorX = Rider::g_MainBody->GetPosition().x;
        m_censorBar->setPosition(ccp(Rider::g_MainBody->GetPosition().x*PTM_RATIO+offset,texObject->GetSprite()->getPosition().y));
        m_frontLayer->addChild(m_censorBar,4);
        m_Exploded = true;
        
        AudioManager::PlayEffect(AUDIO_CENSORED);
        AudioManager::PlayEffect(AUDIO_WATER_TANK);
        AudioManager::PlayEffect(AUDIO_CHAR_DROWN);
        //[Options PlayEffect:AUDIO_LAND_IN_LIQUID];
        
        if(m_Type == SHARK && SaveLoad::m_SaveData.objectives[SaveLoad::JUMP_THE_SHARK]==0)
        {
            Achievements::EarnAchievement(Level::getHUD()->getParent(),SaveLoad::JUMP_THE_SHARK);
        }
        
		return false;
	}
	return false;
}