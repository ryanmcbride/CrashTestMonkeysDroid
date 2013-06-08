/*
 *  Ramp.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __RAMP_H__
#define __RAMP_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Ramp : public TrackObject
{
public:
	enum Type
	{
		ORIGINAL=0,
		FWD,
		FWD_LOW,
		FWD_STEEP,
		REV,
		REV_LOW,
		REV_STEEP,
		ARCH_SMALL,
		WALL_FRONT,
		WALL_BACK,
        TOP_FWD,
		TOP_FWD_LOW,
		TOP_FWD_STEEP,
		TOP_REV,
		TOP_REV_LOW,
		TOP_REV_STEEP,
		MAX_TYPES
	};
	//Ramp(b2World *world, CCNode *CCLayer, b2Vec2 *startPos, float scale = 1.0f);
	Ramp(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, Type intype, int sort=0);
    Ramp(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, Type intype, cocos2d::CCNode *frontLayer, int sort=0);
	virtual ~Ramp();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	b2Body *GetBody(){return m_MainCollision;}
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCNode *m_frontLayer;
	int m_sort;
	b2Body *m_MainCollision;
	TextureObject *m_Texture;
	b2Vec2 m_StartPos;
	float m_Scale;
	Type m_Type;
    cocos2d::CCSprite *m_Overlay;
    cocos2d::CCSprite *m_WallRamp;
    bool m_bLeftSide;
};

#endif