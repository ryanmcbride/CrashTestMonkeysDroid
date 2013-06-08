/*
 *  Fire.h
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#ifndef __FIRE_H__
#define __FIRE_H__

#include "cocos2d.h"


class BikeFire
{
public:
    BikeFire(cocos2d::CCLayer *layer,float runRate);
    ~BikeFire();
    void SetVisible(bool isVisible);
    void Update();
    void Pause(bool pause);
    void CreateFire(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset);
protected:
    float m_AnimRate;
	cocos2d::CCLayer *m_Layer;
	cocos2d::CCArray *m_Sprites;
	cocos2d::CCArray *m_Anims;
	cocos2d::CCArray *m_Actions;
	cocos2d::CCPoint m_Offsets[3];
    int numAnims;
    bool m_IsVisible;
    cocos2d::CCPoint lastScale;
};

class WheelFire
{
public:
    WheelFire(cocos2d::CCLayer *layer,float runRate, bool isFront=true);
    ~WheelFire();
    void SetVisible(bool isVisible);
    void Update();
    void Pause(bool pause);
    void CreateFire(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset);
protected:
    float m_AnimRate;
	cocos2d::CCLayer *m_Layer;
	cocos2d::CCArray *m_Sprites;
	cocos2d::CCArray *m_Anims;
	cocos2d::CCArray *m_Actions;
    cocos2d::CCPoint m_Offsets[3];
    int numAnims;
    bool m_IsVisible;
    bool m_isFront;
};
class ExhaustFX
{
public:
    ExhaustFX(cocos2d::CCLayer *layer,float runRate,int type);
    ~ExhaustFX();
    void SetVisible(bool isVisible);
    void Update();
    void Pause(bool pause);
    void CreateExhaust(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset);
protected:
    float m_AnimRate;
    cocos2d::CCLayer *m_Layer;
	cocos2d::CCArray *m_Sprites;
	cocos2d::CCArray *m_Anims;
	cocos2d::CCArray *m_Actions;
	cocos2d::CCPoint m_Offsets[3];
    int numAnims;
    bool m_IsVisible;
};
#endif
