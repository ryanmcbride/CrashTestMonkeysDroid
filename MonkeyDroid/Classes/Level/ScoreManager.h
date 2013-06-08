//
//  CrashOverlay.h
//  CTM
//
//  Created by Ryan McBride on 6/4/11.
//  Copyright 2011 __MyCompanyName__. All rights reserved.
//

#ifndef __SCORE_MANAGER_H__
#define __SCORE_MANAGER_H__

#include "cocos2d.h"

class ScoreManager : public cocos2d::CCNode
{
public:
    ScoreManager();
    virtual ~ScoreManager();
    
    int GetTrick();
    int GetFlips();
    void AddScore(int score);
    void SetTrick(int tricknum);
    void SetFlips(int flips);
    void SetLoops(int loops);
    void SetFire();
    void FinishTrickGood(bool goodBad);
    bool DuringLockout();
    void update(float dt);
protected:
    cocos2d::CCNode *m_TrickNode;
    char trickString[128];
    bool trickReady;
    
    bool m_bFlaming;
    int m_iTrick;
    int m_iFlips;
    int m_iLoops;
    bool m_bOfFire;
    
    float m_time;
    cocos2d::CCLabelTTF *m_flamingLabel;
    cocos2d::CCLabelTTF *m_trickLabel;
    cocos2d::CCLabelTTF *m_flipLabel;
    cocos2d::CCLabelTTF *m_ofFireLabel;
};

#endif
