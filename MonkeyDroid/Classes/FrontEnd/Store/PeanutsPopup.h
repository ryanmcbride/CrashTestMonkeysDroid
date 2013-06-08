//
//  Store.h
//  CTM
//
//  Created by Ryan McBride on 1/14/12.
//  Copyright 2012 __MyCompanyName__. All rights reserved.
//

#import "cocos2d.h"


@interface PeanutsPopup : CCLayer
{
}
// returns a Scene that contains the MainMenu as the only child
+(id) scene;
-(void) StopPeanuts;
-(void) buildPopUp;
+(BOOL) isActive;
@end

@interface FlipPopup : PeanutsPopup
{
}
-(void) buildPopUp;
@end
