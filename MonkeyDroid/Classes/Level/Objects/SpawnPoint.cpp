//
//  SpawnPoint.mm
//  CTM
//
//  Created by Ryan McBride on 5/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "SpawnPoint.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"

extern int g_TutorialState;

using namespace cocos2d;

SpawnPoint::SpawnPoint(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, float scale):
TrackObject(startPos->x, 10.0f)
{
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
}
SpawnPoint::~SpawnPoint()
{
    
}
void SpawnPoint::CreateSelf()
{
	if(m_created) return;
	
    if(g_TutorialState)
        m_Sprite = CCSprite::createWithSpriteFrameName("ctm_StartStrip_Tutorial.png");
    else
        m_Sprite = CCSprite::createWithSpriteFrameName("ctm_Startpad.png");
    
	m_Sprite->setPosition(CCPointMake(m_StartPos.x*PTM_RATIO,0.0f));
	m_ccLayer->addChild(m_Sprite,2);
}
void SpawnPoint::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
    if(m_created)
    {
        if(Rider::g_MainBody->GetPosition().x < (m_StartPos.x-3.0f))
        {
            Rider::g_LauchDir.y = 0.0f;
            Rider::g_LauchDir.x = 50.0f;
            Rider::g_DoLaunch = true;
            Rider::g_ScoreManager->AddScore(-100);
        }
        float zoom = ScreenHelper::getCameraZoom();
        float scale = ScreenHelper::getTextureScale();
		m_Sprite->setPosition(CCPointMake( m_StartPos.x * PTM_RATIO * zoom, 0.0f));        
		m_Sprite->setScale(scale*zoom);
    }
}
void SpawnPoint::DestroySelf()
{
	if(m_created)
	{
		m_Sprite->removeFromParentAndCleanup(true);
	}
}


