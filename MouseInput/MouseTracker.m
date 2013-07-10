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
        eventMonitor = [NSEvent addLocalMonitorForEventsMatchingMask:(NSLeftMouseDownMask | NSLeftMouseUpMask)
                                                             handler:^(NSEvent *theEvent) {
                                                                 [self postMouseState:theEvent];
                                                                 return theEvent;
                                                             }];
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


- (void)postMouseState:(NSEvent *)theEvent
{
    boost::shared_ptr<mw::MouseInputDevice> mouseInputDevice = mouseInputDeviceWeak.lock();
    if (mouseInputDevice) {
        mouseInputDevice->postMouseState([theEvent type] == NSLeftMouseDown);
    }
}


- (void)dealloc
{
    [NSEvent removeMonitor:eventMonitor];
    [super dealloc];
}


@end

























