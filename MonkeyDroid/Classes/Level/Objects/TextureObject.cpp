//
//  TextureObject.mm
//  CTM
//
//  Created by Ryan McBride on 3/7/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//
#include "cocos2d.h"
#include "TextureObject.h"
#include "../../ScreenHelper.h"

USING_NS_CC;

TextureObject::TextureObject(char *texturename,CCNode *layer, int zOrder, bool isFrameCache,CCTexture2DPixelFormat pixFormat)
{
	if(1)
	{
        if(!isFrameCache)
        {
            CCSprite *newSprite = CCSprite::create(texturename);
            m_Layer = layer;
            m_Layer->addChild(newSprite,zOrder);
            m_Texture = newSprite;
        }
        else
        {
            CCTexture2D::setDefaultAlphaPixelFormat(pixFormat);
            CCSprite *newSprite = CCSprite::createWithSpriteFrameName(texturename);
            m_Layer = layer;
            m_Layer->addChild(newSprite,zOrder);
            m_Texture = newSprite;
            CCTexture2D::setDefaultAlphaPixelFormat(kTexture2DPixelFormat_Default);
        }
        SetTextureScale(1.0f,1.0f);
	}
	else 
	{
		m_Texture = NULL;
	}
    m_scale[0] = 1.0f;
    m_scale[1] = 1.0f;
	m_offset[0] = 0.0f;
	m_offset[1] = 0.0f;
}
TextureObject::~TextureObject()
{
}
void TextureObject::SetTextureScale(float xscale, float yscale)
{
	if(m_Texture)
	{
        float zoom = ScreenHelper::getCameraZoom();
        float scale = ScreenHelper::getTextureScale();
		m_Texture->setScaleX(xscale*scale*zoom);
		m_Texture->setScaleY(yscale*scale*zoom);
        
        m_scale[0] = xscale;
        m_scale[1] = yscale;

	}
}
void TextureObject::SetTexturePosition(float xpos, float ypos)
{
	if(m_Texture)
	{
		float zoom = ScreenHelper::getCameraZoom();
		m_Texture->setPosition(CCPointMake((xpos+m_offset[0]) * PTM_RATIO*zoom, (ypos+m_offset[1]) * PTM_RATIO*zoom));
        SetTextureScale(m_scale[0],m_scale[1]);
	}
}
void TextureObject::SetTextureOffset(float xpos, float ypos)
{
	if(m_Texture)
	{
		m_offset[0] = xpos;
		m_offset[1] = ypos;
	}
}
void TextureObject::SetTextureRotation(float rot)
{
	if(m_Texture)
	{
		m_Texture->setRotation(-1 * CC_RADIANS_TO_DEGREES(rot));
	}
}
void TextureObject::ReleaseTexture()
{
	if(m_Texture)
	{
		m_Texture->removeFromParentAndCleanup(true);
	}
}
void TextureObject::ChangeLayer(CCNode *newLayer, int zOrder)
{
	if(m_Texture  && m_Layer)
	{
		m_Layer->removeChild(m_Texture,false);
		m_Layer = newLayer;
		m_Layer->addChild(m_Texture,zOrder);
	}
}
void TextureObject::Draw(b2Body *owner)
{
	if(m_Texture)
	{
        float zoom = ScreenHelper::getCameraZoom();
		m_Texture->setPosition(CCPointMake( (owner->GetPosition().x+m_offset[0]) * PTM_RATIO * zoom, (owner->GetPosition().y+m_offset[1]) * PTM_RATIO * zoom));
        
        SetTextureScale(m_scale[0],m_scale[1]);
        
		m_Texture->setRotation(-1 * CC_RADIANS_TO_DEGREES(owner->GetAngle()));
	}
}