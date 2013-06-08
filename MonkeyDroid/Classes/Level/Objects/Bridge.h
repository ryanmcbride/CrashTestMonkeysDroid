//
//  Bridge.h
//  CTM
//
//  Created by Ryan McBride on 4/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef __BRIDGE_OBJECT_H__
#define __BRIDGE_OBJECT_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "TrackObject.h"

class Bridge : public TrackObject
{
public:
	Bridge(b2World *world, cocos2d::CCNode *layer, b2Body *ground, b2Vec2 *position, int segments, float xoffset, float yoffset, int sort);
	virtual ~Bridge();
	virtual void CreateSelf();
	virtual void DestroySelf();
protected:
	b2Body *m_Bridge[20];
	b2Body* m_middle;
	b2Vec2 m_StartPos;
	b2Body *m_ground;
	b2World *m_world;
    cocos2d::CCNode *m_ccLayer;
    
    int m_segments;
    float m_yOffset;
    float m_xOffset;
    int m_sort;
};
#endif
