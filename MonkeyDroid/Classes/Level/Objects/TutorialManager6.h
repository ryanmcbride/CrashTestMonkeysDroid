//
//  TutorialManager.h
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __TUTORIAL_MANANGER_6_H__
#define __TUTORIAL_MANANGER_6_H__

#include "cocos2d.h"
#include "TrackObject.h"
#include "../Track.h"

class TutorialManager6 : public TrackObject
{
public:
	TutorialManager6(Track *track, cocos2d::CCNode* backLayer, b2World *world, b2Vec2 *startPos);
	virtual ~TutorialManager6();
	virtual void CreateSelf();
	virtual void DestroySelf();
    virtual void Update(float xpos,float ypos);
protected:
    b2World *m_world;
    cocos2d::CCNode *m_backLayer;
    cocos2d::CCNode *m_frontLayer;
    b2Vec2 m_StartPos;
    int m_State;
    float m_Timer;
    bool m_bStateDone;
    Track *m_Track;
    TrackObject* m_farWall;
    cocos2d::CCSprite *buttonGlow;
    cocos2d::CCSprite *arrowGlow;
    cocos2d::CCNode *m_trickText;
};
#endif