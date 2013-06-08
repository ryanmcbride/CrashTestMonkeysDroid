//
//  Track.h
//  CTM
//
//  Created by Ryan McBride on 5/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#ifndef __TRACK_H__
#define __TRACK_H__

#include "cocos2d.h"
#include "Box2D.h"

#include "Objects/TrackObject.h"

#define BG_RAMPS 20

extern b2Vec2 g_LauchDir;
extern float g_LauchDelay;
extern bool g_DoLaunch;
extern bool g_inLoop;

class Track : public b2ContactListener
{
public:
	Track(b2World *world, cocos2d::CCLayer *ccLayer, cocos2d::CCLayer *frontLayer);
	virtual ~Track();
	virtual void Step(float xpos, float ypos);
	virtual void BeginContact(b2Contact* contact);
	void AddObject(TrackObject *tObject);
	void RemoveObject(TrackObject *tObject);
	b2Body *GetMainCollision(){return m_MainCollision;}
    TrackObject* GetCurrent(){return m_current;}
    cocos2d::CCLayer *GetLayer(){return m_ccLayer;}
protected:
	void AddTestObjects();
	b2World *m_world;
	cocos2d::CCLayer *m_ccLayer;
	cocos2d::CCLayer *m_frontLayer;
	b2Body *m_MainCollision;
	
	TrackObject *m_head;
	TrackObject *m_current;
};
#endif