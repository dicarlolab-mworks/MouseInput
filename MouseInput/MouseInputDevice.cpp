//
//  MouseInputDevice.cpp
//  MouseInput
//
//  Created by Christopher Stawarz on 5/29/13.
//  Copyright (c) 2013 The MWorks Project. All rights reserved.
//

#include "MouseInputDevice.h"


BEGIN_NAMESPACE_MW


const std::string MouseInputDevice::MOUSE_POSITION_X("mouse_position_x");
const std::string MouseInputDevice::MOUSE_POSITION_Y("mouse_position_y");


void MouseInputDevice::describeComponent(ComponentInfo &info) {
    IODevice::describeComponent(info);
    
    info.setSignature("iodevice/mouse_input");
    
    info.addParameter(MOUSE_POSITION_X);
    info.addParameter(MOUSE_POSITION_Y);
}


MouseInputDevice::MouseInputDevice(const ParameterValueMap &parameters) :
    IODevice(parameters),
    posX(parameters[MOUSE_POSITION_X]),
    posY(parameters[MOUSE_POSITION_Y]),
    mainDisplayView(nil),
    tracker(nil),
    trackingArea(nil)
{ }


MouseInputDevice::~MouseInputDevice() {
    if (trackingArea) {
        [mainDisplayView removeTrackingArea:trackingArea];
        [trackingArea release];
    }
    
    if (tracker) {
        [tracker release];
    }
    
    if (mainDisplayView) {
        [mainDisplayView release];
    }
}


bool MouseInputDevice::initialize() {
    mainDisplayView = OpenGLContextManager::instance()->getFullscreenView();
    if (!mainDisplayView) {
        mainDisplayView = OpenGLContextManager::instance()->getMirrorView();
    }
    [mainDisplayView retain];
    
    tracker = [[MouseTracker alloc] init];
    
    trackingArea = [[NSTrackingArea alloc] initWithRect:[mainDisplayView bounds]
                                                options:(NSTrackingMouseEnteredAndExited |
                                                         NSTrackingMouseMoved |
                                                         NSTrackingActiveAlways)
                                                  owner:tracker
                                               userInfo:nil];
    
    [mainDisplayView addTrackingArea:trackingArea];
    
    return true;
}


END_NAMESPACE_MW


























