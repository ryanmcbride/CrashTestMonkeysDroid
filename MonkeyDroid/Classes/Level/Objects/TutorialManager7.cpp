//
//  TutorialManager.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "TutorialManager7.h"
#include "../Rider/Rider.h"
#include "../Level.h"
#include "Ramp.h"
#include "Platform.h"
#include "Bridge.h"
#include "FinishLine.h"
#include "Pickup.h"
#include "Trigger.h"
#include "../../ScreenHelper.h"


using namespace cocos2d;

extern float g_DeltaTime;
#define TUTORIAL_TAG 0xbadbad

TutorialManager7::TutorialManager7(Track *track, CCNode *backLayer, b2World* world, b2Vec2 *startPos):
TrackObject(startPos->x, 10.0f)
{
    m_world = world;
	m_Track = track;
	m_StartPos = *startPos;
    m_frontLayer = NULL;
    m_State = 0;
    m_backLayer = backLayer;
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("Tutorial.plist","Tutorial.pvr.ccz");
    m_Timer = 0.0f;
}
TutorialManager7::~TutorialManager7()
{
    Trigger::TriggerFlags = 0;
}
void TutorialManager7::CreateSelf()
{
	if(m_created) return;
	m_State = 0;
}
void TutorialManager7::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;

    m_Timer += 1.0f/60.0f;
    if(m_frontLayer == NULL /*&& m_Timer > 5.0f*/)
    {
        m_frontLayer = Level::getHUD();
      
        //[GameHUD SetPauseType:1];
        //[[GameHUD GetSelf] pauseButtonTapped:NULL];
    }
    
    //if(Rider::g_isFinished && m_frontLayer)
    //{
    //    [m_frontLayer removeChildByTag:TUTORIAL_TAG cleanup:YES];
    //    m_frontLayer = NULL;
    //}
    //tutorial follows the action
    m_xpos = xpos/PTM_RATIO;    
}
void TutorialManager7::DestroySelf()
{
	if(m_created)
	{
    }
}
