//
//  AnimationSet.h
//  CTM
//
//  Created by Ryan McBride on 2/5/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#ifndef __ANIMATION_SET_H__
#define __ANIMATION_SET_H__

#include "cocos2d.h"

class AnimationSet
{
public:
    enum Type
    {
        IDLE=0,
        TRICK1,
        TRICK2,
        TRICK3,
        MAX_TRICKS
    };
	AnimationSet(cocos2d::CCLayer *layer,float runRate);
	~AnimationSet();
    cocos2d::CCSprite *GetSprite();
	int AddIdle(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset);
	int AddRunandHold(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset);
	int AddRunandHold(const char *name, int startFrame, int endFrame, float xoffset, float yoffset);
	void QueueAnim(int animID);
	void Step();
	void SetVisible(bool isVisible);
	void SetPosition(cocos2d::CCPoint p, float rotation);
	bool IsCurrentAnimDone();
    void HandlePauseChange(bool pause);
protected:
    cocos2d::CCPoint GetOffset(int anim){return m_Offsets[anim];}
	void SetAnimPosition(int anim,cocos2d::CCPoint p, float rotation);
	float m_SwtichSprites;
	int m_LastAnim;
	bool m_IsVisible;
	int m_CurrentAnim;
	float m_AnimRate;
    cocos2d::CCLayer *m_Layer;
    int m_Queue[8];
	cocos2d::CCArray *m_Sprites;
	cocos2d::CCArray *m_Anims;
	cocos2d::CCArray *m_Actions;
    cocos2d::CCPoint m_Offsets[7];
};
#endif