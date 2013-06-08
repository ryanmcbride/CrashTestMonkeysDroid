//
//  DummyRider.mm
//  CTM
//
//  Created by Ryan McBride on 6/1/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "DummyRider.h"
#include "Rider.h"
#include "../../FrontEnd/SaveLoad.h"
//#import "FireMonkey.h"
#include "SimpleAudioEngine.h"
#include "Fire.h"

USING_NS_CC;

extern bool g_bIsRetina;
extern bool g_PermanentFire;

DummyRider::DummyRider(b2World *world, CCLayer* layer)
{
	m_Index = 0;
	m_Monkey = NULL;
	m_Layer = layer;
	m_World = world;
	m_IsCrashed = false;
    m_ExhaustFX = NULL;

    const char *bodyName = NULL;
    
    switch(SaveLoad::GetRiderNumber())
    {
        default:
        case 0:
            bodyName = "Default";
            break;
        case 1:
            bodyName = "Cop";
            break;
        case 2:
            bodyName = "Barb";
            break;
        case 3:
            bodyName = "Elvis";
            break;
        case 4:
            bodyName = "Sock";
            break;
    };
    
    m_BikeFire = new BikeFire(layer,1.0f/15.0f);
    m_WheelFire[0] = new WheelFire(layer,1.0f/15.0f);
    m_WheelFire[1] = new WheelFire(layer,1.0f/15.0f,false);
    if(g_PermanentFire)
        m_BikeFire->SetVisible(true);
    
    const char *bikeExt = SaveLoad::GetBikeExt();
    if(strcmp(bikeExt,"_SciFi")==0)
    {
        m_ExhaustFX = new ExhaustFX(layer,1.0f/30.0f,1);
    }
    if(strcmp(bikeExt,"_Electric")==0)
    {
        m_ExhaustFX = new ExhaustFX(layer,1.0f/15.0f,0);
    }
    
	m_AnimSet = new AnimationSet(layer,1.0f/24.0f);
    char name[64];
    sprintf(name,"ctm_%s_RideCycle",bodyName);
    m_AnimSet->AddIdle(name,name,23,-0.3f,1.4f);
    
    if(SaveLoad::m_SaveData.trickLockLevel == 3)
    {
        sprintf(name,"ctm_%s_Trick7",bodyName);
        m_AnimSet->AddRunandHold(name,name,39,0.85f,1.8f);
        sprintf(name,"ctm_%s_Trick8",bodyName);
        m_AnimSet->AddRunandHold(name,name,43,-0.5f,1.5f);
        sprintf(name,"ctm_%s_Trick9",bodyName);
        m_AnimSet->AddRunandHold(name,name,36,-0.95f,2.5f);
    }
    else if(SaveLoad::m_SaveData.trickLockLevel == 2)
    {
        sprintf(name,"ctm_%s_Trick5",bodyName);
        m_AnimSet->AddRunandHold(name,name,30,-0.8f,1.9f);
        sprintf(name,"ctm_%s_Trick6",bodyName);
        m_AnimSet->AddRunandHold(name,name,36,0.05f,1.65f);
        sprintf(name,"ctm_%s_Trick7",bodyName);
        m_AnimSet->AddRunandHold(name,name,39,0.85f,1.8f);
    }
    else if(SaveLoad::m_SaveData.trickLockLevel == 1)
    {
        sprintf(name,"ctm_%s_Trick3",bodyName);
        m_AnimSet->AddRunandHold(name,name,35,-0.8f,1.5f);
        sprintf(name,"ctm_%s_Trick4",bodyName);
        m_AnimSet->AddRunandHold(name,name,35,-0.95f,3.0f);
        sprintf(name,"ctm_%s_Trick5",bodyName);
        m_AnimSet->AddRunandHold(name,name,30,-0.8f,1.9f);
    }
    else
    {
        sprintf(name,"ctm_%s_Trick1",bodyName);
        m_AnimSet->AddRunandHold(name,name,35,-0.35f,1.8f);
        sprintf(name,"ctm_%s_Trick2",bodyName);
        m_AnimSet->AddRunandHold(name,name,28,0.59f,1.9f);
        sprintf(name,"ctm_%s_Trick3",bodyName);
        m_AnimSet->AddRunandHold(name,name,35,-0.8f,1.5f);
    }
}
DummyRider::~DummyRider()
{
	if(m_Monkey)
		delete m_Monkey;
	delete m_AnimSet;
    delete m_BikeFire;
    delete m_WheelFire[0];
    delete m_WheelFire[1];
    if(m_ExhaustFX)
        delete m_ExhaustFX;
}
b2Vec2 DummyRider::GetCameraFocus()
{
    return m_Monkey->Chest->GetWorldCenter();
}
void DummyRider::Step()
{
	if(!m_IsCrashed)
	{
        if(m_ExhaustFX)
            m_ExhaustFX->Update();
        m_BikeFire->Update();
		m_WheelFire[0]->Update();
		m_WheelFire[1]->Update();
		m_AnimSet->Step();
		CCPoint position = CCPointMake(Rider::g_MainBody->GetWorldCenter().x,Rider::g_MainBody->GetWorldCenter().y);
		m_AnimSet->SetPosition(position ,Rider::g_MainBody->GetAngle());
		
		if(Rider::g_OnFire>0.0f)
		{
			m_WheelFire[0]->SetVisible(true);
			m_WheelFire[1]->SetVisible(true);
            Rider::g_OnFire -= (1.0f/60.0f)/3.0f;
            if(Rider::g_OnFire<=0.0f)
            {
                m_WheelFire[0]->SetVisible(false);
                m_WheelFire[1]->SetVisible(false);
            }
		}
	}
}
bool DummyRider::SetTrick(int index)
{
	if(index == m_Index) return false;
    //if(!m_AnimSet->IsCurrentAnimDone())
    //    return false;
    
	if(index == AnimationSet::IDLE)
	{
		m_AnimSet->QueueAnim(AnimationSet::IDLE);
        m_Index = index;
        return false;
	}
    
	if(index == 1)
	{
        m_AnimSet->QueueAnim(AnimationSet::TRICK1);
        m_AnimSet->QueueAnim(AnimationSet::IDLE);
	}
	if(index == 2)
	{
		m_AnimSet->QueueAnim(AnimationSet::TRICK2);
        m_AnimSet->QueueAnim(AnimationSet::IDLE);
	}
	if(index == 3)
	{
		m_AnimSet->QueueAnim(AnimationSet::TRICK3);
        m_AnimSet->QueueAnim(AnimationSet::IDLE);
	}
	
	m_Index = index;
    return true;
}
void DummyRider::Crash()
{
	if(m_Monkey == NULL)
	{
        m_AnimSet->SetVisible(false);
        if(m_ExhaustFX)
            m_ExhaustFX->SetVisible(false);
		
		m_BikeFire->SetVisible(false);
		m_WheelFire[0]->SetVisible(false);
		m_WheelFire[1]->SetVisible(false);

		b2Vec2 startPos = Rider::g_MainBody->GetWorldCenter();
		b2Transform xform = Rider::g_MainBody->GetTransform();
		startPos.y += 1.0f;
        if(!Rider::g_WaterCrash)
		{
            m_Monkey = new Monkey(m_World,m_Layer, startPos, xform);
            m_Monkey->SetVelocity(Rider::g_MainBody->GetLinearVelocity());
        }
        m_IsCrashed = true;
	}
}
void DummyRider::HandlePauseChange(bool pause)
{
    if(m_ExhaustFX)
        m_ExhaustFX->Pause(pause);
    m_WheelFire[0]->Pause(pause);
    m_WheelFire[1]->Pause(pause);
    m_BikeFire->Pause(pause);
    
    m_AnimSet->HandlePauseChange(pause);
}