/*
 *  Ramp.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "Ramp.h"
#include "TextureObject.h"
#include "../Rider/Rider.h"
#include "../../ScreenHelper.h"

USING_NS_CC;

struct RampDef
{
	float yOffset;
	b2Vec2 points[3];
	char*	texturename;
};
static RampDef s_RampDefs[Ramp::MAX_TYPES] = 
{
	{
		27.0f/PTM_RATIO,
		{
			b2Vec2(-(39.0f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),(30.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_01.png"
	},
	{
		27.0f/PTM_RATIO,
		{
			b2Vec2(-(39.0f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),(30.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_FWD.png"
	},
	{
		20.0f/PTM_RATIO,
		{
			b2Vec2(-(89.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((53.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((53.5f/PTM_RATIO),(25.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_FWD_Low.png"
	},
	{
		37.0f/PTM_RATIO,
		{
			b2Vec2(-(30.0f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((30.5f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((30.5f/PTM_RATIO),(40.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_FWD_Steep.png"
	},
	{
		27.0f/PTM_RATIO,
		{
			b2Vec2(-(39.0f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2(-(39.0f/PTM_RATIO),(30.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_Reverse.png"
	},
	{
		20.0f/PTM_RATIO,
		{
			b2Vec2(-(89.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((48.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2(-(48.5f/PTM_RATIO),(25.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_Reverse_Low.png"
	},
	{
		37.0f/PTM_RATIO,
		{
			b2Vec2(-(30.0f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((30.5f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2(-(30.5f/PTM_RATIO),(40.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_Reverse_Steep.png"
	},
	{
		15.0f/PTM_RATIO,
		{
			b2Vec2(-(44.0f/PTM_RATIO),-(15.0f/PTM_RATIO)),
			b2Vec2((44.0f/PTM_RATIO),-(15.0f/PTM_RATIO)),
			b2Vec2(-(0.0f/PTM_RATIO),(25.0f/PTM_RATIO))
		},
		(char*)"ctm_Ramp_Arch_Small.png"
	},
	{
		100.0f/PTM_RATIO,
		{
			b2Vec2(-(150.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((120.5f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((120.5f/PTM_RATIO),(120.0f/PTM_RATIO))
		},
		(char*)"ctm_Wall_frontramp_01.png"
	},
	{
		100.0f/PTM_RATIO,
		{
			b2Vec2(-(175.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2((134.0f/PTM_RATIO),-(100.0f/PTM_RATIO)),
			b2Vec2(-(175.0f/PTM_RATIO),(120.0f/PTM_RATIO))
		},
		(char*)"ctm_Wall_backramp_01.png"
	},
    {
		27.0f/PTM_RATIO,
		{
			b2Vec2(-(39.0f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),(30.0f/PTM_RATIO))
		},
		(char*)"ctm_TopRamp_FWD.png"
	},
	{
		10.0f/PTM_RATIO,
		{
			b2Vec2(-(43.0f/PTM_RATIO),-(12.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(12.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),(17.0f/PTM_RATIO))
		},
		(char*)"ctm_TopRamp_FWD_Low.png"
	},
	{
		37.0f/PTM_RATIO,
		{
			b2Vec2(-(30.0f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((30.5f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((30.5f/PTM_RATIO),(40.0f/PTM_RATIO))
		},
		(char*)"ctm_TopRamp_FWD_Steep.png"
	},
	{
		27.0f/PTM_RATIO,
		{
			b2Vec2(-(39.0f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2((38.5f/PTM_RATIO),-(27.0f/PTM_RATIO)),
			b2Vec2(-(39.0f/PTM_RATIO),(30.0f/PTM_RATIO))
		},
		(char*)"ctm_TopRamp_Reverse.png"
	},
	{
		20.0f/PTM_RATIO,
		{
			b2Vec2(-(89.0f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2((48.5f/PTM_RATIO),-(20.0f/PTM_RATIO)),
			b2Vec2(-(48.5f/PTM_RATIO),(25.0f/PTM_RATIO))
		},
		(char*)"ctm_TopRamp_Reverse_Low.png"
	},
	{
		37.0f/PTM_RATIO,
		{
			b2Vec2(-(30.0f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2((30.5f/PTM_RATIO),-(37.0f/PTM_RATIO)),
			b2Vec2(-(30.5f/PTM_RATIO),(40.0f/PTM_RATIO))
		},
		(char*)"ctm_TopRamp_Reverse_Steep.png"
	},
};
Ramp::Ramp(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, Type intype, CCNode *frontLayer, int sort):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_Scale = 1.0f;
	m_Type = intype;
    m_Overlay = NULL;
    m_frontLayer = frontLayer;
    m_sort = sort;
}
Ramp::Ramp(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, Type intype, int sort):
TrackObject(startPos->x, 10.0f)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_StartPos = *startPos;
	m_Scale = 1.0f;
	m_Type = intype;
    m_Overlay = NULL;
    m_sort = sort;
    m_WallRamp = NULL;
}

Ramp::~Ramp()
{
	if(m_created)
		delete m_Texture;
}
void Ramp::CreateSelf()
{
	if(m_created) return;
	
	b2PolygonShape triangle;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	triangle.Set(s_RampDefs[m_Type].points,3);
	
	
	fd.shape = &triangle;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	
	bd.position.Set(m_StartPos.x, m_StartPos.y+s_RampDefs[m_Type].yOffset);
	
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);
	TextureObject *tex = new TextureObject(s_RampDefs[m_Type].texturename,m_ccLayer,m_sort,true,kTexture2DPixelFormat_Default);
	tex->SetTextureScale(m_Scale,m_Scale);
	m_MainCollision->SetUserData(tex);
    m_Texture = tex;
    
/*    if(m_Type==WALL_FRONT)
    {
        m_Overlay = [CCSprite spriteWithSpriteFrameName:@"ctm_Wall_frontramp_01_Overlay_Fade.png"];
        [m_frontLayer addChild:m_Overlay z:1];
        m_Overlay.position = ccp(m_MainCollision->GetPosition().x*PTM_RATIO,m_MainCollision->GetPosition().y*PTM_RATIO);
        m_bLeftSide = true;
        m_WallRamp = nil;
    }*/
	
}
void Ramp::Update(float xpos,float ypos)
{
    TrackObject::Update(xpos,ypos);
	if(!m_created) return;
    
/*    if(m_Type==WALL_FRONT)
    {
        if(Rider::g_MainBody->GetPosition().x < (m_StartPos.x+8.5))
        {
            if(!m_bLeftSide)
            {
                if(m_WallRamp)
                {
                    TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
                    texObject->GetSprite().visible = YES;
                    [m_WallRamp removeFromParentAndCleanup:YES];
                    m_WallRamp = nil;
                }
                m_bLeftSide = true;
            }
        }
        if(Rider::g_MainBody->GetPosition().x > (m_StartPos.x+8.6))
        {
            if(m_bLeftSide)
            {
                if(!m_WallRamp)
                {
                    m_WallRamp = [CCSprite spriteWithSpriteFrameName:@"ctm_Wall_frontramp_01.png"];
                    [m_frontLayer addChild:m_WallRamp z:0];
                    m_WallRamp.position = ccp(m_MainCollision->GetPosition().x*PTM_RATIO,m_MainCollision->GetPosition().y*PTM_RATIO);
                }
                TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
                texObject->GetSprite().visible = NO;
                m_bLeftSide = false;
            }
        }
    }*/
}

void Ramp::DestroySelf()
{
	if(m_created)
	{
		TextureObject* texObject = (TextureObject*)m_MainCollision->GetUserData();
		texObject->ReleaseTexture();
		delete texObject;
        m_Texture = NULL;
		m_world->DestroyBody(m_MainCollision);
        
/*        if(m_WallRamp)
        {
            [m_WallRamp removeFromParentAndCleanup:YES];
            m_WallRamp = nil;
        }*/
	}
}

