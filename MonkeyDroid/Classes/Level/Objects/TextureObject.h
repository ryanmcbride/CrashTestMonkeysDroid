//
//  TextureObject.h
//  CTM
//
//  Created by Ryan McBride on 3/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __TEXTURE_OBJECT_H__
#define __TEXTURE_OBJECT_H__

#include "cocos2d.h"
#include "Box2D.h"
#include "../Level.h"

class TextureObject
{
public:
	TextureObject(char *texturename,cocos2d::CCNode *layer, int zOrder=2, bool isFrameCache=false, cocos2d::CCTexture2DPixelFormat pixFormat=cocos2d::kTexture2DPixelFormat_Default);
	virtual ~TextureObject();
	virtual void SetTextureScale(float xscale, float yscale);
	virtual void SetTexturePosition(float xpos, float ypos);
	virtual void SetTextureOffset(float xpos, float ypos);
	virtual void SetTextureRotation(float rot);
	virtual void ReleaseTexture();
	virtual void Draw(b2Body *owner);
	virtual cocos2d::CCSprite* GetSprite(){return (cocos2d::CCSprite*)m_Texture;}
	virtual void ChangeLayer(cocos2d::CCNode *newLayer, int zOrder=2);
protected:
	cocos2d::CCNode *m_Layer;
	cocos2d::CCSprite *m_Texture;
	float m_offset[2];
    float m_scale[2];
};
#endif