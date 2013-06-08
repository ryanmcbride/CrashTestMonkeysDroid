//
//  LevelContactListener.mm
//  CTM
//
//  Created by Ryan McBride on 3/26/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "LevelContactListener.h"


LevelContactListener::LevelContactListener()
{
	m_NumListeners = 0;
}
LevelContactListener::~LevelContactListener()
{
}
void LevelContactListener::PostSolve(b2Contact* contact, const b2ContactImpulse* impulse)
{
	for(int i= 0; i < m_NumListeners; i++)
	{
		m_ListenerArray[i]->PostSolve(contact,impulse);
	}
}
void LevelContactListener::BeginContact(b2Contact* contact)
{
	for(int i= 0; i < m_NumListeners; i++)
	{
		m_ListenerArray[i]->BeginContact(contact);
	}
}
void LevelContactListener::EndContact(b2Contact* contact)
{
	for(int i= 0; i < m_NumListeners; i++)
	{
		m_ListenerArray[i]->EndContact(contact);
	}
}
void LevelContactListener::AddListener(b2ContactListener* listener)
{
	m_ListenerArray[m_NumListeners] = listener;
	m_NumListeners++;
}