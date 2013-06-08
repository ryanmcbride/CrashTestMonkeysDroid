//
//  HelloWorldScene.h
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#ifndef __BACKGROUND_H__
#define __BACKGROUND_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"


class BackGround : public cocos2d::CCLayer
{
public:
    virtual ~BackGround();
    BackGround();
    virtual void InitBG(cocos2d::CCNode *layer);
    
    static BackGround *create(cocos2d::CCNode *layer);
    
    virtual void Step(float xpos, float ypos);
protected:
    cocos2d::CCNode *m_layer;
    cocos2d::CCPoint m_Parallax1Points[4];
    cocos2d::CCArray *m_Parallax1;
    
    cocos2d::CCPoint m_TrackPoints[4];
    cocos2d::CCArray *m_Track;
    cocos2d::CCParallaxNode *pNode;
};

class CCParallaxNodeTile : public cocos2d::CCParallaxNode
{
public:
    CCParallaxNodeTile(){}
    
    static CCParallaxNodeTile *create();
    void setOffset(cocos2d::CCPoint offset,cocos2d::CCNode* node);
    cocos2d::CCPoint getRatio(cocos2d::CCNode* node);
};


#endif // __BACKGROUND_H__
