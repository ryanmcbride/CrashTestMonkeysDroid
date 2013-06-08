//
//  Loop.mm
//  CTM
//
//  Created by Ryan McBride on 3/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "TripleLoop.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../AudioManager.h"
#include "../../ScreenHelper.h"

extern float g_DeltaTime;
extern float g_DeltaTime;

using namespace cocos2d;

#define DIVISIONS (36-9)
#define INNERSCALE 9.0f
#define OUTERSCALE 10.0f
#define MOVESCALE (INNERSCALE * 0.7f)
#define OFFSET_X 0.0f
#define OFFSET_Y 10.0f
#define COS_SCALE 0.85f
#define SIN_SCALE 1.0f

extern bool g_is60;

TripleLoop::TripleLoop(b2World *world, CCNode *ccLayer, CCLayer *frontLayer, b2Vec2 *startPos):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_frontLayer = frontLayer;
	m_StartPos = *startPos;
	Rider::g_inLoop = false;
    m_LaunchTime = 0.0f;
    m_bThisLoop = false;
}

TripleLoop::~TripleLoop()
{
	if(m_created)
	{
		DestroySelf();
	}
}
void TripleLoop::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
	
    
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    m_TopTexture->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture->setScale(scale*zoom);
    m_BottomTexture->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture->setScale(scale*zoom);
    m_TopTexture2->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture2->setScale(scale*zoom);
    m_BottomTexture2->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture2->setScale(scale*zoom);
    m_BottomTexture4->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.75f),zoom*PTM_RATIO*(m_StartPos.y+7.9f)));
    m_BottomTexture4->setScale(scale*zoom);
    m_TopTexture3->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture3->setScale(scale*zoom);
    m_BottomTexture3->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture3->setScale(scale*zoom);
    
    
	if(Rider::g_inLoop)
    {
        if(t<0.0f || t > 1.0f)
            t = backupT;
        
        b2Vec2 point = m_Spline->GetPosition(t);
        b2Vec2 forward;
        
        forward = point-lastPos;
        forward.Normalize();
        
        lastPos = point;
        
        if(m_AngleInterp > 0.0f)
        {
            float anglein = m_EntryForward;
            float angleout = b2Atan2(forward.y, forward.x);
            if(anglein > b2_pi && angleout < b2_pi)
                anglein -= 2.0f*b2_pi;
            if(anglein < b2_pi && angleout > b2_pi)
                anglein += 2.0f*b2_pi;
            
            Rider::g_MainBody->SetTransform(point,anglein*m_AngleInterp + (1.0f-m_AngleInterp)*angleout);
        }
        else
            Rider::g_MainBody->SetTransform(point,b2Atan2(forward.y, forward.x));
        Rider::FixWheelPos();
        
        float moveScale = g_DeltaTime/(1.0f/60.0f);
        
        float prevT = t;
        if(g_is60)
        {
            if(m_DeltaStep < 1.0f/180.0f)
                m_DeltaStep += m_AccelStep*moveScale;
            t += m_DeltaStep*moveScale;
            m_AngleInterp -= 1.0f/60.0f*3.0f;
        }
        else
        {
            if(m_DeltaStep < 1.0f/180.0f)
                m_DeltaStep += m_AccelStep*2.0f;
            t += m_DeltaStep*2.0f;
            m_AngleInterp -= 1.0f/30.0f*3.0f;
        }
        backupT = t;
        
        if(t >= 0.015f && prevT < 0.015f)
        {
            AudioManager::PlayEffect(AUDIO_CHAR_LOOP3);
            Rider::g_BikeAudio->PushState(BikeAudio::LOOP3);
        }
        
        if(t >= 0.25f && prevT < 0.25f)
        {
            m_TopTexture->removeFromParentAndCleanup(false);
            m_BottomTexture->removeFromParentAndCleanup(false);
            m_frontLayer->addChild(m_TopTexture,2);
            m_frontLayer->addChild(m_BottomTexture,2);
        }
        else if(t >= 0.33f && prevT < 0.33f)
        {
            //[Options PlayEffect:AUDIO_LOOP_2];
        }
        else if(t >= 0.5f && prevT < 0.5f)
        {
            m_TopTexture2->removeFromParentAndCleanup(false);
            m_BottomTexture2->removeFromParentAndCleanup(false);
            m_frontLayer->addChild(m_TopTexture2,1);
            m_frontLayer->addChild(m_BottomTexture2,1);
        }
        else if(t >= 0.66f && prevT < 0.66f)
        {
            //[Options PlayEffect:AUDIO_LOOP_3];
        }
        else if(t >= 0.75f && prevT < 0.75f)
        {
            m_TopTexture3->removeFromParentAndCleanup(false);
            m_BottomTexture3->removeFromParentAndCleanup(false);
            m_frontLayer->addChild(m_TopTexture3,0);
            m_frontLayer->addChild(m_BottomTexture3,0);
        }
        
        //vfx
        /*if(t >= 0.01f && prevT < 0.01f)
        {
            CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop 1A.png"];
            sprite.opacity = 0.0f;
            sprite.position = ccp(m_TopTexture.position.x-117,m_TopTexture.position.y-72);
            CCSequence *sequence = [CCSequence actions:[CCFadeIn actionWithDuration:0.1f],
                                    [CCDelayTime actionWithDuration:0.2f],
                                    [CCFadeOut actionWithDuration:0.1f],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
            
            sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop 1B.png"];
            sprite.opacity = 0.0f;
            sprite.position = ccp(m_TopTexture.position.x-53,m_TopTexture.position.y-6);
            sequence = [CCSequence actions:[CCDelayTime actionWithDuration:0.05f],
                        [CCFadeIn actionWithDuration:0.1f],
                        [CCDelayTime actionWithDuration:0.2f],
                        [CCFadeOut actionWithDuration:0.1f],
                        [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
            
            
            sprite = [CCSprite spriteWithSpriteFrameName:@"CTM_Circular_Loop.png"];
            sprite.opacity = 0.0f;
            sequence = [CCSequence actions:[CCDelayTime actionWithDuration:0.15f],
                        [CCFadeIn actionWithDuration:0.1f],
                        [CCDelayTime actionWithDuration:0.245f],
                        [CCFadeOut actionWithDuration:0.1f],
                        nil];
            [sprite runAction:sequence];
            
            m_BikeLoopVFX = [CCNode node];
            [m_frontLayer addChild:m_BikeLoopVFX z:3];
            
            sprite.position = ccp(0.0f,100.0f);
            //sprite.rotation = 90.0f;
            [m_BikeLoopVFX addChild:sprite z:0 tag:1];
        }
        else if(t >= 0.33f && prevT < 0.33f)
        {
            CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop 2A.png"];
            sprite.opacity = 0.0f;
            sprite.position = ccp(m_TopTexture2.position.x+20,m_TopTexture2.position.y-50);
            CCSequence *sequence = [CCSequence actions:[CCFadeIn actionWithDuration:0.1f],
                                    [CCDelayTime actionWithDuration:0.2f],
                                    [CCFadeOut actionWithDuration:0.1f],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
            
            sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop 2B.png"];
            sprite.opacity = 0.0f;
            sprite.position = ccp(m_TopTexture2.position.x+80,m_TopTexture2.position.y);
            sequence = [CCSequence actions:[CCDelayTime actionWithDuration:0.05f],
                        [CCFadeIn actionWithDuration:0.1f],
                        [CCDelayTime actionWithDuration:0.2f],
                        [CCFadeOut actionWithDuration:0.1f],
                        [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                        [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                        nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
            
            sprite = (CCSprite*)[m_BikeLoopVFX getChildByTag:1];
            sprite.opacity = 0.0f;
            sequence = [CCSequence actions:[CCDelayTime actionWithDuration:0.15f],
                        [CCFadeIn actionWithDuration:0.1f],
                        [CCDelayTime actionWithDuration:0.245f],
                        [CCFadeOut actionWithDuration:0.1f],
                        nil];
            [sprite runAction:sequence];
        }
        else if(t >= 0.66f && prevT < 0.66f)
        {
            CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop 2A.png"];
            sprite.opacity = 0.0f;
            sprite.position = ccp(m_TopTexture3.position.x+170,m_TopTexture3.position.y-30);
            CCSequence *sequence = [CCSequence actions:[CCFadeIn actionWithDuration:0.1f],
                                    [CCDelayTime actionWithDuration:0.2f],
                                    [CCFadeOut actionWithDuration:0.1f],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
            
            
            sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop 2B.png"];
            sprite.opacity = 0.0f;
            sprite.position = ccp(m_TopTexture3.position.x+230,m_TopTexture3.position.y+20);
            sequence = [CCSequence actions:[CCDelayTime actionWithDuration:0.05f],
                        [CCFadeIn actionWithDuration:0.1f],
                        [CCDelayTime actionWithDuration:0.2f],
                        [CCFadeOut actionWithDuration:0.1f],
                        [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                        [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                        nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
            
            sprite = (CCSprite*)[m_BikeLoopVFX getChildByTag:1];
            sprite.opacity = 0.0f;
            sequence = [CCSequence actions:[CCDelayTime actionWithDuration:0.15f],
                        [CCFadeIn actionWithDuration:0.1f],
                        [CCDelayTime actionWithDuration:0.245f],
                        [CCFadeOut actionWithDuration:0.1f],
                        nil];
            [sprite runAction:sequence];
        }
        else if(t >= 0.95f && prevT < 0.95f)
        {
            CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Loop Stright_Section.png"];
            sprite.opacity = 0.0f;
            sprite.rotation = -22.5f;
            sprite.position = ccp(m_TopTexture3.position.x+350,m_TopTexture3.position.y+20);
            CCSequence *sequence = [CCSequence actions:[CCFadeIn actionWithDuration:0.1f],
                                    [CCDelayTime actionWithDuration:0.2f],
                                    [CCFadeOut actionWithDuration:0.1f],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    [CCCallFuncND actionWithTarget:sprite selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                                    nil];
            [sprite runAction:sequence];
            [m_frontLayer addChild:sprite z:1];
   
        }
        else if(t >= 0.99f && prevT < 0.99f)
        {
            [m_BikeLoopVFX removeFromParentAndCleanup:YES];
            m_BikeLoopVFX = nil;
        }
        if(m_BikeLoopVFX)
        {
            CCSprite *bikeBody = ((TextureObject*)Rider::g_MainBody->GetUserData())->GetSprite();
            [m_BikeLoopVFX setPosition: bikeBody.position];
            [m_BikeLoopVFX setRotation: bikeBody.rotation];
        }*/
        
        
        
        if(t>=1.0f)
        {
            m_LaunchTime = 0.5f;
            Rider::g_LauchDir.x = 25.0f;
            Rider::g_LauchDir.y = 30.0f;
			Rider::g_DoLaunch = true;
            Rider::g_inLoop = false;
            m_bThisLoop = false;
            Rider::g_ScoreManager->FinishTrickGood(true);
            Rider::g_TrickState = 0;
        }
    }
    else
    {
        if(m_LaunchTime > 0.0f)
        {
            Rider::g_LauchDir.x = 25.0f;
            Rider::g_LauchDir.y = 30.0f;
			Rider::g_DoLaunch = true;
            m_LaunchTime -= g_DeltaTime;
        }
        if(Rider::g_MainBody->GetPosition().x < (m_StartPos.x-OUTERSCALE))
        {
            if(!m_bLeftSide)
            {
                m_TopTexture->removeFromParentAndCleanup(false);
                m_BottomTexture->removeFromParentAndCleanup(false);
                m_TopTexture2->removeFromParentAndCleanup(false);
                m_BottomTexture2->removeFromParentAndCleanup(false);
                m_TopTexture3->removeFromParentAndCleanup(false);
                m_BottomTexture3->removeFromParentAndCleanup(false);
                m_ccLayer->addChild(m_BottomTexture3,2);
                m_ccLayer->addChild(m_BottomTexture2,2);
                m_ccLayer->addChild(m_BottomTexture,2);
                m_ccLayer->addChild(m_TopTexture3,2);
                m_ccLayer->addChild(m_TopTexture2,2);
                m_ccLayer->addChild(m_TopTexture,2);
                
                m_bLeftSide = true;
            }
        }
        if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x+OUTERSCALE*3))
        {
            if(m_bLeftSide)
            {
                m_TopTexture->removeFromParentAndCleanup(false);
                m_BottomTexture->removeFromParentAndCleanup(false);
                m_TopTexture2->removeFromParentAndCleanup(false);
                m_BottomTexture2->removeFromParentAndCleanup(false);
                m_TopTexture3->removeFromParentAndCleanup(false);
                m_BottomTexture3->removeFromParentAndCleanup(false);
                m_ccLayer->addChild(m_BottomTexture3,2);
                m_ccLayer->addChild(m_BottomTexture2,2);
                m_ccLayer->addChild(m_BottomTexture,2);
                m_ccLayer->addChild(m_TopTexture3,2);
                m_ccLayer->addChild(m_TopTexture2,2);
                m_ccLayer->addChild(m_TopTexture,2);
                
                m_bLeftSide = false;
            }
        }
    }
}
void TripleLoop::CreateSelf()
{
	if(m_created)return;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	
    b2Vec2 verts[4];
    verts[3].x = -2.0f-10.0f;verts[3].y = -0.5f+1.0f;
    verts[2].x = -2.0f-10.0f;verts[2].y = 5.5f+1.0f;
    verts[1].x = 2.0f-10.0f; verts[1].y = 5.5f+1.0f;
    verts[0].x = 2.0f-10.0f; verts[0].y = -0.5f+1.0f;
    box.Set(verts,4);
    
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = 0x0011;
	fd.isSensor = true;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y);
	
	m_MainCollision = m_world->CreateBody(&bd);
	
    m_ForwardTrigger = m_MainCollision->CreateFixture(&fd);
    
    verts[3].x = -2.0f+10.0f;verts[3].y = -0.5f+1.0f;
    verts[2].x = -2.0f+10.0f;verts[2].y = 5.5f+1.0f;
    verts[1].x = 2.0f+10.0f; verts[1].y = 5.5f+1.0f;
    verts[0].x = 2.0f+10.0f; verts[0].y = -0.5f+1.0f;
    box.Set(verts,4);
    
    if(m_StartPos.y>1.0f)
        m_TopTexture = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_1a.png");
    else
        m_TopTexture = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_1a.png");
    
    m_TopTexture->retain();
    m_TopTexture->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture->setScale(1.0f);
    m_ccLayer->addChild(m_TopTexture,2);
    
    
    if(m_StartPos.y>1.0f)
        m_BottomTexture = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_1b.png");
    else
        m_BottomTexture = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_1b.png");
    
    m_BottomTexture->retain();
    m_BottomTexture->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture->setScale(1.0f);
    m_ccLayer->addChild(m_BottomTexture,2);
    
    
    if(m_StartPos.y>1.0f)
        m_TopTexture2 = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_2a.png");
    else
        m_TopTexture2 = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_2a.png");
    
    m_TopTexture2->retain();
    m_TopTexture2->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture2->setScale(1.0f);
    m_ccLayer->addChild(m_TopTexture2,2);
    
    if(m_StartPos.y>1.0f)
        m_BottomTexture2 = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_2b.png");
    else
        m_BottomTexture2 = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_2b.png");
    
    m_BottomTexture2->retain();
    m_BottomTexture2->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture2->setScale(1.0f);
    m_ccLayer->addChild(m_BottomTexture2,2);

    CCSprite *temp = NULL;
    if(m_StartPos.y>1.0f)
        temp = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_3c.png");
    else
        temp = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_3c.png");
    
    temp->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.75f),PTM_RATIO*(m_StartPos.y+7.9f)));
    temp->setScale(1.0f);
    m_ccLayer->addChild(temp,2);
    m_BottomTexture4 = temp;
    m_BottomTexture4->retain();
    
    if(m_StartPos.y>1.0f)
        m_TopTexture3 = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_3a.png");
    else
        m_TopTexture3 = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_3a.png");
    
    m_TopTexture3->retain();
    m_TopTexture3->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture3->setScale(1.0f);
    m_ccLayer->addChild(m_TopTexture3,2);
    
    if(m_StartPos.y>1.0f)
        m_BottomTexture3 = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_3b.png");
    else
        m_BottomTexture3 = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_3b.png");
    
    m_BottomTexture3->retain();
    m_BottomTexture3->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture3->setScale(1.0f);
    m_ccLayer->addChild(m_BottomTexture3,2);
    
    
    m_Spline = NULL;
    
    if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x+OUTERSCALE))
        m_bLeftSide = true;
    else
        m_bLeftSide = false;
    
    m_LaunchTime = 0.0f;
}
void TripleLoop::DestroySelf()
{
	if(m_created)
	{
        m_TopTexture->autorelease();
        m_BottomTexture->autorelease();
        m_TopTexture->removeFromParentAndCleanup(true);
        m_BottomTexture->removeFromParentAndCleanup(true);
		m_TopTexture2->autorelease();
        m_BottomTexture2->autorelease();
        m_TopTexture2->removeFromParentAndCleanup(true);
        m_BottomTexture2->removeFromParentAndCleanup(true);
		m_TopTexture3->autorelease();
        m_BottomTexture3->autorelease();
        m_BottomTexture4->autorelease();
        m_TopTexture3->removeFromParentAndCleanup(true);
        m_BottomTexture3->removeFromParentAndCleanup(true);
        m_BottomTexture4->removeFromParentAndCleanup(true);
        
		m_world->DestroyBody(m_MainCollision);
        if(m_Spline)
        {
            delete m_Spline;
            m_Spline = NULL;
        }
	}
}
bool TripleLoop::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
{
	if(!m_created) return false;
	
    if(Rider::g_isCrashed) return false;
    
	if(!Rider::g_inLoop && (m_ForwardTrigger == fixtureA || m_ForwardTrigger == fixtureB))
	{
        if(m_ForwardTrigger == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(m_ForwardTrigger == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        
        CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("ctm_VFX.plist","ctm_VFX.png");
        m_BikeLoopVFX = NULL;
        
        b2Vec2 vel = Rider::g_MainBody->GetLinearVelocity();
        float angle = Rider::g_MainBody->GetAngle();
        while(angle > b2_pi*2.0f) angle -= b2_pi*2.0f;
        while(angle < 0) angle += b2_pi*2.0f;
		bool goodAngle = (angle < 0.15f || angle > (b2_pi*2.0f-0.15f));
        
        b2Vec2 pos = Rider::g_MainBody->GetPosition();
        bool goodY = (pos.y < (m_StartPos.y+3.75f) && pos.y > (m_StartPos.y+1.25f));
        
        if(vel.x > 20.0f && goodAngle && goodY)
        {
            m_EntryForward = angle;
            m_AngleInterp = 1.0f;
            lastPos = Rider::g_MainBody->GetPosition();
            Rider::g_inLoop = true;
            m_bThisLoop = true;
            m_DeltaStep = 1.0f/120.0f;
            m_AccelStep = (1.0f/90.0f - 1.0f/120.0f)/10.0f;
            
            m_DeltaStep /= 3.0f;
            m_AccelStep /= 3.0f;
            
            t = m_DeltaStep;
            
            b2Vec2 points[17] =
            {
                b2Vec2(lastPos.x,lastPos.y),
                b2Vec2(0.0f+m_StartPos.x+6.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f,-2.5f+m_StartPos.y+20.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f,-2.5f+m_StartPos.y+20.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f,m_StartPos.y+4.0f),
                
                b2Vec2(0.0f+m_StartPos.x+6.0f+8.0f,-2.5f+m_StartPos.y+8.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f+10.0f,-2.5f+m_StartPos.y+22.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f+10.0f,-2.5f+m_StartPos.y+22.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f+10.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f+10.0f,m_StartPos.y+6.0f),
                
                b2Vec2(0.0f+m_StartPos.x+6.0f+18.0f,-2.5f+m_StartPos.y+10.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f+20.0f,-2.5f+m_StartPos.y+23.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f+20.0f,-2.5f+m_StartPos.y+23.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f+20.0f,-2.5f+m_StartPos.y+8.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f+20.0f,m_StartPos.y+8.0f),
                
                b2Vec2(0.0f+m_StartPos.x+6.0f+30.0f,m_StartPos.y+13.0f),
            };
            
            if(m_Spline)
                delete m_Spline;
            m_Spline = new Spline(points, 17);
            
            m_TopTexture->removeFromParentAndCleanup(false);
            m_BottomTexture->removeFromParentAndCleanup(false);
            m_ccLayer->addChild(m_TopTexture,2);
            m_ccLayer->addChild(m_BottomTexture,2);
            
            Rider::g_ScoreManager->SetLoops(3);
            //[Options PlayEffect:AUDIO_LOOP_2];
            return true;
        }
	}
    
	return false;
}