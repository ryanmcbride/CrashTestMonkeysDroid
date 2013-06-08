//
//  TrackObject.h
//  CTM
//
//  Created by Ryan McBride on 5/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TRACK_OBJECT_H__
#define __TRACK_OBJECT_H__
#include "cocos2d.h"
#include "Box2D.h"

class TrackObject
{
public:
	TrackObject(float xpos, float width);
	virtual ~TrackObject();
	virtual void CreateSelf()=0;
	virtual void DestroySelf()=0;
	virtual void Update(float xpos,float ypos);
	virtual bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB){return false;}
	virtual bool InRange(float xpos);
	TrackObject *next;
	float m_xpos;
    int m_trigger;
    int m_offtrigger;
protected:
	float m_width;
	bool m_created;
};
#endif