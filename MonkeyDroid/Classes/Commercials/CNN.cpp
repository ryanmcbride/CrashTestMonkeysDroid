//
//  HelloWorldScene.cpp
//  MonkeyDroid
//
//  Created by Admin on 3/19/13.
//  Copyright __MyCompanyName__ 2013. All rights reserved.
//
#include "CNN.h"
#include "SimpleAudioEngine.h"
#include "../ScreenHelper.h"
#include "../AudioManager.h"

using namespace cocos2d;
using namespace CocosDenshion;

CNN::CNN()
{
    float scale = ScreenHelper::getTextureScale();
    float scaleX = ScreenHelper::getTextureScaleX();
    float scaleY = ScreenHelper::getTextureScaleY();
    
    CCSpriteFrameCache::sharedSpriteFrameCache()->addSpriteFramesWithFile("CNN.plist","CNN.png");
    
    CCSprite *sprite = CCSprite::createWithSpriteFrameName("ctm_News_Background.png");
    sprite->setScale(scale);
    sprite->setPosition(ScreenHelper::getAnchorPoint(ScreenHelper::ANCHOR_CENTER));
    addChild(sprite);
    
    int storyBGIndex = RandomInt(1,5);
    char storyBGName[64];
    sprintf(storyBGName,"ctm_News_Screen_%02d.png",storyBGIndex);
    
    sprite = CCSprite::createWithSpriteFrameName(storyBGName);
    sprite->setScale(scale);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, 39, 16));
    addChild(sprite);
    
    
    const char* StoryArray[42] =
    {
        "Serial Voyeur Jane Goodall Spotted in Tanzania",
        "I will not eat cat poop!",
        "Foolish Monkey Crashes Motorcycle",
        "My cat can eat the whole watermelon",
        "News Anchor Breaks 4th Wall",
        "Giant Human climbs Empire State Building",
        "Your Brains are a 1/3 the size of ours",
        "Congress passes gas ..... bill",
        "Incontinent War Impacts World",
        "Missing link discovered. Broken chain now fixed",
        
        "Baboon wins date with \"Gorilla's Next Door\" star",
        "Bonobo wins annual poop throwing contest",
        "Actor Mel Gibbon missing in Congo Rainforest",
        "Sea Monkeys....Can they really be trusted?",
        "Lonely Gorilla adopts 30 cats",
        "Chimpanzee graduates Havard Business School with Honors",
        "Gibbon poses for Spanish fresco",
        "Friends of monkee hoarding peanuts express concern",
        "Banana split on I-5 causes major delays",
        "Monkey arrested for concealing weapon claims it was only a banana",
        "Chimps Gone Wild cause disturbance in library",
        "Chimp debates with self on evolution...and loses",
        "Orangutan swingers from out of town finally roped in",
        "Banana smoothie craze causes riots. Chimps out of control…again!",
        "\"Careful, it's a jungle out there\" say police responding to traffic chaos.",
        "Worlds tallest treehouse finally finished at a cost of 15,000,000 peanuts.",
        "Breaking News: Nutty Professor arrested for mixing Peanuts with Butter.",
        "Monkey biker amazes with record breaking number of bike flips.",
        "New triple loop freeway causing dizziness. Officials mystified.",
        
        "Monkey Centipede movie banned from stores.",
        "I'm tired of these Monkey Fighting Snakes in this Monday to Friday Game!",
        "Drama unfolds after Stefano implants a chimp in Hope's brain!",
        "Flee to the planet with the yellow sun, it will give you great strength",
        "Sometimes I doubt your commitment to Sparkle Motion",
        "San Dimas High School Football Rules!",
        "Duck!!!",
        "Rally against apathy draws small crowd.",
        "Literacy an obstable, study finds",
        "City Council unsure why sewer smells.",
        "Psychics predict the world didn't end yesterday",
        "Monkeys using iPads solve mystery of Universe",
        "What do I have in my Pocket?",
    };
    int index = RandomInt(0,42);
    
    //  Measure the height of the string given the width.
    float fontSize = 18*scale;
    //CCSize maxSize = CCSizeMake( 120*scale, 400*scale );		// Start off with an actual width and a height.
    
    // Calculate the actual size of the text with the font, size and line break mode.
    //CCSize actualSize = [StoryArray[index] sizeWithFont:[UIFont fontWithName:"impact.ttf" size:fontSize]
    //                                  constrainedToSize:maxSize
    //                                      lineBreakMode:UILineBreakModeWordWrap);
    //actualSize.height += 50;
    CCSize containerSize = CCSizeMake( 120*scale, 400*scale );
    
    CCLabelTTF *labelFX = CCLabelTTF::create(StoryArray[index],"impact.ttf",fontSize,containerSize,kCCTextAlignmentRight);
    labelFX->setColor(ccc3(230,230,210));
    labelFX->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,102,95-200));
    
    CCLabelTTF *labelFXShadow = CCLabelTTF::create(StoryArray[index],"impact.ttf",fontSize,containerSize,kCCTextAlignmentRight);
    labelFXShadow->setColor(ccc3(0,0,0));
    labelFXShadow->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,102,95-200));
    
    addChild(labelFX,0);
    
    
    int themeIndex = RandomInt(0,10);
    if(themeIndex == 0)//Mexico
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_AnchorSuit.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,-75));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_Anchor_Hat_rear.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,17));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_AnchorHead.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        
        int anchorMouthIndex = RandomInt(1,6);
        char anchorMouthName[64];
        sprintf(anchorMouthName,"ctm_News_Anchor_mth%02d.png",anchorMouthIndex);
        sprite = CCSprite::createWithSpriteFrameName(anchorMouthName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        mouthSprite = sprite;
        mouthIndex = anchorMouthIndex;
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_Anchor_Hat_Front.png");
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,45));
        sprite->setScale(scale);
        addChild(sprite);
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_Anchor_Hat_Shadow.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,23));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Desktop.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,0));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_Picture.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-165,55));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_Items.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,-80));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Mexico_Wall_item.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-210,80));
        addChild(sprite);
        
    }
    else if(themeIndex == 1)//Hawaii
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Hawaii_Anchor_suit.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-13,-75));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_AnchorHead.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        
        int anchorMouthIndex = RandomInt(1,6);
        char anchorMouthName[64];
        sprintf(anchorMouthName,"ctm_News_Anchor_mth%02d.png",anchorMouthIndex);
        sprite = CCSprite::createWithSpriteFrameName(anchorMouthName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        mouthSprite = sprite;
        mouthIndex = anchorMouthIndex;
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Desktop.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,0));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Hawaii_Picture.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-165,55));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Hawaii_DeskItems.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,-80));
        addChild(sprite);
    }
    else if(themeIndex == 2)//Halloween
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Halloween_Anchor.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,-75));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Desktop.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,0));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Halloween_Picture.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-165,55));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Halloween_Desk.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,-80));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Halloween_ghost.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,60,120));
        addChild(sprite);
        
        mouthSprite = NULL;
        
    }
    else if(themeIndex == 3)//Disco
    {
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Disco_Anchor.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,-75));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_AnchorHead.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        
        int anchorMouthIndex = RandomInt(1,6);
        char anchorMouthName[64];
        sprintf(anchorMouthName,"ctm_News_Anchor_mth%02d.png",anchorMouthIndex);
        sprite = CCSprite::createWithSpriteFrameName(anchorMouthName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        mouthSprite = sprite;
        mouthIndex = anchorMouthIndex;
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Disco_Head_Piece.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-13,37));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Desktop.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,0));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Disco_Picture.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-165,55));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Disco_Desk.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,-80));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Disco_Ball.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,30,120));
        addChild(sprite);
        
    }
    else //if(themeIndex == 1)
    {
        int anchorTieIndex = RandomInt(1, 18);
        char anchorTieName[64];
        sprintf(anchorTieName,"ctm_News_anchor_tie_%02d.png",anchorTieIndex);
        sprite = CCSprite::createWithSpriteFrameName(anchorTieName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,-75));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_anchor_Suit.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,-75));
        addChild(sprite);
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_AnchorHead.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        
        int anchorMouthIndex = RandomInt(1,6);
        char anchorMouthName[64];
        sprintf(anchorMouthName,"ctm_News_Anchor_mth%02d.png",anchorMouthIndex);
        sprite = CCSprite::createWithSpriteFrameName(anchorMouthName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-10,0));
        addChild(sprite);
        mouthSprite = sprite;
        mouthIndex = anchorMouthIndex;
        
        sprite = CCSprite::createWithSpriteFrameName("ctm_News_Desktop.png");
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,0));
        addChild(sprite);
        
        int pictureIndex = RandomInt(1, 12);
        char pictureName[64];
        sprintf(pictureName,"ctm_News_PictureFrame_%02d.png",pictureIndex);
        sprite = CCSprite::createWithSpriteFrameName(pictureName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-165,55));
        addChild(sprite);
        
        int deskItemIndex = RandomInt(1, 16);
        char deskItemName[64];
        sprintf(deskItemName,"ctm_News_Desk_item_%02d.png",deskItemIndex);
        sprite = CCSprite::createWithSpriteFrameName(deskItemName);
        sprite->setScale(scale);
        sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,-170,-75));
        addChild(sprite);
    }
    
    //CCLayerColor *tickerBar = [CCLayerColor layerWithColor:ccc4(255,255,0,120) width:640.0f height:20.0f);
    //addChild(tickerBar);
    //tickerBar->setPosition(ccp(0.0f,25.0f);
    int tempNum = index;
    do
    {
        index = RandomInt(0,42);
    }
    while (tempNum==index);
    
    CCLabelTTF *tickerlabel = CCLabelTTF::create(StoryArray[index],"impact.ttf",18*scale);
    addChild(tickerlabel);
    tickerlabel->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,360,-144.5));
    tickerlabel->setColor(ccc3(187,140,52));
    tickerlabel->runAction(CCMoveBy::create(14.0f,ccp(-600.0f*scale,0.0f)));
    
    int randInt = RandomInt(0, 100);
    if(randInt > 50)
        sprite = CCSprite::createWithSpriteFrameName("ctm_CNN_TitleCard.png");
    else
        sprite = CCSprite::createWithSpriteFrameName("ctm_CNN_TitleCard2.png");
    sprite->setScale(scale);
    sprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER,0,0));
    addChild(sprite);
    sprite->runAction(
                      CCSequence::create(
                                         CCDelayTime::create(3.0f),
                                         CCMoveTo::create(1.0f,CCPointMake(480*scaleX*1.6f, 160*scaleY)),
                                         NULL));
    sprite->runAction(
                      CCSequence::create(
                                         CCDelayTime::create(2.8f),
                                         CCScaleTo::create(0.2f,0.2f),
                                         NULL));
    sprite->runAction(
                      CCSequence::create(
                                         CCDelayTime::create(2.8f),
                                         CCRotateBy::create(1.2f,720.0f),
                                         NULL));
        
    if(mouthSprite != NULL)
    {
        mouthIndexTime = 3.5f;
        talkTime = mouthIndexTime + 6.0f;
        m_TimeOut = talkTime + 0.5f;
    }
    else
    {
        talkTime = -1.0f;
        m_TimeOut = 7.0f;
    }
    //[Options PlayEffect:AUDIO_NEWS_INTRO);
    bMouthAudio = false;
    m_mouthAudio = 0;
}
CNN::~CNN()
{
    
}
void CNN::update(float dt)
{
    Commercial::update(dt);
    float scale = ScreenHelper::getTextureScale();
    
        mouthIndexTime -= dt;
        talkTime -= dt;
        if(talkTime > 0.0f && mouthIndexTime <= 0.0f)
        {
            if(!bMouthAudio)
            {
                //[Options PlayEffect:AUDIO_MONKEY_ANCHOR_1+RandomInt(0,6)];
                m_mouthAudio = AudioManager::PlayEffect(AUDIO_NEWS_ANCHOR);
                bMouthAudio = true;
            }
            
            mouthSprite->removeFromParentAndCleanup(true);
            
            int anchorMouthIndex = RandomInt(1,6);
            while (anchorMouthIndex == mouthIndex)
            {
                anchorMouthIndex = RandomInt(1,6);
            }
            char anchorMouthName[64];
            sprintf(anchorMouthName,"ctm_News_Anchor_mth%02d.png",anchorMouthIndex);
            mouthSprite = CCSprite::createWithSpriteFrameName(anchorMouthName);
            mouthSprite->setScale(scale);
            mouthSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -10, 0));
            addChild(mouthSprite);
            mouthIndex = anchorMouthIndex;
            
            mouthIndexTime = RandomFloat(1.5f/30.0f, 4.0f/30.0f);
        }
        else if(mouthSprite != NULL && mouthIndexTime <= 0.0f)
        {
            mouthSprite->removeFromParentAndCleanup(true);
            
            int anchorMouthIndex = 2;
            char anchorMouthName[64];
            sprintf(anchorMouthName,"ctm_News_Anchor_mth%02d.png",anchorMouthIndex);
            mouthSprite = CCSprite::createWithSpriteFrameName(anchorMouthName);
            mouthSprite->setScale(scale);
            mouthSprite->setPosition(ScreenHelper::getAnchorPointPlusOffset(ScreenHelper::ANCHOR_CENTER, -10, 0));
            addChild(mouthSprite);
            mouthIndex = anchorMouthIndex;
            
            mouthIndexTime = 1000.0f;
        }
    
    if(!SimpleAudioEngine::sharedEngine()->isBackgroundMusicPlaying())
        SimpleAudioEngine::sharedEngine()->playBackgroundMusic("CTMNewsMusic.3gp", true);
}


