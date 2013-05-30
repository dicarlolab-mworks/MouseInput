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
    {
        boost::shared_ptr<StimulusDisplay> display = StimulusDisplay::getCurrentStimulusDisplay();
        OpenGLContextLock ctxLock = display->setCurrent(0);
        
        // Get the parameters needed by gluUnProject
        glGetDoublev(GL_MODELVIEW_MATRIX, modelViewMatrix.data());
        glGetDoublev(GL_PROJECTION_MATRIX, projectionMatrix.data());
        glGetIntegerv(GL_VIEWPORT, viewport.data());
    }
    
    mainDisplayView = OpenGLContextManager::instance()->getFullscreenView();
    if (!mainDisplayView) {
        mainDisplayView = OpenGLContextManager::instance()->getMirrorView();
    }
    [mainDisplayView retain];
    
    tracker = [[MWKMouseTracker alloc] initWithMouseInputDevice:component_shared_from_this<MouseInputDevice>()];
    
    trackingArea = [[NSTrackingArea alloc] initWithRect:[mainDisplayView bounds]
                                                options:(NSTrackingMouseEnteredAndExited |
                                                         NSTrackingMouseMoved |
                                                         NSTrackingActiveAlways)
                                                  owner:tracker
                                               userInfo:nil];
    
    [mainDisplayView addTrackingArea:trackingArea];
    
    return true;
}


void MouseInputDevice::postMouseLocation(NSPoint location) const {
    NSPoint locationInPixels = [mainDisplayView convertPointToBacking:location];
    GLdouble mouseX, mouseY, mouseZ;
    
    if (GLU_TRUE != gluUnProject(locationInPixels.x, locationInPixels.y, 0.0,
                                 modelViewMatrix.data(),
                                 projectionMatrix.data(),
                                 viewport.data(),
                                 &mouseX, &mouseY, &mouseZ))
    {
        merror(M_DISPLAY_MESSAGE_DOMAIN, "Unable to convert mouse location from window to eye coordinates");
    } else {
        MWTime time = Clock::instance()->getCurrentTimeUS();
        posX->setValue(mouseX, time);
        posY->setValue(mouseY, time);
    }
}


END_NAMESPACE_MW


























