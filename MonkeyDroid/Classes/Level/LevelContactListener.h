//
//  LevelContactListener.h
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __LEVEL_LISTENER_H__
#define __LEVEL_LISTENER_H__
#include "Box2d.h"


class LevelContactListener : public b2ContactListener
{
public:
	LevelContactListener();
	virtual ~LevelContactListener();
	virtual void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
	virtual void BeginContact(b2Contact* contact);
	virtual void EndContact(b2Contact* contact);
	void AddListener(b2ContactListener* listener);
protected:
	b2ContactListener* m_ListenerArray[10];
	int m_NumListeners;
};
#endif