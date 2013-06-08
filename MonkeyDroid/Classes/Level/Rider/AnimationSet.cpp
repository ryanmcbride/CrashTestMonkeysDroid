//
//  AnimationSet.mm
//  CTM
//
//  Created by Ryan McBride on 2/5/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#include "AnimationSet.h"
#include "Box2D.h"
#include "Rider.h"
#include "SimpleAudioEngine.h"
#include "../Level.h"
#include "../../ScreenHelper.h"

USING_NS_CC;

extern bool g_is60;
extern bool g_bIsRetina;

AnimationSet::AnimationSet(CCLayer *layer, float runRate)
{
	m_IsVisible = true;
	m_Layer = layer;
	m_AnimRate = runRate;
	m_CurrentAnim = 0;
	m_SwtichSprites = -1.0f;
	m_LastAnim = 0;

    m_Queue[0] = -1;
    
    m_Sprites = CCArray::createWithCapacity(4);
    m_Sprites->retain();
    
    m_Anims = CCArray::createWithCapacity(4);
    m_Anims->retain();

    m_Actions = CCArray::createWithCapacity(4);
    m_Actions->retain();
}
AnimationSet::~AnimationSet()
{
	m_Sprites->release();
	m_Anims->release();
	m_Actions->release();
}
CCSprite *AnimationSet::GetSprite()
{
    return (CCSprite*)m_Sprites->objectAtIndex(m_CurrentAnim);
}
int AnimationSet::AddIdle(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset)
{
    char temp[64];
    sprintf(temp,"%s.plist",name);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(temp);
    
    sprintf(temp,"%s.pvr.ccz",name);
    CCTextureCache::sharedTextureCache()->addImage(temp);
    CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::create(temp);
    
    m_Layer->addChild(spritesheet,2);
    
	CCArray *animFrames = CCArray::createWithCapacity(numFrames);
	int i;  
	for(i = 1; i <= numFrames; i++) 
	{
        sprintf(temp,"%s-%d.png",frameBaseName,i);
		animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
	}

	CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames,m_AnimRate);
	
	sprintf(temp,"%s-%d.png",frameBaseName,1);
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(temp);
	CCAction *action = CCRepeatForever::create(CCAnimate::create(anim));
	sprite->runAction(action);
	spritesheet->addChild(sprite);
	
	m_Sprites->addObject(sprite);
	m_Anims->addObject(anim);
	m_Actions->addObject(action);
	
	m_Offsets[0].x = xoffset;
	m_Offsets[0].y = yoffset;
	return 0;
}
int AnimationSet::AddRunandHold(const char *name, const char *frameBaseName, int numFrames, float xoffset, float yoffset)
{
    char temp[64];
    sprintf(temp,"%s.plist",name);
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile(temp);
    
    sprintf(temp,"%s.pvr.ccz",name);
    CCTextureCache::sharedTextureCache()->addImage(temp);
    CCSpriteBatchNode *spritesheet = CCSpriteBatchNode::create(temp);
    
    m_Layer->addChild(spritesheet,2);
    
	CCArray *animFrames = CCArray::createWithCapacity(numFrames);
	int i;
	for(i = 1; i <= numFrames; i++)
	{
        sprintf(temp,"%s-%d.png",frameBaseName,i);
		animFrames->addObject(CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(temp));
	}
    
	CCAnimation *anim = CCAnimation::createWithSpriteFrames(animFrames,m_AnimRate);
	
	sprintf(temp,"%s-%d.png",frameBaseName,1);
	CCSprite *sprite = CCSprite::createWithSpriteFrameName(temp);
	sprite->setVisible(false);
    CCAction *action = CCAnimate::create(anim);
	spritesheet->addChild(sprite);
	
	m_Sprites->addObject(sprite);
	m_Anims->addObject(anim);
	m_Actions->addObject(action);
	
    
    int index = m_Sprites->count()-1;
	m_Offsets[index].x = xoffset;
	m_Offsets[index].y = yoffset;
    
	
	return index;
}
int AnimationSet::AddRunandHold(const char *name, int startFrame, int endFrame, float xoffset, float yoffset)
{
/*	[[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:[NSString stringWithFormat:@"%@.plist", name]];
	
	CCSpriteBatchNode *spriteSheet = [CCSpriteBatchNode batchNodeWithFile:[NSString stringWithFormat:@"%@.png", name]];
	[m_Layer addChild:spriteSheet z:2];
	
	NSMutableArray *animFrames = [NSMutableArray array];
	int i;
	for(i = startFrame; i <= endFrame; i++) 
	{
		[animFrames addObject:
		 [[CCSpriteFrameCache sharedSpriteFrameCache] spriteFrameByName:
		  [NSString stringWithFormat:@"%@_%02d.png", name,i]]];
	}
	
	CCAnimation *anim = [CCAnimation 
					  animationWithFrames:animFrames delay:m_AnimRate];
	
	CCAction *action = [CCAnimate actionWithAnimation:anim restoreOriginalFrame:NO];
	
	
	
	CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:[NSString stringWithFormat:@"%@_%02d.png", name,startFrame]];        
	sprite.visible = NO;
	
	[spriteSheet addChild:sprite];
	
	[m_Sprites addObject: sprite];
	[m_Anims addObject: anim];
	[m_Actions addObject: action];
	
	int index = [m_Sprites count]-1;
	m_Offsets[index].x = xoffset;
	m_Offsets[index].y = yoffset;

	
	return index;*/
    return 0;
}
void AnimationSet::QueueAnim(int animID)
{
    for(int i = 0; i < 7; i++)
    {
        if(m_Queue[i] == -1)
        {
            m_Queue[i] = animID;
            m_Queue[i+1] = -1;
            break;
        }
    }
	
	return;
}
bool AnimationSet::IsCurrentAnimDone()
{
	if(m_SwtichSprites >= 0.0f)
		return false;
	
	if(m_CurrentAnim == 0/*idle*/)
		return true;
	
	CCAction *action = (CCAction*)m_Actions->objectAtIndex(m_CurrentAnim);
	if(action->isDone())
		return true;
	
	return false;
}
void AnimationSet::HandlePauseChange(bool pause)
{
    if(pause)
    {
        CCDirector::sharedDirector()->getActionManager()->pauseTarget(m_Sprites->objectAtIndex(m_CurrentAnim));
    }
    if(!pause)
    {
        CCDirector::sharedDirector()->getActionManager()->resumeTarget(m_Sprites->objectAtIndex(m_CurrentAnim));
    }
}
void AnimationSet::Step()
{
    
    if(m_SwtichSprites >= 0.0f)
    {
        
        m_SwtichSprites -= (g_is60?1.0f/60.0f:1.0f/30.0f);
        
        if(m_SwtichSprites < 0.0f)
        {
            CCSprite *oldSprite = (CCSprite*)m_Sprites->objectAtIndex(m_LastAnim);
            CCSprite *newSprite = (CCSprite*)m_Sprites->objectAtIndex(m_CurrentAnim);
            oldSprite->setVisible(false);
            newSprite->setVisible(true);
        }
    }
    
    if(IsCurrentAnimDone() && m_Queue[0] != -1)
    {
        m_SwtichSprites = m_AnimRate;
        m_LastAnim = m_CurrentAnim;
        
        m_CurrentAnim = m_Queue[0];
        
        for(int ii = 0; ii < 7; ii++)
        {
            m_Queue[ii] = m_Queue[ii+1];
            if(m_Queue[ii]==-1)
                break;
        }
        
        
        CCSprite *oldSprite = (CCSprite*)m_Sprites->objectAtIndex(m_LastAnim);
        CCSprite *newSprite = (CCSprite*)m_Sprites->objectAtIndex(m_CurrentAnim);
        
        if(m_CurrentAnim != 0)//Idle
        {
            CCAction *newAction = (CCAction*)m_Actions->objectAtIndex(m_CurrentAnim);
            //			if(reverse)
            //			{
            //				CCReverseTime *reverse = [CCReverseTime actionWithAction:(CCAnimate*)newAction];
            //				newAction = reverse;
            //			}
            newSprite->runAction(newAction);
            
            //[Options PlayEffect:AUDIO_TRICK_3];
        }
        else
        {
            Rider::g_TrickState = 0;
        }
        if(m_LastAnim != IDLE)//Idle
        {
            CCAction *oldAction = (CCAction*)m_Actions->objectAtIndex(m_LastAnim);
            if(!oldAction->isDone())
                oldSprite->stopAction(oldAction);
        }
    }
    
	return;
}
void AnimationSet::SetVisible(bool isVisible)
{
	m_IsVisible = isVisible;
	CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(m_CurrentAnim);
	sprite->setVisible(isVisible);
}
void AnimationSet::SetAnimPosition(int anim,CCPoint p, float rotation)
{
    float scale = ScreenHelper::getTextureScale();
    float zoom = ScreenHelper::getCameraZoom();
    
	CCSprite *sprite = (CCSprite*)m_Sprites->objectAtIndex(anim);
    
	CCPoint offset = GetOffset(anim);
	CCPoint position;
	b2Transform xform = Rider::g_MainBody->GetTransform();
	b2Vec2 off;
	off.x = offset.x;
	off.y = offset.y;
	
	off = b2Mul(xform.q,off);
	
    position.x = PTM_RATIO*(p.x + off.x)*zoom;
	position.y = PTM_RATIO*(p.y + off.y)*zoom;
	
	sprite->setPosition(position);
	sprite->setRotation(-1 * CC_RADIANS_TO_DEGREES(rotation));
    sprite->setScale(0.5f*scale*zoom);
}
void AnimationSet::SetPosition(CCPoint p, float rotation)
{
	SetAnimPosition(m_CurrentAnim,p,rotation);
	if(m_SwtichSprites >= 0.0f)
		SetAnimPosition(m_LastAnim,p,rotation);
}