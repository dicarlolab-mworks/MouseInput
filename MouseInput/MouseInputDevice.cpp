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
    posY(parameters[MOUSE_POSITION_Y])
{
}


MouseInputDevice::~MouseInputDevice() {
}


END_NAMESPACE_MW
