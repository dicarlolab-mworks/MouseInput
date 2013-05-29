//
//  MouseInputDevice.h
//  MouseInput
//
//  Created by Christopher Stawarz on 5/29/13.
//  Copyright (c) 2013 The MWorks Project. All rights reserved.
//

#ifndef __MouseInput__MouseInputDevice__
#define __MouseInput__MouseInputDevice__


BEGIN_NAMESPACE_MW


class MouseInputDevice : public IODevice, boost::noncopyable {
    
public:
    static const std::string MOUSE_POSITION_X;
    static const std::string MOUSE_POSITION_Y;
    
    static void describeComponent(ComponentInfo &info);
    
    explicit MouseInputDevice(const ParameterValueMap &parameters);
    ~MouseInputDevice();
    
private:
    VariablePtr posX;
    VariablePtr posY;
    
};


END_NAMESPACE_MW


#endif /* !defined(__MouseInput__MouseInputDevice__) */
