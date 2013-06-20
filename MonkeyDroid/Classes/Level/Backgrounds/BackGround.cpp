//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "BackGround.h"
#include "TutorialBackGround.h"
#include "TikiBackGround.h"
#include "CityBackGround.h"
#include "NightBackGround.h"
#include "SpaceBackGround.h"
#include "SimpleAudioEngine.h"
#include "../../ScreenHelper.h"
#include "../Level.h"
#include "../../FrontEnd/LevelSelect.h"

using namespace cocos2d;
using namespace CocosDenshion;

class CCPointObject : CCObject
{
    CC_SYNTHESIZE(CCPoint, m_tRatio, Ratio)
    CC_SYNTHESIZE(CCPoint, m_tOffset, Offset)
    CC_SYNTHESIZE(CCNode *,m_pChild, Child)    // weak ref
    
    static CCPointObject * pointWithCCPoint(CCPoint ratio, CCPoint offset)
    {
        CCPointObject *pRet = new CCPointObject();
        pRet->initWithCCPoint(ratio, offset);
        pRet->autorelease();
        return pRet;
    }
    bool initWithCCPoint(CCPoint ratio, CCPoint offset)
    {
        m_tRatio = ratio;
        m_tOffset = offset;
        m_pChild = NULL;
        return true;
    }
};

CCParallaxNodeTile *CCParallaxNodeTile::create()
{
    CCParallaxNodeTile *pRet = new CCParallaxNodeTile();
    pRet->autorelease();
    return pRet;
}
void CCParallaxNodeTile::setOffset(CCPoint offset,CCNode* node)
{
    for( unsigned int i=0;i < m_pParallaxArray->num;i++)
    {
        CCPointObject *point = (CCPointObject *)m_pParallaxArray->arr[i];
        CCNode * curNode = point->getChild() ;
        if( curNode->isEqual(node) )
        {
            point->setOffset(offset);
            break;
        }
    }
}
CCPoint CCParallaxNodeTile::getRatio(CCNode* node)
{
    for( unsigned int i=0;i < m_pParallaxArray->num;i++)
    {
        CCPointObject *point = (CCPointObject *)m_pParallaxArray->arr[i];
        CCNode * curNode = point->getChild() ;
        if( curNode->isEqual(node) )
        {
            return point->getRatio();
            break;
        }
    }
    return ccp(0.0f,0.0f);
}


BackGround::BackGround()
{
    
}

void BackGround::InitBG(cocos2d::CCNode *layer)
{
    glClearColor(81.0f/255.0f, 150.0f/255.0f, 239.0f/255.0f, 1.0f);
    m_layer = layer;
    pNode = CCParallaxNodeTile::create();
    m_layer->addChild(pNode);
        
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    
    CCSprite *sprite = CCSprite::create("ctm_island_BG_01.png");
    sprite->setScaleX(s.width/940.0f);
    sprite->setScaleY(s.width/940.0f);
    pNode->addChild(sprite,0,CCPointMake(1.0f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,40.0f));
    
    
    m_Parallax1 = CCArray::createWithCapacity(4);
    m_Parallax1->retain();
    for(int i = 0; i < 4; i++)
    {
        sprite = CCSprite::create("ctm_Grass_withplants_00.png");
        sprite->setScale(scale);
        m_Parallax1Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 53.0f);
        pNode->addChild(sprite,0,CCPointMake(0.90f,0.0f),m_Parallax1Points[i]);
        m_Parallax1->addObject(sprite);
        
    }
    
    m_Track = CCArray::createWithCapacity(4);
    m_Track->retain();
    for(int i = 0; i < 4; i++)
    {
        sprite = CCSprite::create("ctm_island_FG_01.png");
        sprite->setScaleX(scaleX);
        sprite->setScaleY(scale);
        m_TrackPoints[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, -30.0f);
        sprite->setPosition(m_TrackPoints[i]);
        m_layer->addChild(sprite,4);
        m_Track->addObject(sprite);
    }

}


BackGround::~BackGround()
{
    m_Track->release();
    m_Parallax1->release();
}

void BackGround::Step(float xpos, float ypos)
{
    float scaleY = ScreenHelper::getTextureScaleY();
    float scaleX = ScreenHelper::getTextureScaleX();
    float zoom  = ScreenHelper::getCameraZoom();
    pNode->setPosition(CCPointMake(xpos,ypos));
    
    float count = m_Track->count();
    for ( int ii = 0  ; ii < m_Track->count() ; ii++ )
    {
        CCSprite * trackPiece = (CCSprite *)(m_Track->objectAtIndex(ii));
        trackPiece->setScaleX(scaleX*zoom);
        trackPiece->setScaleY(scaleY*zoom);
        CCPoint newPoint;
        newPoint.x = m_TrackPoints[ii].x*zoom;
        newPoint.y = m_TrackPoints[ii].y*zoom;
        trackPiece->setPosition(newPoint);
        //float xPosition = newPoint.x-xpos;
        float size = trackPiece->getContentSize().width*scaleX*zoom;
        if ( (newPoint.x + size) < xpos)
        {
            m_TrackPoints[ii].x += 256.0f*scaleX*count;
        }
        if ( (newPoint.x + size) > (xpos+256.0f*scaleX*count - 150.0f*scaleX))
        {
            m_TrackPoints[ii].x -= 256.0f*scaleX*count;
        }
    }

}

BackGround *BackGround::create(CCNode *layer)
{
    BackGround *bg;
    int level = LevelSelect::getCurrentLevel();
    
    if(level>=0 && level < 8)
        bg = new TutorialBackGround();
    else if(level>=8 && level < 16)
        bg = new TikiBackGround();
    else if(level>=16 && level < 24)
        bg = new CityBackGround();
    else if(level>=24 && level < 32)
        bg = new NightBackGround();
    else if(level>=32 && level < 40)
        bg = new SpaceBackGround();
    else
        bg = new BackGround();
    
    bg->InitBG(layer);
    
    return bg;
}

