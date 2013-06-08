//
//  Track.mm
//  CTM
//
//  Created by Ryan McBride on 5/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#include "Track.h"
#include "Objects/Ramp.h"
#include "Objects/TurboStrip.h"

USING_NS_CC;

#define BG_COLLISION_LENGTH 150.0f

Track::Track(b2World *world, CCLayer *ccLayer, CCLayer *frontLayer)
{
	m_world = world;
	m_ccLayer = ccLayer;
	m_frontLayer = frontLayer;
	m_head = NULL;
	m_current = NULL;
	
	b2PolygonShape box;
	b2FixtureDef fd;
	b2BodyDef bd;
	
	//set main ground collision
	//b2Vec2 edge1(-BG_COLLISION_LENGTH*1.0f,0.0f);
	//b2Vec2 edge2(BG_COLLISION_LENGTH*20.0f,0.0f);
	//box.SetAsEdge(edge1,edge2);
    box.SetAsBox(BG_COLLISION_LENGTH*20.0f, 0.25, b2Vec2(BG_COLLISION_LENGTH*9.0f, -0.25f/2.0f), 0.0f);
	fd.shape = &box;
	fd.friction = 0.62f;
	fd.filter.groupIndex = -1;
	m_MainCollision = m_world->CreateBody(&bd);
	m_MainCollision->CreateFixture(&fd);	
	
	
	//AddTestObjects();
	
}
Track::~Track()
{
	m_current = m_head;
	while(m_current != NULL)
	{
		m_head = m_current->next;
		delete m_current;
		m_current = m_head;
	}
}
void Track::AddTestObjects()
{
	int i;
	for(i = 0; i < BG_RAMPS; i++)
	{
        b2Vec2 turboPos(130.0f+150.0f*i,0.0f);
        AddObject(new TurboStrip(m_world,m_ccLayer,&turboPos));

		b2Vec2 rampPos(150.0f+150.0f*i,0.0f);
        AddObject(new Ramp(m_world,m_ccLayer,&rampPos, Ramp::FWD));
	}
}

void Track::AddObject(TrackObject *tObject)
{
	if(m_current==NULL)
	{
		m_head = tObject;
		m_current = m_head;
	}
	else 
	{
		m_current->next = tObject;
		m_current = tObject;
	}
}

void Track::RemoveObject(TrackObject *tObject)
{
	if(m_current==NULL)
	{
        return;
    }
	else
	{
        TrackObject *current = m_head;
        TrackObject *previous = NULL;
        for(; current != NULL; current = current->next)
        {
            if(tObject == current)
            {
                if(!previous)
                {
                    m_head = current->next;
                }
                else
                {
                    previous->next = current->next;
                }
                return;
            }
            previous = current;
        }
	}
}

void Track::Step(float xpos, float ypos)
{	
	m_current = m_head;
	while(m_current != NULL)
	{
		m_current->Update(xpos,ypos);
		m_current = m_current->next;
	}
}
void Track::BeginContact(b2Contact* contact)
{
	b2Fixture *fixtureA = contact->GetFixtureA();
	b2Fixture *fixtureB = contact->GetFixtureB();
	//if(Rider::g_LauchDelay <= 0.0f)
	{
		m_current = m_head;
		while(m_current != NULL)
		{
			m_current->HandleBeginContact(fixtureA,fixtureB);
			m_current = m_current->next;
		}
		
	}
}
