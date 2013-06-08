//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "TutorialBackGround.h"
#include "SimpleAudioEngine.h"
#include "../../ScreenHelper.h"
#include "../Level.h"

using namespace cocos2d;
using namespace CocosDenshion;


TutorialBackGround::TutorialBackGround()
{
}
void TutorialBackGround::InitBG(cocos2d::CCNode *layer)
{
    glClearColor(0.0f/255.0f, 0.0f/255.0f, 0.0f/255.0f, 1.0f);
    m_layer = layer;
    pNode = CCParallaxNodeTile::create();
    m_layer->addChild(pNode);
    
    
    CCTextureCache::sharedTextureCache()->addPVRImage("TutorialBG.pvr.ccz");
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("TutorialBG.plist");
    
    
    CCSize s = CCDirector::sharedDirector()->getWinSize();
    
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_Android_Tutorial_BG1.png");
    sprite->setScaleX(s.width/940.0f);
    sprite->setScaleY(s.width/940.0f);
    pNode->addChild(sprite,0,CCPointMake(1.0f,0.0f),ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0.0f,-40.0f));
    
    m_Parallax1 = CCArray::createWithCapacity(4);
    m_Parallax1->retain();
    for(int i = 0; i < 4; i++)
    {
        char temp[64];
        sprintf(temp,"CTM_EasterHeads_BG_%d.png",RandomInt(1,7));
        sprite = CCSprite::createWithSpriteFrameName(temp);
        sprite->setScale(scale*0.5f);
        m_Parallax1Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 113.0f);
        pNode->addChild(sprite,0,CCPointMake(0.99f,0.0f),m_Parallax1Points[i]);
        m_Parallax1->addObject(sprite);
        
    }
    
    m_Parallax2 = CCArray::createWithCapacity(4);
    m_Parallax2->retain();
    for(int i = 0; i < 4; i++)
    {
        char temp[64];
        sprintf(temp,"CTMStatue_%d.png",RandomInt(1,6));
        sprite = CCSprite::createWithSpriteFrameName(temp);
        sprite->setScale(scale*0.5f);
        m_Parallax2Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 64+512.0f*i, 133.0f);
        pNode->addChild(sprite,0,CCPointMake(0.97f,0.0f),m_Parallax2Points[i]);
        m_Parallax2->addObject(sprite);
        
    }
    
    m_Parallax3 = CCArray::createWithCapacity(4);
    m_Parallax3->retain();
    for(int i = 0; i < 4; i++)
    {
        char temp[64];
        sprintf(temp,"CTM_easterFG_%d.png",RandomInt(1,6));
        sprite = CCSprite::createWithSpriteFrameName(temp);
        sprite->setScale(scale*0.5f);
        m_Parallax3Points[i] = ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 384.0f*i, 73.0f);
        pNode->addChild(sprite,0,CCPointMake(0.95f,0.0f),m_Parallax3Points[i]);
        m_Parallax3->addObject(sprite);
        
    }
    
    m_Track = CCArray::createWithCapacity(4);
    m_Track->retain();
    for(int i = 0; i < 4; i++)
    {
        sprite = CCSprite::create("ctm_island_FG_01.png");
        sprite->setScaleX(scaleX);
        sprite->setScaleY(scaleY);
        m_TrackPoints[i] = ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_BOTTOM_LEFT);
        m_TrackPoints[i].x += (256.0f*i)*scaleX;
        m_TrackPoints[i].y += -30.0f*scale;
        sprite->setPosition(m_TrackPoints[i]);
        m_layer->addChild(sprite,4);
        m_Track->addObject(sprite);
        
        /*       sprite = CCSprite::create("ctm_256_Front_hazardstripe.png");
         sprite->setScaleX(scaleX);
         sprite->setScaleY(scaleY);
         sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_BOTTOM_LEFT, 256.0f*i, 55.0f));
         addChild(sprite,4);
         */
    }
    
    
}
void TutorialBackGround::Step(float xpos, float ypos)
{
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float zoom  = ScreenHelper::getCameraZoom();
    
    
    BackGround::Step(xpos,ypos);
    
    float count = m_Parallax1->count();
    for ( int ii = 0  ; ii < m_Parallax1->count() ; ii++ )
    {
        CCSprite * parallaxPiece = (CCSprite *)(m_Parallax1->objectAtIndex(ii));
        parallaxPiece->setScale(scaleX*zoom*0.5f);
        
        CCPoint newPoint;
        newPoint.x = m_Parallax1Points[ii].x*zoom;
        newPoint.y = m_Parallax1Points[ii].y;//*zoom;
        
        float xRatio = ((CCParallaxNodeTile*)pNode)->getRatio(parallaxPiece).x;
        ((CCParallaxNodeTile*)pNode)->setOffset(newPoint, parallaxPiece);
        //parallaxPiece->setPosition(newPoint);
        
        float size = parallaxPiece->getContentSize().width*scaleX*zoom;
        if ( (newPoint.x + size) < (xpos*(1.0f-xRatio)))
        {
            m_Parallax1Points[ii].x += 256.0f*scaleX*count;
        }
        if ( (newPoint.x + size) > ((xpos*(1.0f-xRatio))+256.0f*scaleX*count - 150.0f*scaleX))
        {
            m_Parallax1Points[ii].x -= 256.0f*scaleX*count;
        }
    }
    
    
    count = m_Parallax3->count();
    for ( int ii = 0  ; ii < m_Parallax3->count() ; ii++ )
    {
        CCSprite * parallaxPiece = (CCSprite *)(m_Parallax3->objectAtIndex(ii));
        parallaxPiece->setScale(scaleX*zoom*0.5f);
        
        CCPoint newPoint;
        newPoint.x = m_Parallax3Points[ii].x*zoom;
        newPoint.y = m_Parallax3Points[ii].y;//*zoom;
        
        float xRatio = ((CCParallaxNodeTile*)pNode)->getRatio(parallaxPiece).x;
        ((CCParallaxNodeTile*)pNode)->setOffset(newPoint, parallaxPiece);
        //parallaxPiece->setPosition(newPoint);
        
        float size = 384.0f*scaleX*zoom;
        if ( (newPoint.x + size) < (xpos*(1.0f-xRatio)))
        {
            m_Parallax3Points[ii].x += 384.0f*scaleX*count;
        }
        if ( (newPoint.x + size) > ((xpos*(1.0f-xRatio))+384.0f*scaleX*count - 150.0f*scaleX))
        {
            m_Parallax3Points[ii].x -= 384.0f*scaleX*count;
        }
    }
    
    
    count = m_Parallax2->count();
    for ( int ii = 0  ; ii < m_Parallax2->count() ; ii++ )
    {
        CCSprite * parallaxPiece = (CCSprite *)(m_Parallax2->objectAtIndex(ii));
        parallaxPiece->setScale(scaleX*zoom*0.5f);
        
        CCPoint newPoint;
        newPoint.x = m_Parallax2Points[ii].x*zoom;
        newPoint.y = m_Parallax2Points[ii].y;//*zoom;
        
        float xRatio = ((CCParallaxNodeTile*)pNode)->getRatio(parallaxPiece).x;
        ((CCParallaxNodeTile*)pNode)->setOffset(newPoint, parallaxPiece);
        //parallaxPiece->setPosition(newPoint);
        
        float size = 512.0f*scaleX*zoom;
        if ( (newPoint.x + size) < (xpos*(1.0f-xRatio)))
        {
            m_Parallax2Points[ii].x += 512.0f*scaleX*count;
        }
        if ( (newPoint.x + size) > ((xpos*(1.0f-xRatio))+512.0f*scaleX*count - 150.0f*scaleX))
        {
            m_Parallax2Points[ii].x -= 512.0f*scaleX*count;
        }
    }
}
TutorialBackGround::~TutorialBackGround()
{
}
