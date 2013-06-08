//
//  Loop.mm
//  CTM
//
//  Created by Ryan McBride on 3/28/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SingleLoop.h"
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

SingleLoop::SingleLoop(b2World *world, CCNode *ccLayer, CCLayer *frontLayer, b2Vec2 *startPos):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_frontLayer = frontLayer;
	m_StartPos = *startPos;
	Rider::g_inLoop = false;
    m_bThisLoop = false;
}

SingleLoop::~SingleLoop()
{
	if(m_created)
	{
		DestroySelf();
	}
}
void SingleLoop::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
	
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    
    m_BottomTexture->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture->setScale(scale*zoom);
    m_TopTexture->setPosition(CCPointMake(zoom*PTM_RATIO*(m_StartPos.x+9.5f),zoom*PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture->setScale(scale*zoom);
    
	if(Rider::g_inLoop && m_bThisLoop)
    {
        if(t<0.0f || t > 1.0f)
            t = backupT;
        
        b2Vec2 point = m_Spline->GetPosition(t);
        b2Vec2 forward;
        if(m_bReverse)
            forward = lastPos-point;
        else
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
            if(m_DeltaStep < 1.0f/90.0f)
                m_DeltaStep += m_AccelStep*moveScale;
            t += m_DeltaStep*moveScale;
            m_AngleInterp -= 1.0f/60.0f*3.0f;
        }
        else
        {
            if(m_DeltaStep < 1.0f/90.0f)
                m_DeltaStep += m_AccelStep*2.0f;
            t += m_DeltaStep*2.0f;
            m_AngleInterp -= 1.0f/30.0f*3.0f;
        }
        backupT = t;
        if(t >= 0.15f && prevT < 0.15f)
        {
            AudioManager::PlayEffect(AUDIO_CHAR_LOOP1);
            Rider::g_BikeAudio->PushState(BikeAudio::LOOP1);
        }
        if(t >= 0.5f && prevT < 0.5f)
        {
            if(m_bReverse)
            {
                m_TopTexture->removeFromParentAndCleanup(false);
                m_BottomTexture->removeFromParentAndCleanup(false);
                m_ccLayer->addChild(m_BottomTexture,2);
                m_ccLayer->addChild(m_TopTexture,2);
            }
            else
            {
                m_TopTexture->removeFromParentAndCleanup(false);
                m_BottomTexture->removeFromParentAndCleanup(false);
                m_frontLayer->addChild(m_BottomTexture,0);
                m_frontLayer->addChild(m_TopTexture,0);
            }
        }
        
        //vfx
        /*if(t >= 0.01f && prevT < 0.01f)
        {
            CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Loop 1A.png");
            sprite->setOpacity(0.0f);
            sprite->setPosition(ccp(m_TopTexture->getPosition().x-117,m_TopTexture->getPosition().y-72));
            CCSequence *sequence = CCSequence::create(CCFadeIn::create(0.1f),
                                                      CCDelayTime::create(0.2f),
                                                      CCFadeOut::create(0.1f),
                                                      CCCallFuncN::create(sprite, callfuncN_selector(CCNode::removeFromParentAndCleanup)),
                                                      NULL);
            sprite->runAction(sequence);
            m_frontLayer->addChild(sprite,1);
            
            sprite = CCSprite::createWithSpriteFrameName("ctm_Loop 1B.png");
            sprite->setOpacity(0.0f);
            sprite->setPosition(ccp(m_TopTexture->getPosition().x-53,m_TopTexture->getPosition().y-6));
            sequence = CCSequence::create(CCDelayTime::create(0.05f),
                                          CCFadeIn::create(0.1f),
                                          CCDelayTime::create(0.2f),
                                          CCFadeOut::create(0.1f),
                                          CCCallFuncN::create(sprite, callfuncN_selector(CCNode::removeFromParentAndCleanup)),
                                          NULL);
            sprite->runAction(sequence);
            m_frontLayer->addChild(sprite,1);
            
            sprite = CCSprite::createWithSpriteFrameName("CTM_Circular_Loop.png");
            sprite->setOpacity(0.0f);
            sequence = CCSequence::create(CCDelayTime::create(0.15f),
                        CCFadeIn::create(0.1f),
                        CCDelayTime::create(0.245f),
                        CCFadeOut::create(0.1f),
                        NULL);
            sprite->runAction(sequence);
            
            m_BikeLoopVFX = CCNode::create();
            m_frontLayer->addChild(m_BikeLoopVFX,3);
            
            sprite->setPosition(ccp(0.0f,100.0f));
            //sprite.rotation = 90.0f;
            m_BikeLoopVFX->addChild(sprite,0,1);
        }
        else if(t >= 0.99f && prevT < 0.99f)
        {
            m_BikeLoopVFX->removeFromParentAndCleanup(true);
            m_BikeLoopVFX = NULL;
        }
        if(m_BikeLoopVFX)
        {
            CCSprite *bikeBody = ((TextureObject*)Rider::g_MainBody->GetUserData())->GetSprite();
            m_BikeLoopVFX->setPosition(bikeBody->getPosition());
            m_BikeLoopVFX->setRotation(bikeBody->getRotation());
        }*/
        
        if(t>=1.0f)
        {
            if(m_bReverse)
                Rider::g_LauchDir.x = -50.0f;
            else
                Rider::g_LauchDir.x = 50.0f;
			Rider::g_LauchDir.y = 0.0f;
			Rider::g_DoLaunch = true;
            Rider::g_inLoop = false;
            m_bThisLoop = false;
            Rider::g_ScoreManager->FinishTrickGood(true);
            Rider::g_TrickState = 0;
        }
    }
    else
    {
        if(Rider::g_MainBody->GetPosition().x < (m_StartPos.x-OUTERSCALE))
        {
            if(!m_bLeftSide)
            {
                m_TopTexture->removeFromParentAndCleanup(false);
                m_BottomTexture->removeFromParentAndCleanup(false);
                m_ccLayer->addChild(m_BottomTexture,2);
                m_ccLayer->addChild(m_TopTexture,2);
                
                m_bLeftSide = true;
            }
        }
        if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x+OUTERSCALE))
        {
            if(m_bLeftSide)
            {
                m_TopTexture->removeFromParentAndCleanup(false);
                m_BottomTexture->removeFromParentAndCleanup(false);
                m_ccLayer->addChild(m_BottomTexture,2);
                m_ccLayer->addChild(m_TopTexture,2);
                
                m_bLeftSide = false;
            }
        }
    }
}

void SingleLoop::CreateSelf()
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
    m_ReverseTrigger = m_MainCollision->CreateFixture(&fd);
    
    
    //m_TurboTextures[0] = new TextureObject((char*)"ctm_SpeedBoost.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
    //m_TurboTextures[0]->SetTexturePosition(m_StartPos.x-10, m_StartPos.y);
    //m_TurboTextures[1] = new TextureObject((char*)"ctm_SpeedBoost.png",m_ccLayer,2,true,kTexture2DPixelFormat_RGBA4444);
    //m_TurboTextures[1]->SetTexturePosition(m_StartPos.x+10, m_StartPos.y);
    
    if(m_StartPos.y>1.0f)
        m_BottomTexture = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_1b.png");
    else
        m_BottomTexture = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_1b.png");
    m_BottomTexture->retain();
    
    m_BottomTexture->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_BottomTexture->setScale(1.0f);
    m_ccLayer->addChild(m_BottomTexture,2);
    
    
    if(m_StartPos.y>1.0f)
        m_TopTexture = CCSprite::createWithSpriteFrameName("ctm_UpperLoop_1a.png");
    else
        m_TopTexture = CCSprite::createWithSpriteFrameName("ctm_BigLoop_New_1a.png");
    m_TopTexture->retain();
    
    m_TopTexture->setPosition(CCPointMake(PTM_RATIO*(m_StartPos.x+9.5f),PTM_RATIO*(m_StartPos.y+7.8f)));
    m_TopTexture->setScale(1.0f);
    m_ccLayer->addChild(m_TopTexture,2);
    
    
    m_Spline = NULL;
    
    if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x+OUTERSCALE))
        m_bLeftSide = true;
    else
        m_bLeftSide = false;
}
void SingleLoop::DestroySelf()
{
	if(m_created)
	{
        //m_TurboTextures[0]->ReleaseTexture();
		//delete m_TurboTextures[0];
        //m_TurboTextures[1]->ReleaseTexture();
		//delete m_TurboTextures[1];
        
        m_TopTexture->autorelease();
        m_BottomTexture->autorelease();
        m_TopTexture->removeFromParentAndCleanup(true);
        m_BottomTexture->removeFromParentAndCleanup(true);
		m_world->DestroyBody(m_MainCollision);
        if(m_Spline)
        {
            delete m_Spline;
            m_Spline = NULL;
        }
	}
}
bool SingleLoop::HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB)
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
            m_bReverse = false;
            lastPos = Rider::g_MainBody->GetPosition();
            Rider::g_inLoop = true;
            m_bThisLoop = true;
            m_DeltaStep = 1.0f/120.0f;
            m_AccelStep = (1.0f/90.0f - 1.0f/120.0f)/10.0f;
            
            t = m_DeltaStep;
            
            b2Vec2 points[6] =
            {
                
                //b2Vec2(10.0f+m_StartPos.x-10.0f,-2.5f+m_StartPos.y+5.0f),
                b2Vec2(lastPos.x,lastPos.y),
                b2Vec2(0.0f+m_StartPos.x+6.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f,-2.5f+m_StartPos.y+20.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f,-2.5f+m_StartPos.y+20.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f,m_StartPos.y+1.25f+0.3f),
            };
            
            if(m_Spline)
                delete m_Spline;
            m_Spline = new Spline(points, 6);
            
            m_TopTexture->removeFromParentAndCleanup(false);
            m_BottomTexture->removeFromParentAndCleanup(false);
            m_ccLayer->addChild(m_TopTexture,2);
            m_ccLayer->addChild(m_BottomTexture,2);
            
            Rider::g_ScoreManager->SetLoops(1);
            //[Options PlayEffect:AUDIO_LOOP_1];
            return false;
        }
	}
    
    /*if(!Rider::g_inLoop && (m_ReverseTrigger == fixtureA || m_ReverseTrigger == fixtureB))
	{
        if(m_ReverseTrigger == fixtureA && fixtureB->GetFilterData().categoryBits == 0x7fff)
            return false;
        if(m_ReverseTrigger == fixtureB && fixtureA->GetFilterData().categoryBits == 0x7fff)
            return false;
        
        b2Vec2 vel = Rider::g_MainBody->GetLinearVelocity();
		float angle = Rider::g_MainBody->GetAngle();
        while(angle > b2_pi*2.0f) angle -= b2_pi*2.0f;
        while(angle < 0) angle += b2_pi*2.0f;
		bool goodAngle = (angle < 0.15f || angle > (b2_pi*2.0f-0.15f));
        
        b2Vec2 pos = Rider::g_MainBody->GetPosition();
        bool goodY = (pos.y < (m_StartPos.y+3.75f) && pos.y > (m_StartPos.y+1.25f));
        
        if(vel.x < -20.0f && goodAngle && goodY)
        {
            m_EntryForward = angle;
            m_AngleInterp = 1.0f;
            m_bReverse = true;
            lastPos = Rider::g_MainBody->GetPosition();
            Rider::g_inLoop = true;
            m_bThisLoop = true;
            m_DeltaStep = 1.0f/120.0f;
            m_AccelStep = (1.0f/90.0f - 1.0f/120.0f)/10.0f;
            
            t = m_DeltaStep;
            
            
            b2Vec2 points[6] =
            {
                
                b2Vec2(lastPos.x,lastPos.y),
                b2Vec2(0.0f+m_StartPos.x-6.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f,-2.5f+m_StartPos.y+20.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f,-2.5f+m_StartPos.y+20.0f),
                b2Vec2(0.0f+m_StartPos.x+6.0f,-2.5f+m_StartPos.y+6.0f),
                b2Vec2(0.0f+m_StartPos.x-6.0f,m_StartPos.y+1.25f+0.3f),
                //b2Vec2(0.0f+m_StartPos.x+8.0f,lastPos.y+0.3f),
            };
            
            if(m_Spline)
                delete m_Spline;
            m_Spline = new Spline(points, 6);
            
            
            [m_TopTexture removeFromParentAndCleanup:NO];
            [m_BottomTexture removeFromParentAndCleanup:NO];
            [m_frontLayer addChild:m_TopTexture z:0];
            [m_frontLayer addChild:m_BottomTexture z:0];
            
            [Rider::g_ScoreManager SetLoops:1];
            //[Options PlayEffect:AUDIO_LOOP_1];
            return true;
        }
	}*/
    
    
	return false;
}