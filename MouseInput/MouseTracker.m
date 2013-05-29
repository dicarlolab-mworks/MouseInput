//
//  MouseTracker.m
//  MouseInput
//
//  Created by Christopher Stawarz on 5/29/13.
//  Copyright (c) 2013 The MWorks Project. All rights reserved.
//

#import "MouseTracker.h"


@implementation MouseTracker


- (void)mouseEntered:(NSEvent *)theEvent
{
    
}


- (void)mouseExited:(NSEvent *)theEvent
{
    
}


- (void)mouseMoved:(NSEvent *)theEvent
{
    NSPoint location = [theEvent locationInWindow];
    mw::mprintf("mouse location = (%g, %g)", location.x, location.y);
}


@end
