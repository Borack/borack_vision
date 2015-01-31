//
//  Processing.cpp
//  Camera
//
//  Created by Simon Willi on 30/01/15.
//  Copyright (c) 2015 Simon Willi. All rights reserved.
//

#import "Processing.h"

#include <string>

//@interface Processing
//
//@end

@implementation Processing
// ..name space would be nicer!

+ (void) halftoneWithInput:(const uint8_t*)input  width:(int) width height:(int)heigth rowBytes:(int)rowBytes outputData:(uint8_t*)output;
{
    
    std::memcpy(output, input, rowBytes*heigth);
}

@end
