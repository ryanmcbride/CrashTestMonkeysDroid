/*
 *  Ramp.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/26/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */

#ifndef __CRATE_H__
#define __CRATE_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Crate : public TrackObject
{
public:
    enum Type
	{
		ORIGINAL=0,
		BEACH_BALL,
		MAX_TYPES
	};
	Crate(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, float scale = 1.0f);
	Crate(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, Type type, int sort);
	virtual ~Crate();
	virtual void CreateSelf();
	virtual void DestroySelf();
	virtual void Update(float xpos,float ypos){TrackObject::Update(xpos,ypos);Step(xpos);}
	void Step(float xpos);
	b2Body *GetBody(){return m_MainCollision;}
    bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	TextureObject *m_Texture;
    TextureObject *m_TextureHighlight;
	b2Vec2 m_StartPos;
	float m_Scale;
    Type m_type;
    int m_beachBallTexNum;
    float m_HitDelay;
    int m_sort;
};
#endif