/*
 *  Rider.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "Rider.h"
//#include "Motorcycle.h"
#include "DirtBike.h"
#include "../../ScreenHelper.h"


extern int g_TutorialState;
//hmmmm not sure this is right
b2Vec2 Rider::g_LauchDir(0.0f,0.0f);
float Rider::g_ForceCrash = -1.0f;
int Rider::g_Score = 0.0f;
int Rider::g_Pickups = 0;
float Rider::g_OnFire = 0.0f;
int Rider::g_TrickState = 0;
bool Rider::g_DoLaunch = false;
bool Rider::g_inLoop = false;
b2Body* Rider::g_MainBody = NULL;
b2Vec2 Rider::g_startPos(0.0f,0.0f);
bool Rider::g_isFinished = false;
bool Rider::g_isCrashed = false;
bool Rider::g_WaterCrash = false;
bool Rider::g_isInAir = false;
ScoreManager* Rider::g_ScoreManager = NULL;
BikeAudio *Rider::g_BikeAudio = NULL;
bool Rider::s_bWheelsTouch = false;


Vehicle *Rider::s_Vehicle = NULL;
void Rider::FixWheelPos()
{
    DirtBike *dirtBike = (DirtBike *)s_Vehicle;
    b2Transform xform = g_MainBody->GetTransform();
    
    b2Vec2 fVec = dirtBike->m_FrontWheelColCenter;
    fVec.x -= 0.2f;
    fVec.y += 0.2f;
    b2Vec2 fPos = b2Mul(xform,fVec);
    
    
    b2Vec2 bVec = dirtBike->m_BackWheelColCenter;
    bVec.x += 0.2f;
    bVec.y += 0.2f;
    b2Vec2 bPos = b2Mul(xform,bVec);
    
    b2Body *fwheel = dirtBike->GetWheelFront();
    b2Body *bwheel = dirtBike->GetWheelBack();
    
    fwheel->SetTransform(fPos,fwheel->GetAngle());
    bwheel->SetTransform(bPos,bwheel->GetAngle());
        
    return;
}
Rider::Rider(b2World *world, CCNode *ccLayer)
{
	m_CCLayer = ccLayer;
	m_world = world;
	
	b2Vec2 gravity(0.0f,-20.0f);
	
	//b2Vec2 gravity(0.0f,0.0f);
	
	m_world->SetGravity(gravity);
	
	b2Vec2 startPos = g_startPos;
	startPos.y += 2.5f;
	m_Vehicle = new DirtBike(world,(CCLayer*)ccLayer,startPos);
	g_MainBody = m_Vehicle->GetMainBody();
    s_Vehicle = m_Vehicle;
	g_DoLaunch = false;
	g_inLoop = false;
	g_LauchDir.Set(0.0f,0.0f);
	g_isFinished = false;
	g_isCrashed = false;
    g_WaterCrash = false;
	g_TrickState = 0;
	g_Score = 0.0f;
	g_Pickups = 0;
	g_OnFire = 0.0f;
	cameraInterpolateCount = -1.0f;
    m_bTrickedAlready = 0.0f;
    s_bWheelsTouch = false;

	g_BikeAudio = new BikeAudio();
	
	m_DummyRider = new DummyRider(m_world,(CCLayer*)m_CCLayer);
	m_TrickTimer = 0.0f;
	m_TrickState = 0;
	m_CrashTimer = 5.0f;
	
	m_doCrash = false;
	m_LastCamera = PTM_RATIO*startPos+b2Vec2(-140.0f,-160.0f);
}
Rider::~Rider()
{
	if(m_DummyRider)
		delete m_DummyRider;
	delete m_Vehicle;
	m_Vehicle = NULL;
    
    delete g_BikeAudio;
    g_BikeAudio = NULL;
}
void Rider::BeginContact(b2Contact* contact)
{
	m_Vehicle->BeginContact(contact);
}
void Rider::EndContact(b2Contact* contact)
{
	m_Vehicle->EndContact(contact);
}

void Rider::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
}

void Rider::GetCameraPosition(b2Vec2 &outVec)
{
	b2Vec2 offset;
	b2Vec2 center;
	
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
	if(g_isFinished && !g_isCrashed)
	{
		center = m_LastCamera;
	}
	else if(g_isCrashed && m_DummyRider)
	{
        if(g_WaterCrash)
            center = m_LastCamera;//g_MainBody->GetWorldCenter();
        else
            center = m_DummyRider->GetCameraFocus();
	}
	else 
	{
		if(cameraInterpolateCount <= 0.0f)
		{
			center = m_Vehicle->GetMainBody()->GetWorldCenter();
		}
		else
		{
			cameraInterpolateCount -= 0.1f/(10.0f*scale);
			center.x = m_Vehicle->GetMainBody()->GetWorldCenter().x*(1.0f-cameraInterpolateCount) + m_LastCamera.x*cameraInterpolateCount;
			center.y = m_Vehicle->GetMainBody()->GetWorldCenter().y*(1.0f-cameraInterpolateCount) + m_LastCamera.y*cameraInterpolateCount;
		}

	}
	offset = center;
	offset.x = 0.0f;
	offset.y *= -10.0f*scale;
	if(offset.y < -140.0f*scale)
		offset.y = -140.0f*scale;
	outVec = (PTM_RATIO*center)+b2Vec2(-140.0f*scale,-100.0f*scale) + offset;
	
	if(outVec.y < -90.0f*scale)//bottom of the screen
		outVec.y = -90.0f*scale;
	
	m_LastCamera = center;
}
void Rider::Step(int loop)
{
	//if(m_TrickState != 0 && !m_Vehicle->isInAir())
	//	m_doCrash = true;
	if(m_CrashTimer <= 0.0f && m_Vehicle->getRiderTest())
		m_doCrash = true;
	if(m_doCrash)
		Crash();
	m_Vehicle->Step(loop);
	m_DummyRider->Step();
	
	if(m_TrickTimer > 0.0f)
	{
		m_TrickTimer -= 0.01666f/3.0f;
		if(m_TrickTimer <= 0.0f)
		{
			m_TrickState = 0;
			m_DummyRider->SetTrick(m_TrickState);
		}
	}
	
	if(!g_isCrashed && m_CrashTimer > 0.0f)
	{
		m_CrashTimer -= 0.01666f/3.0f;
	}
	
	if(g_ForceCrash > 0.0f)
	{
		g_ForceCrash -= 0.01666f/3.0f;

		if(g_ForceCrash <= 0.0f)
		{
			m_doCrash = true;
		}
	}
    g_isInAir = m_Vehicle->isInAir();
    
    if(m_bTrickedAlready>0.0f)
        m_bTrickedAlready -= 0.01666f/3.0f;
}
void Rider::Crash()
{
//rpm    if(g_TutorialState)
//    {
//        m_doCrash = false;
//        return;
//    }
    if(Rider::g_isFinished)
    {
        m_doCrash = false;
        return;        
    }
	if(!Rider::g_isCrashed)
	{
		m_doCrash = false;
		Rider::g_isFinished = true;
		Rider::g_isCrashed = true;
		m_Vehicle->Crash();
		m_DummyRider->Crash();
		m_TrickState = 0;
		m_CrashTimer = 5.0f;
	}
}

bool Rider::Trick(int trickNum)
{
	if(m_bTrickedAlready>0.0f)
		return false;
    
    if(trickNum && !(Rider::g_isInAir || Rider::g_inLoop))
    {
        return false;
    }
    
    if(g_ScoreManager->DuringLockout())
        return false;
    
    bool didTrick = m_DummyRider->SetTrick(trickNum);
    if(didTrick)
    {
        m_TrickTimer = 0.2f;
        m_TrickState = trickNum;
        m_bTrickedAlready = 1.25f;
        
        //if(g_TrickState < m_TrickState)
        g_TrickState = m_TrickState;
        g_ScoreManager->SetTrick(g_TrickState);
    }
    return didTrick;
}
void Rider::AirSpin(float val)
{
	m_Vehicle->AirSpin(val);
}
void Rider::GasAndBrake(float val, bool preStart)
{
	if(!Rider::g_isFinished)
	   m_Vehicle->GasAndBrake(val,preStart);
}
void Rider::HandlePauseChange(bool pause)
{
    m_DummyRider->HandlePauseChange(pause);
}
