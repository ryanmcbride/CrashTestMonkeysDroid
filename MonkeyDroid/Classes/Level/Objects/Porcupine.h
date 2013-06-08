//
//  Trampoline.h
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __PORCUPINE_H__
#define __PORCUPINE_H__

#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class Porcupine : public TrackObject
{
public:
	Porcupine(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, float scale = 1.0f);
	virtual ~Porcupine();
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