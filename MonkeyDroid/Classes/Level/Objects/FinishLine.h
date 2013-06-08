//
//  FinishLine.h
//  CTM
//
//  Created by Ryan McBride on 5/20/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef __FINISH_LINE_H__
#define __FINISH_LINE_H__
#include "cocos2d.h"
#include "Box2d.h"
#include "TrackObject.h"
#include "TextureObject.h"

class FinishLine : public TrackObject
{
public:
	FinishLine(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, float scale = 1.0f);
	virtual ~FinishLine();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
	virtual bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	TextureObject *m_Texture;
	b2Vec2 m_StartPos;
    int m_FireWorks;
    float m_FireWorksDelay;
};
#endif