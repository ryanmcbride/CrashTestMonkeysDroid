//
//  SpawnPoint.h
//  CTM
//
//  Created by Ryan McBride on 5/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef __SPAWN_POINT_H__
#define __SPAWN_POINT_H__

#include "cocos2d.h"
#include "Box2d.h"
#include "TextureObject.h"
#include "TrackObject.h"

class SpawnPoint : public TrackObject
{
public:
	SpawnPoint(b2World *world, cocos2d::CCNode *ccLayer, b2Vec2 *startPos, float scale = 1.0f);
	virtual ~SpawnPoint();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
protected:
	cocos2d::CCNode *m_ccLayer;
	cocos2d::CCSprite *m_Sprite;
	b2Vec2 m_StartPos;
};
#endif// __SPAWN_POINT_H__