//
//  Processing.h
//  Camera
//
//  Created by Simon Willi on 30/01/15.
//  Copyright (c) 2015 Simon Willi. All rights reserved.
//

#ifndef __Camera__Processing__
#define __Camera__Processing__

#import <UIKit/UIKit.h>
#include <inttypes.h>

@interface Processing : NSObject

+ (void) halftoneWithInput:(const uint8_t*)input  width:(int) width height:(int)heigth rowBytes:(int)rowBytes outputData:(uint8_t*)output;

@end

//
//
//// namespace would be nicer, but then we would need C++ style, which needs additional steps to make objective-c happy.
//
//
//
//void halftone(const uint8_t* input, int width, int height, int rowBytes, uint8_t* output);
//
#endif /* defined(__Camera__Processing__) */
