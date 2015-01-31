//
//  Processing.cpp
//  Camera
//
//  Created by Simon Willi on 30/01/15.
//  Copyright (c) 2015 Simon Willi. All rights reserved.
//

#import "Processing.h"

#include <string>
#include <vector>

//@interface Processing
//
//@end

@implementation Processing
// ..name space would be nicer!

+ (void) halftoneWithInput:(const uint8_t*)input  width:(int) width height:(int)heigth rowBytes:(int)rowBytes outputData:(uint8_t*)output;
{
    
    typedef std::vector<double> ColDouble;
    typedef std::vector<ColDouble> MatDouble;
    
    MatDouble eg(heigth);
    MatDouble ep(heigth);
    
    static const float C[2][3] = {{0.0, 0.2, 0.0}, {0.6, 0.1, 0.1}};
    
    int threshold = 250;
    
    for(int r =0; r< heigth; r++)
    {
        eg[r] = ColDouble(width, 0);
        ep[r] = ColDouble(width, 0);
    }
    
    for(int r =0; r< heigth; r++)
    {
        
        for(int c = 0; c < width; c++)
        {
//            int T = *input + E_g_m_n; // step 5
            double sum_p = 0;
            int xx,yy;
            for (int i  =0; i < 2; i++) {
                for (int j = 0; j<3; j++) {
                    
                    xx = std::min<int>(heigth-1,std::max<int>(0,r-i-1));
                    yy = std::min<int>(width-1, std::max<int>(0,c-j-1));
                    
                    sum_p += (C[i][j] * eg[xx][yy]);
                              
                }
            }
            
            ep[r][c] = sum_p;
            double T = ep[r][c] + input[r*width + c];
            
            if(T > threshold)
            {
                output[r*width +c] = 255;
                eg[r][c] = T - 2*threshold;
            }
            else{
                output[r*width +c] = 0;
                eg[r][c] = threshold;
                
                
            }
        }
    }
}

+ (void) ditheringFloydWidth:( uint8_t*)input  width:(int) width height:(int)heigth rowBytes:(int)rowBytes outputData:(uint8_t*)output;
{
    
    typedef std::vector<double> ColDouble;
    typedef std::vector<ColDouble> MatDouble;
    
    MatDouble eg(heigth);
    MatDouble ep(heigth);
    
    
    for(int r =0; r< heigth; r++)
    {
        eg[r] = ColDouble(width, 0);
        ep[r] = ColDouble(width, 0);
    }
    
    
    uint8_t * pixel = input;
    for(int r =0; r< heigth; r++)
    {
        int rowIndex = r*width;
        for(int c = 0; c < width; c++)
        {
            int diff = *pixel++  - 128;
            if(diff > 0) *output++ = 255;
            else *output++ = 0;
            
            if(c < width-1)input[rowIndex+c+1] += diff * 7.f/16.f;
            if(c > 0 && r < heigth - 1)input[rowIndex+c+width-1] += diff * 2.f/16.f;
            if(r < heigth - 1)input[rowIndex+c+width] += diff * 5.f/16.f;
            if(c < width-1 && r < heigth-1) input[rowIndex+c+width+1] += diff * 1.f/16.f;
        }
    }
}
@end
