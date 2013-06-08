//
//  Trampoline.h
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TRIGGER_H__
#define __TRIGGER_H__
#include "cocos2d.h"
#include "Box2D.h"
#include "TrackObject.h"
//#include "TextureObject.h"

class Trigger : public TrackObject
{
public:
	Trigger(b2World *world, cocos2d::CCNode *CCLayer, b2Vec2 *startPos, int triggerFlag = 0);
	virtual ~Trigger();
	virtual void CreateSelf();
	virtual void DestroySelf();
	bool HandleBeginContact(b2Fixture *fixtureA,b2Fixture *fixtureB);
    static int TriggerFlags;
protected:
	b2World *m_world;
	cocos2d::CCNode *m_ccLayer;
	b2Body *m_MainCollision;
	b2Vec2 m_StartPos;
	//TextureObject *m_Texture;
    int m_Flag;
    bool m_isTriggered;
};
#endif