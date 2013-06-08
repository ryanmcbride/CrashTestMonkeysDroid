/*
 *  Ramp.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#include "DrawTexture.h"
#include "TextureObject.h"
#import "GameLevel.h"

DrawTexture::DrawTexture(b2World *world, CCNode *ccLayer, b2Vec2 *startPos, NSString *filename):
TrackObject(startPos->x, 10.0f)
{
    m_filename = [[NSString stringWithString: filename] retain];
	m_sprite = nil;
    m_ccLayer = ccLayer;
    m_StartPos = *startPos;
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"SkyAssets.plist"textureFile:@"SkyAssets.pvr.ccz"];
}


DrawTexture::~DrawTexture()
{
	if(m_created && m_sprite)
    {
        [m_sprite removeFromParentAndCleanup:YES];
    }
    [m_filename release];
}
void DrawTexture::CreateSelf()
{
	if(m_created) return;
	
    
    m_sprite = [CCSprite spriteWithSpriteFrameName:m_filename];
    m_sprite.position = CGPointMake(PTM_RATIO*(m_StartPos.x),PTM_RATIO*(m_StartPos.y));
	[m_ccLayer addChild:m_sprite];
}
void DrawTexture::DestroySelf()
{
	if(m_created && m_sprite)
	{
        [m_sprite removeFromParentAndCleanup:YES];
        m_sprite = nil;
		m_created = false;
	}
}

