//
//  TrackObject.mm
//  CTM
//
//  Created by Ryan McBride on 5/8/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "TrackObject.h"
#include "Trigger.h"
#include "ScreenHelper.h"

TrackObject::TrackObject(float xpos, float width)
{
	m_xpos = xpos;
	m_width = width;
	m_created = false;
	next = NULL;
    m_trigger = 0;
    m_offtrigger = 0;
}
TrackObject::~TrackObject()
{
}
bool TrackObject::InRange(float xpos)
{
    if(m_trigger != 0 && !(Trigger::TriggerFlags & m_trigger)) return false;
    if(m_offtrigger != 0 && (Trigger::TriggerFlags & m_offtrigger)) return false;
    
	float newXPos = xpos/PTM_RATIO;
	if((m_xpos - newXPos) > -30 && (m_xpos - newXPos) < 50 )
		return true;
	return false;
}
void TrackObject::Update(float xpos,float ypos)
{
	if(!m_created && InRange(xpos))
	{
		CreateSelf();
		m_created = true;
		return;
	}
	   
    if(m_created && !InRange(xpos))
    {
		DestroySelf();
		m_created = false;
	    return;
	}
}
