//
//  MouseTracker.m
//  MouseInput
//
//  Created by Christopher Stawarz on 5/29/13.
//  Copyright (c) 2013 The MWorks Project. All rights reserved.
//

#import "MouseTracker.h"

#include "MouseInputDevice.h"


@implementation MWKMouseTracker


- (id)initWithMouseInputDevice:(boost::shared_ptr<mw::MouseInputDevice>)mouseInputDevice
{
    if ((self = [super init])) {
        mouseInputDeviceWeak = mouseInputDevice;
    }
    
    return self;
}


- (void)mouseEntered:(NSEvent *)theEvent
{
    [self postMouseLocation:theEvent];
}


- (void)mouseExited:(NSEvent *)theEvent
{
    [self postMouseLocation:theEvent];
}


- (void)mouseMoved:(NSEvent *)theEvent
{
    [self postMouseLocation:theEvent];
}


- (void)postMouseLocation:(NSEvent *)theEvent
{
    boost::shared_ptr<mw::MouseInputDevice> mouseInputDevice = mouseInputDeviceWeak.lock();
    if (mouseInputDevice) {
        mouseInputDevice->postMouseLocation([theEvent locationInWindow]);
    }
}


@end

























