//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "TikiBackGround.h"
#include "SimpleAudioEngine.h"
#include "../../ScreenHelper.h"
#include "../Level.h"

using namespace cocos2d;
using namespace CocosDenshion;


TikiBackGround::TikiBackGround()
{
}
void TikiBackGround::InitBG(cocos2d::CCNode *layer)
{
    glClearColor(81.0f/255.0f, 150.0f/255.0f, 239.0f/255.0f, 1.0f);
    m_layer = layer;
    pNode = CCParallaxNodeTile::create();
    m_layer->addChild(pNode);
    
        
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCSprite *sprite = CCSprite::create("ctm_island_BG_01.png");
    sprite->setScaleX(s.width/940.0f);
    sprite->setScaleY(s.width/940.0f);
    pNode->addChild(sprite,0,CCPointMake(1.0f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,40.0f));
    bool tikiObjsLoaded = ScreenHelper::AddOBBSpriteToCache("TikiObjs.png","TikiObjs.plist");
    bool tikiListLoaded = ScreenHelper::AddOBBSpriteToCache("Tiki.png","Tiki.plist");
    if(tikiListLoaded)
    {
        char name[64];
        sprintf(name,"ctm_Island_%02d.png",(RandomInt(1, 21)));
        sprite = CCSprite::createWithSpriteFrameName(name);
        sprite->setScale(scale);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 64.0f, 80.0f));
        m_Scale9[0] = sprite;
        
        sprintf(name,"ctm_Island_%02d.png",(RandomInt(1, 21)));
        sprite = CCSprite::createWithSpriteFrameName(name);
        sprite->setScale(scale);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 380.0f, 80.0f));
        m_Scale9[1] = sprite;
        
        
        sprintf(name,"ctm_Island_%02d.png",(RandomInt(1, 21)));
        sprite = CCSprite::createWithSpriteFrameName(name);
        sprite->setScale(scale);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 680.0f, 80.0f));
        m_Scale9[2] = sprite;
        
        sprintf(name,"ctm_Island_%02d.png",(RandomInt(1, 21)));
        sprite = CCSprite::createWithSpriteFrameName(name);
        sprite->setScale(scale);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 980.0f, 80.0f));
        m_Scale9[3] = sprite;
        
        numScale9 = 4;
    }
    else if(tikiObjsLoaded)
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_Island_01.png");
        sprite->setScale(scale);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 64.0f, 80.0f));
        m_Scale9[0] = sprite;
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_Island_02.png");
        sprite->setScale(scale);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 380.0f, 80.0f));
        m_Scale9[1] = sprite;
        
        numScale9 = 2;
    }
    else
    {
        numScale9 = 0;
    }
    
    
    m_Parallax1 = CCArray::createWithCapacity(4);
    m_Parallax1->retain();
    for(int i = 0; i < 4; i++)
    {
        if(tikiListLoaded)
        {
            char grassname[64];
            sprintf(grassname,"ctm_Grass_withplants_0%d.png",(RandomInt(1, 8)));
            sprite = CCSprite::createWithSpriteFrameName(grassname);
        }
        else
            sprite = CCSprite::create("ctm_Grass_withplants_00.png");
        
        sprite->setScale(scale);
        m_Parallax1Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 53.0f);
        pNode->addChild(sprite,1,CCPointMake(0.90f,0.0f),m_Parallax1Points[i]);
        m_Parallax1->addObject(sprite);
    }
    if(tikiObjsLoaded)
    {
        m_Parallax2 = CCArray::createWithCapacity(4);
        m_Parallax2->retain();
        m_Parallax3 = CCArray::createWithCapacity(4);
        m_Parallax3->retain();
        m_Parallax4 = CCArray::createWithCapacity(4);
        m_Parallax4->retain();
        
        for(int i = 0; i < 4; i++)
        {
            //head
            char name[64];
            if(RandomInt(0, 100)>80)
            {
                sprintf(name,"ctm_Tiki__Head_0%02d.png",(RandomInt(1, 24)));
                sprite = CCSprite::createWithSpriteFrameName(name);
                sprite->setScale(scale);
                m_Parallax2Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i-64.0f, 143.0f);
                pNode->addChild(sprite,2,CCPointMake(0.90f,0.0f),m_Parallax2Points[i]);
                m_Parallax2->addObject(sprite);
            }
            else
            {
                sprintf(name,"ctm_plant_%d.png",(RandomInt(22, 30)));
                sprite = CCSprite::createWithSpriteFrameName(name);
                sprite->setScale(scale);
                m_Parallax2Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i-64.0f, 123.0f);
                pNode->addChild(sprite,2,CCPointMake(0.90f,0.0f),m_Parallax2Points[i]);
                m_Parallax2->addObject(sprite);                
            }
            
            //torch
            sprintf(name,"ctm_Tiki_torch_0%d.png",(RandomInt(1, 10)));
            sprite = CCSprite::createWithSpriteFrameName(name);
            sprite->setScale(scale);
            m_Parallax3Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 93.0f);
            pNode->addChild(sprite,2,CCPointMake(0.90f,0.0f),m_Parallax3Points[i]);
            m_Parallax3->addObject(sprite);
            CCParticleSystem *fire = CCParticleSystemQuad::create("TorchFire6.plist");
            //fire->setScale(10.0f);
            fire->setPosition(ccp(sprite->getContentSize().width/2.0f+2.5f,sprite->getContentSize().height));
            fire->setPositionType(kCCPositionTypeRelative);
            sprite->addChild(fire);

            
            //palm
            
            sprintf(name,"ctm_palm_0%d.png",(RandomInt(1, 7)));
            sprite = CCSprite::createWithSpriteFrameName(name);
            sprite->setScale(scale);
            m_Parallax4Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i+64.0f, 133.0f);
            pNode->addChild(sprite,0,CCPointMake(0.90f,0.0f),m_Parallax4Points[i]);
            if(RandomInt(0, 100)>80)
                m_Parallax4->addObject(CCNode::create());
            else
                m_Parallax4->addObject(sprite);
        }
        
    }
    else
    {
        m_Parallax2 = NULL;
    }
    
    m_Track = CCArray::createWithCapacity(4);
    m_Track->retain();
    for(int i = 0; i < 4; i++)
    {
        sprite = CCSprite::create("ctm_island_FG_01.png");
        sprite->setScaleX(scaleX);
        sprite->setScaleY(scaleY * 0.5f);
        m_TrackPoints[i] = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT);
        m_TrackPoints[i].x += (256.0f*i)*scaleX;
        m_TrackPoints[i].y += -28.0f*scale;
        sprite->setPosition(m_TrackPoints[i]);
        m_layer->addChild(sprite,4);
        m_Track->addObject(sprite);
    }
    
    
}
void TikiBackGround::Step(float xpos, float ypos)
{
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float zoom  = ScreenHelper::getCameraZoom();
    
    for(int i = 0; i < numScale9; i++)
    {
        float factor = (1.0f-0.5f);
        float zoomScaleDiff = (1.0f-zoom);
        float newscale = 1.0f-(factor*zoomScaleDiff);
        
        m_Scale9[i]->setScale(newscale*scale);
    }
    BackGround::Step(xpos,ypos);
    
    float count = m_Parallax1->count();
    for ( int ii = 0  ; ii < m_Parallax1->count() ; ii++ )
    {
        CCSprite * parallaxPiece = (CCSprite *)(m_Parallax1->objectAtIndex(ii));
        parallaxPiece->setScale(scaleX*zoom);
        
        CCPoint newPoint;
        newPoint.x = m_Parallax1Points[ii].x*zoom;
        newPoint.y = m_Parallax1Points[ii].y*zoom;
        
        float xRatio = ((CCParallaxNodeTile*)pNode)->getRatio(parallaxPiece).x;
        ((CCParallaxNodeTile*)pNode)->setOffset(newPoint, parallaxPiece);
        
        float size = parallaxPiece->getContentSize().width*scaleX*zoom;

        if(m_Parallax2)
        {
            CCPoint newPoint2;
            CCSprite *parallaxPiece2;
            
            newPoint2.x = m_Parallax2Points[ii].x*zoom;
            newPoint2.y = m_Parallax2Points[ii].y*zoom;
            parallaxPiece2 = (CCSprite *)(m_Parallax2->objectAtIndex(ii));
            ((CCParallaxNodeTile*)pNode)->setOffset(newPoint2, parallaxPiece2);
            parallaxPiece2->setScale(scaleX*zoom);
            if ( (newPoint2.x + size) < (xpos*(1.0f-xRatio)))
            {
                m_Parallax2Points[ii].x += 256.0f*scaleX*count;
            }
            if ( (newPoint2.x + size) > ((xpos*(1.0f-xRatio))+256.0f*scaleX*count - 150.0f*scaleX))
            {
                m_Parallax2Points[ii].x -= 256.0f*scaleX*count;
            }
            
            newPoint2.x = m_Parallax3Points[ii].x*zoom;
            newPoint2.y = m_Parallax3Points[ii].y*zoom;
            parallaxPiece2 = (CCSprite *)(m_Parallax3->objectAtIndex(ii));
            ((CCParallaxNodeTile*)pNode)->setOffset(newPoint2, parallaxPiece2);
            parallaxPiece2->setScale(scaleX*zoom);
            if ( (newPoint2.x + size) < (xpos*(1.0f-xRatio)))
            {
                m_Parallax3Points[ii].x += 256.0f*scaleX*count;
            }
            if ( (newPoint2.x + size) > ((xpos*(1.0f-xRatio))+256.0f*scaleX*count - 150.0f*scaleX))
            {
                m_Parallax3Points[ii].x -= 256.0f*scaleX*count;
            }
            
            newPoint2.x = m_Parallax4Points[ii].x*zoom;
            newPoint2.y = m_Parallax4Points[ii].y*zoom;
            parallaxPiece2 = (CCSprite *)(m_Parallax4->objectAtIndex(ii));
            ((CCParallaxNodeTile*)pNode)->setOffset(newPoint2, parallaxPiece2);
            parallaxPiece2->setScale(scaleX*zoom);
            if ( (newPoint2.x + size) < (xpos*(1.0f-xRatio)))
            {
                m_Parallax4Points[ii].x += 256.0f*scaleX*count;
            }
            if ( (newPoint2.x + size) > ((xpos*(1.0f-xRatio))+256.0f*scaleX*count - 150.0f*scaleX))
            {
                m_Parallax4Points[ii].x -= 256.0f*scaleX*count;
            }
        }
        
        if ( (newPoint.x + size) < (xpos*(1.0f-xRatio)))
        {
            m_Parallax1Points[ii].x += 256.0f*scaleX*count;
        }
        if ( (newPoint.x + size) > ((xpos*(1.0f-xRatio))+256.0f*scaleX*count - 150.0f*scaleX))
        {
            m_Parallax1Points[ii].x -= 256.0f*scaleX*count;
        }
    }
}

TikiBackGround::~TikiBackGround()
{
    if(m_Parallax2)
    {
        m_Parallax2->release();
        m_Parallax3->release();
        m_Parallax4->release();
    }
}
