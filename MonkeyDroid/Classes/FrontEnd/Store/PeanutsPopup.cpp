//
//  Store.mm
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "PeanutsPopup.h"
#import "Store.h"
#import "SaveManager.h"
#import "CCLabelFX.h"
#import "AudioManager.h"

@implementation PeanutsPopup

static BOOL s_isPopupActive = NO;

+(BOOL) isActive
{
    return s_isPopupActive;
}


+(id) scene
{
	// 'scene' is an autorelease object.
	CCScene *scene = [CCScene node];
	
	// 'layer' is an autorelease object.
	PeanutsPopup *layer = [PeanutsPopup node];
	
	// add layer as a child to scene
	[scene addChild: layer];
	
	// return the scene
	return scene;
}
-(void) buildPopUp
{
    CGSize screenSize = [CCDirector sharedDirector].winSize;
    CCLOG(@"Screen width %0.2f screen height %0.2f",screenSize.width,screenSize.height);
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
    CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
    sprite.position = ccp(screenSize.width/2, screenSize.height/2-30);
    [self addChild:sprite];
    
    
    CGSize dim;
    dim.width = 300.0f;
    dim.height = 25.0f;
    
    CCLabelFX *label = [CCLabelFX labelWithString:@"Need More Peanuts!"
                                       dimensions:dim
                                        alignment:CCTextAlignmentCenter
                                         fontName:@"Jacoby ICG Black.ttf"
                                         fontSize:20
                                     shadowOffset:CGSizeMake(2,-2)
                                       shadowBlur:1.0f
                                      shadowColor:ccc4(0,0,0,255)
                                        fillColor:ccc4(237,188,0,255)];
    label.position = ccp(315.0f/2.0f,85);
    [sprite addChild:label];
    
    label = [CCLabelFX labelWithString:@"Would you like to get more Peanuts?"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:15
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(230,230,230,255)];
    label.position = ccp(315.0f/2.0f,65);
    [sprite addChild:label];
    
    dim.width = 50.0f;
    dim.height = 35.0f;
    label = [CCLabelFX labelWithString:@"Yes"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:30
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(237,188,0,255)];
    
    CCMenuItem *yes = [CCMenuItemFont itemWithLabel:label
                                             target:self
                                           selector:@selector(yesbuttonPushed:)];
    
    label = [CCLabelFX labelWithString:@"No"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:30
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(237,188,0,255)];
    CCMenuItem *no = [CCMenuItemFont itemWithLabel:label
                                            target:self
                                          selector:@selector(nobuttonPushed:)];
    
    CCMenu *pop = [CCMenu menuWithItems:no, yes, nil];
    pop.position = ccp(315.0f/2.0f,110.0f/2.0f-25);
    [pop alignItemsHorizontallyWithPadding:30];
    
    [sprite addChild:pop];
    
    [sprite setPosition:ccp(sprite.position.x-250.0f,sprite.position.y)];
    [sprite runAction: [CCMoveBy actionWithDuration:0.1f position:ccp(250, 0)]];
}
// initialize your instance here
-(id) init
{
	if( (self=[super init]))
    {
		
		// enable touches
		self.isTouchEnabled = YES;
		
		
		[self buildPopUp];
        
        s_isPopupActive = YES;
	}
	return self;
}

-(void) yesbuttonPushed:(id)sender
{
    AudioManager::PlayEffect(AUDIO_SELECT);
    [(StoreScene*)self.parent StartGetPeanuts];
    [self StopPeanuts];
}

-(void) nobuttonPushed:(id)sender
{
    AudioManager::PlayEffect(AUDIO_SELECT);
    [self StopPeanuts];
}

-(void) StopPeanuts
{
	id action = [CCSequence actions:
                 [CCMoveBy actionWithDuration:0.1f position:CGPointMake(-250, 0)],
				 [CCCallFuncND actionWithTarget:self selector:@selector(removeFromParentAndCleanup:) data:(void*)YES],
                 nil];
	
	[self runAction:action ];	
}

- (void)ccTouchesEnded:(NSSet *)touches withEvent:(UIEvent *)event
{
	//Add a new body/atlas sprite at the touched location
	for( UITouch *touch in touches ) 
	{
		CGPoint location = [touch locationInView: [touch view]];
		
		location = [[CCDirector sharedDirector] convertToGL: location];		
	}
}


// on "dealloc" you need to release all your retained objects
- (void) dealloc
{
    s_isPopupActive = NO;

	// don't forget to call "super dealloc"
	[super dealloc];
}
@end

@implementation FlipPopup
-(void) buildPopUp
{
    CGSize screenSize = [CCDirector sharedDirector].winSize;
    CCLOG(@"Screen width %0.2f screen height %0.2f",screenSize.width,screenSize.height);
    
    [[CCSpriteFrameCache sharedSpriteFrameCache] addSpriteFramesWithFile:@"Tutorial.plist"textureFile:@"Tutorial.pvr.ccz"];
    CCSprite *sprite = [CCSprite spriteWithSpriteFrameName:@"ctm_Tutorial_Text_Blank.png"];
    sprite.position = ccp(screenSize.width/2, screenSize.height/2-30);
    [self addChild:sprite];
    
    
    CGSize dim;
    dim.width = 300.0f;
    dim.height = 25.0f;
    
    CCLabelFX *label = [CCLabelFX labelWithString:@"You Can Now Flip!"
                                       dimensions:dim
                                        alignment:CCTextAlignmentCenter
                                         fontName:@"Jacoby ICG Black.ttf"
                                         fontSize:20
                                     shadowOffset:CGSizeMake(2,-2)
                                       shadowBlur:1.0f
                                      shadowColor:ccc4(0,0,0,255)
                                        fillColor:ccc4(237,188,0,255)];
    label.position = ccp(315.0f/2.0f,85);
    [sprite addChild:label];
    
    dim.width = 280.0f;
    dim.height = 45.0f;
    label = [CCLabelFX labelWithString:@"While in the Air, tilt left or right to flip.  Tilt back to center to stop flipping."
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:15
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(230,230,230,255)];
    label.position = ccp(315.0f/2.0f,55);
    [sprite addChild:label];
    
    dim.width = 50.0f;
    dim.height = 35.0f;
    label = [CCLabelFX labelWithString:@"Yes"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:30
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(237,188,0,255)];
    
    //CCMenuItem *yes = [CCMenuItemFont itemWithLabel:label
    //                                         target:self
    //                                       selector:@selector(yesbuttonPushed:)];
    
    label = [CCLabelFX labelWithString:@"OK"
                            dimensions:dim
                             alignment:CCTextAlignmentCenter
                              fontName:@"Jacoby ICG Black.ttf"
                              fontSize:30
                          shadowOffset:CGSizeMake(2,-2)
                            shadowBlur:1.0f
                           shadowColor:ccc4(0,0,0,255)
                             fillColor:ccc4(237,188,0,255)];
    CCMenuItem *no = [CCMenuItemFont itemWithLabel:label
                                            target:self
                                          selector:@selector(nobuttonPushed:)];
    
    CCMenu *pop = [CCMenu menuWithItems:no, nil];
    pop.position = ccp(315.0f/2.0f,110.0f/2.0f-25);
    [pop alignItemsHorizontallyWithPadding:30];
    
    [sprite addChild:pop];
    
    [sprite setPosition:ccp(sprite.position.x-250.0f,sprite.position.y)];
    [sprite runAction: [CCMoveBy actionWithDuration:0.1f position:ccp(250, 0)]];
}
@end