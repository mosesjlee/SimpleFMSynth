//
//  MultiplierObject.cpp
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#define DEBUG 0

#if DEBUG
#include <iostream>
#endif

#include "MultiplierObject.hpp"

MultiplierObject::MultiplierObject()
{
    readIndex = 0;
}

MultiplierObject::MultiplierObject(float * leftInput, float * rightInput)
{
    readIndex = 0;
    leftInputBuffer = leftInput;
    rightInputBuffer = rightInput;
}

MultiplierObject::~MultiplierObject()
{
    
}

void MultiplierObject::tick(float *fillBuffer, int numSamples)
{
    float lVal, rVal;
    for (int i = 0; i < numSamples; i++) {
        
        
        //If any channel is null pass in 0.0 as sample
        lVal = leftInputBuffer == nullptr ? constantLeftVal : leftInputBuffer[readIndex];
        rVal = rightInputBuffer == nullptr ? constantRightVal : rightInputBuffer[readIndex];
        
        float outVal = lVal * rVal;
#if DEBUG
        std::cout << "mult lVal: " << lVal << " rVal: " << rVal << " outVal: " << outVal << std::endl;
#endif
        
        fillBuffer[i] = outVal;
        readIndex = (readIndex + 1) % MAX_SAMPLES;
    }
}