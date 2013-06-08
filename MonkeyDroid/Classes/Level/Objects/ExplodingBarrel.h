//
//  ExplodingBarrel.h
//  CTM
//
//  Created by Ryan McBride on 1/11/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __EXPLODING_BARREL_H__
#define __EXPLODING_BARREL_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class ExplodingBarrel : public TrackObject
{
public:
	ExplodingBarrel(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, float scale = 1.0f);
	virtual ~ExplodingBarrel();
	virtual void CreateSelf();
	virtual void DestroySelf();
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	b2Vec2 m_StartPos;
	TextureObject *m_Texture;
	bool m_Exploded;
};
#endif