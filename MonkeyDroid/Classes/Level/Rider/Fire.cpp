/*
 *  Vehicle.cpp
 *  CTM
 *
 *  Created by Ryan McBride on 2/5/11.
 *  Copyright 2011 __MyCompanyName__. All rights reserved.
 *
 */
#include "Box2D.h"
#include "Rider.h"
#include "Fire.h"
#include "DirtBike.h"
#include "../../FrontEnd/SaveLoad.h"
#include "../../ScreenHelper.h"

using namespace cocos2d;

BikeFire::BikeFire(CCLayer *layer,float runRate)
{
    m_Sprites = CCArray::createWithCapacity(3);
	m_Sprites->retain();
	m_Anims = CCArray::createWithCapacity(3);
	m_Anims->retain();
	m_Actions = CCArray::createWithCapacity(3);
	m_Actions->retain();
    
    m_IsVisible = true;
    m_AnimRate = runRate;
	m_Layer = layer;
	numAnims = 0;
    const char *ext = SaveLoad::GetBikeExt();
    const char *topframeNames = NULL;
    const char *midframeNames = NULL;
    const char *lowframeNames = NULL;
    
    if(strcmp(ext,"_McAcme")==0 || strcmp(ext,"_Pizza")==0 || strcmp(ext,"_Island")==0)
    {
        topframeNames = "ctm_TopFire";
        midframeNames = "ctm_MidFire";
        lowframeNames = "ctm_LowerFire";
    }
    if(strcmp(ext,"_Default")==0)
    {
        topframeNames = "Default_TopFire";
        midframeNames = "Default_MidFire";
        lowframeNames = "Default_LowerFire";
    }
    if(strcmp(ext,"_SciFi")==0 || strcmp(ext,"_Police")==0)
    {
        topframeNames = "Blue_TopFire";
        midframeNames = "Blue_MidFire";
        lowframeNames = "Blue_LowerFire";
    }
    if(strcmp(ext,"_DirtBike")==0)
    {
        topframeNames = "Green_TopFire";
        midframeNames = "Green_MidFire";
        lowframeNames = "Green_LowerFire";
    }
    if(strcmp(ext,"_Electric")==0)
    {
        topframeNames = "Purple_TopFire";
        midframeNames = "Purple_MidFire";
        lowframeNames = "Purple_LowerFire";
    }
    
    
    CreateFire("ctm_TopFire",topframeNames,11,-1.2f,0.6f);
    CreateFire("ctm_MidFire",midframeNames,11,-1.2f,0.0f);
    CreateFire("ctm_LowerFire",lowframeNames,11,-1.2f,-0.6f);
    
    lastScale.x = -0.5f;
    lastScale.y = 1.0f;
    
    SetVisible(false);
}
BikeFire::~BikeFire()
{
    m_Sprites->autorelease();
	m_Anims->autorelease();
	m_Actions->autorelease();
}
void BikeFire::Update()
{
    if(!m_IsVisible)return;
    
    CCPoint velocity = CCPointMake(Rider::g_MainBody->GetLinearVelocity().x,Rider::g_MainBody->GetLinearVelocity().y);
    float rotVel = Rider::g_MainBody->GetAngularVelocity();
    CCPoint p = CCPointMake(Rider::g_MainBody->GetWorldCenter().x,Rider::g_MainBody->GetWorldCenter().y);
    float rotation = Rider::g_MainBody->GetAngle();
    float scaleX = -0.5f;
    float scaleY = 1.0f;
    
    if(!Rider::g_inLoop)
    {
        if(rotVel > 4.0f || rotVel < -4.0f)
            rotation -= rotVel/120.0f;
        
        if(velocity.x > 0.0f)
        {
            if(velocity.x>40.0f)
                velocity.x = 40.0f;
            float scale = -velocity.x/40.0f;
            scaleX += scale;
        }
        else if(velocity.x < 0.0f)
        {
            if(velocity.x<-10.0f)
                velocity.x = -10.0f;
            
            float scale = -velocity.x/10.0f;
            scale *= 0.25f;
            
            scaleX += scale;
        }
    }
    else
    {
        scaleX += -0.8f;
    }
    float zoom = ScreenHelper::getCameraZoom();
    float scale = ScreenHelper::getTextureScale();
    for(int anim = 0; anim < numAnims; anim++)
    {
        CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(anim);
        
        CCPoint offset = m_Offsets[anim];
        CCPoint position;
        b2Transform xform = Rider::g_MainBody->GetTransform();
        b2Vec2 off;
        off.x = offset.x;
        off.y = offset.y;
        
        off = b2Mul(xform.q,off);
        
        position.x = zoom*PTM_RATIO*(p.x + off.x);
        position.y = zoom*PTM_RATIO*(p.y + off.y);
        
        sprite->setPosition(position);
        sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(rotation));
        sprite->setScaleX(scaleX*zoom*scale);
        sprite->setScaleY(scaleY*zoom*scale);
    }
}
void BikeFire::CreateFire(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset)
{
    char tempName[64];
    sprintf(tempName,"%s.plist",name);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(tempName);
    sprintf(tempName,"%s.pvr.ccz",name);
    CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::create(tempName);
    m_Layer->addChild(spriteSheet,2);
    
    CCArray *animFrames = CCArray::createWithCapacity(numFrames);
    int i;
    for(i = 1; i <= numFrames; i++)
    {
        sprintf(tempName,"%s_%03d.png",frameBaseName,i);
        animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tempName));
    }
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames,m_AnimRate);
    
    
    sprintf(tempName,"%s_%03d.png",frameBaseName,1);
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(tempName);
    CCAction *action = CCRepeatForever::create(CCAnimate::create(anim));
    
    sprite->runAction(action);
    spriteSheet->addChild(sprite);
    
    m_Sprites->addObject(sprite);
    m_Anims->addObject(anim);
    m_Actions->addObject(action);
    
    m_Offsets[numAnims].x = xoffset;
    m_Offsets[numAnims].y = yoffset;
    numAnims++;
}
void BikeFire::SetVisible(bool isVisible)
{
    if(m_IsVisible == isVisible) return;
	m_IsVisible = isVisible;
    for(int i = 0; i < numAnims; i++)
    {
        CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(i);
        sprite->setVisible(isVisible);
    }
}
void BikeFire::Pause(bool pause)
{
    for(int i = 0; i < numAnims; i++)
    {
        if(pause)
        {
            CCDirector::sharedDirector()->getActionManager()->pauseTarget(m_Sprites->objectAtIndex(i));
        }
        if(!pause)
        {
            CCDirector::sharedDirector()->getActionManager()->resumeTarget(m_Sprites->objectAtIndex(i));
        }
    }
}


WheelFire::WheelFire(CCLayer *layer,float runRate, bool isFront)
{
    m_isFront = isFront;
    
    m_Sprites = CCArray::createWithCapacity(3);
	m_Sprites->retain();
	m_Anims = CCArray::createWithCapacity(3);
	m_Anims->retain();
	m_Actions = CCArray::createWithCapacity(3);
	m_Actions->retain();
    
    m_IsVisible = true;
    m_AnimRate = runRate;
	m_Layer = layer;
	numAnims = 0;
    CreateFire("ctm_WheelFire","ctm_WheelFire",9,0.0f,0.0f);
    CreateFire("ctm_WheelFire","ctm_WheelFire_Still",4,0.0f,0.0f);
    CreateFire("ctm_WheelFire","ctm_WheelFire_Transition",5,0.0f,0.0f);
    SetVisible(false);
}
WheelFire::~WheelFire()
{
    m_Sprites->autorelease();
	m_Anims->autorelease();
	m_Actions->autorelease();
}
void WheelFire::Update()
{
    if(!m_IsVisible)return;
    DirtBike *dirtBike = (DirtBike *)Rider::s_Vehicle;
    
    b2Vec2 vel = Rider::g_MainBody->GetLinearVelocity();
    float velLength = vel.Normalize();
    
    float rotVel = Rider::g_MainBody->GetAngularVelocity();
    CCPoint p;
    CCSprite *wheelSprite = NULL;
    if(m_isFront)
        wheelSprite = dirtBike->GetWheelFrontSprite();
    else
        wheelSprite = dirtBike->GetWheelBackSprite();
    
    p = wheelSprite->getPosition();
    
    float rotation = 0.0f;
    int visibilityIndex = 0;
    if(velLength<1.0f)
    {
        visibilityIndex = 1;
    }
    else
    {
        if(velLength<5.0f)
            visibilityIndex = 2;
        rotation = b2Atan2(vel.y, vel.x);
    }
    if(Rider::g_inLoop)
    {
        rotation = 0.0f;
    }
    if(Rider::g_isInAir)
    {
        if(m_isFront)
        {
            if(rotVel>5.0f)
            {
                rotation = Rider::g_MainBody->GetAngle()+b2_pi/2.0f;
            }
            if(rotVel<-5.0f)
            {
                rotation = Rider::g_MainBody->GetAngle()-b2_pi/2.0f;
            }
        }
        else
        {
            if(rotVel>5.0f)
            {
                rotation = Rider::g_MainBody->GetAngle()-b2_pi/2.0f;
            }
            if(rotVel<-5.0f)
            {
                rotation = Rider::g_MainBody->GetAngle()+b2_pi/2.0f;
            }
        }
    }
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    for(int anim = 0; anim < numAnims; anim++)
    {
        CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(anim);
        
        CCPoint offset = m_Offsets[anim];
        CCPoint position;
        b2Transform xform = Rider::g_MainBody->GetTransform();
        b2Vec2 off;
        off.x = offset.x;
        off.y = offset.y;
        
        off = b2Mul(xform.q,off);
        
        position.x = (p.x + PTM_RATIO*off.x);
        position.y = (p.y + PTM_RATIO*off.y);
        
        sprite->setPosition(position);
        sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(rotation));
        sprite->setScaleX(-1.0f*zoom*scale);
        sprite->setScaleY(zoom*scale);
        if(anim==visibilityIndex)
            sprite->setVisible(true);
        else
            sprite->setVisible(false);
    }
}
void WheelFire::CreateFire(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset)
{
    char tempName[64];
    sprintf(tempName,"%s.plist",name);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(tempName);
    sprintf(tempName,"%s.pvr.ccz",name);
    CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::create(tempName);
    m_Layer->addChild(spriteSheet,2);
    
    CCArray *animFrames = CCArray::createWithCapacity(numFrames);
    int i;
    for(i = 1; i <= numFrames; i++)
    {
        sprintf(tempName,"%s_%03d.png",frameBaseName,i);
        animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tempName));
    }
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames,m_AnimRate);
    
    
    sprintf(tempName,"%s_%03d.png",frameBaseName,1);
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(tempName);
    CCAction *action = CCRepeatForever::create(CCAnimate::create(anim));
    
    sprite->runAction(action);
    spriteSheet->addChild(sprite);
    
    m_Sprites->addObject(sprite);
    m_Anims->addObject(anim);
    m_Actions->addObject(action);
    
    m_Offsets[numAnims].x = xoffset;
    m_Offsets[numAnims].y = yoffset;
    numAnims++;

}
void WheelFire::SetVisible(bool isVisible)
{
    if(m_IsVisible == isVisible) return;
    
	m_IsVisible = isVisible;
    if(!m_IsVisible)
    {
        for(int i = 0; i < numAnims; i++)
        {
            CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(i);
            sprite->setVisible(isVisible);
        }
    }
}
void WheelFire::Pause(bool pause)
{
    for(int i = 0; i < numAnims; i++)
    {
        if(pause)
        {
            CCDirector::sharedDirector()->getActionManager()->pauseTarget(m_Sprites->objectAtIndex(i));
        }
        if(!pause)
        {
            CCDirector::sharedDirector()->getActionManager()->resumeTarget(m_Sprites->objectAtIndex(i));
        }
    }
}


ExhaustFX::ExhaustFX(CCLayer *layer,float runRate, int type)
{
    m_Sprites = CCArray::createWithCapacity(1);
	m_Sprites->retain();
	m_Anims = CCArray::createWithCapacity(1);
	m_Anims->retain();
	m_Actions = CCArray::createWithCapacity(1);
	m_Actions->retain();
    
    m_IsVisible = true;
    m_AnimRate = runRate;
	m_Layer = layer;
	numAnims = 0;
    if(type==0)
        CreateExhaust("ctm_Electric_Exhaust","ctm_electric_Exhaust",5,-3.4f,0.36f);
    else
        CreateExhaust("ctm_Scifi_Exhaust","ctm_scifi_Exhaust",10,-3.4f,0.7f);
}
ExhaustFX::~ExhaustFX()
{
    m_Sprites->autorelease();
	m_Anims->autorelease();
	m_Actions->autorelease();
}
void ExhaustFX::Update()
{
    if(!m_IsVisible)return;
    float rotation = Rider::g_MainBody->GetAngle();
    CCPoint p = CCPointMake(Rider::g_MainBody->GetWorldCenter().x,Rider::g_MainBody->GetWorldCenter().y);
    
    float zoom = ScreenHelper::getCameraZoom();
    float scale = ScreenHelper::getTextureScale();
    
    for(int anim = 0; anim < numAnims; anim++)
    {
        CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(anim);
        
        CCPoint offset = m_Offsets[anim];
        CCPoint position;
        b2Transform xform = Rider::g_MainBody->GetTransform();
        b2Vec2 off;
        off.x = offset.x;
        off.y = offset.y;
        
        off = b2Mul(xform.q,off);
        
        position.x = zoom*PTM_RATIO*(p.x + off.x);
        position.y = zoom*PTM_RATIO*(p.y + off.y);
        
        sprite->setPosition(position);
        sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(rotation));
        sprite->setScale(zoom*scale);
    }
}
void ExhaustFX::CreateExhaust(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset)
{
    char tempName[64];
    sprintf(tempName,"%s.plist",name);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(tempName);
    sprintf(tempName,"%s.pvr.ccz",name);
    CCSpriteBatchNode *spriteSheet = CCSpriteBatchNode::create(tempName);
    m_Layer->addChild(spriteSheet,2);
    
    CCArray *animFrames = CCArray::createWithCapacity(numFrames);
    int i;
    for(i = 1; i <= numFrames; i++)
    {
        sprintf(tempName,"%s_%03d.png",frameBaseName,i);
        animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(tempName));
    }
    
    CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames,m_AnimRate);
    
    
    sprintf(tempName,"%s_%03d.png",frameBaseName,1);
    CCSprite *sprite = CCSprite::createWithSpriteFrameName(tempName);
    CCAction *action = CCRepeatForever::create(CCAnimate::create(anim));
    
    sprite->runAction(action);
    spriteSheet->addChild(sprite);
    
    m_Sprites->addObject(sprite);
    m_Anims->addObject(anim);
    m_Actions->addObject(action);
    
    m_Offsets[numAnims].x = xoffset;
    m_Offsets[numAnims].y = yoffset;
    numAnims++;
}
void ExhaustFX::SetVisible(bool isVisible)
{
    m_IsVisible = isVisible;
    if(!m_IsVisible)
    {
        for(int i = 0; i < numAnims; i++)
        {
            CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(i);
            sprite->setVisible(isVisible);
        }
    }
}
void ExhaustFX::Pause(bool pause)
{
    for(int i = 0; i < numAnims; i++)
    {
        if(pause)
        {
            CCDirector::sharedDirector()->getActionManager()->pauseTarget(m_Sprites->objectAtIndex(i));
        }
        if(!pause)
        {
            CCDirector::sharedDirector()->getActionManager()->resumeTarget(m_Sprites->objectAtIndex(i));
        }
    }
}
