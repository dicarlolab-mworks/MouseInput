//
//  MouseInputDevice.h
//  MouseInput
//
//  Created by Christopher Stawarz on 5/29/13.
//  Copyright (c) 2013 The MWorks Project. All rights reserved.
//

#ifndef __MouseInput__MouseInputDevice__
#define __MouseInput__MouseInputDevice__

#import "MouseTracker.h"


BEGIN_NAMESPACE_MW


class MouseInputDevice : public IODevice, boost::noncopyable {
    
public:
    static const std::string MOUSE_POSITION_X;
    static const std::string MOUSE_POSITION_Y;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit MouseInputDevice(const ParameterValueMap &parameters);
    ~MouseInputDevice();
    
    bool initialize() MW_OVERRIDE;
    
private:
    VariablePtr posX;
    VariablePtr posY;
    
    NSOpenGLView *mainDisplayView;
    MouseTracker *tracker;
    NSTrackingArea *trackingArea;
    
};


END_NAMESPACE_MW


#endif /* !defined(__MouseInput__MouseInputDevice__) */


























