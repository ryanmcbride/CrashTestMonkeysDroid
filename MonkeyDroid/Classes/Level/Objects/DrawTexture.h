/*
 *  Ramp.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#pragma once
#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class DrawTexture : public TrackObject
{
public:
	DrawTexture(b2World *world, CCNode *CCLayer, b2Vec2 *startPos, NSString *filename);
	virtual ~DrawTexture();
	virtual void CreateSelf();
	virtual void DestroySelf();
protected:
    NSString *m_filename;
    CCSprite *m_sprite;
    CCNode *m_ccLayer;
    b2Vec2 m_StartPos;
};