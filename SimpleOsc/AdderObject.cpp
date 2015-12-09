//
//  AdderObject.cpp
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#include "AdderObject.hpp"

AdderObject::AdderObject()
{
    readIndex = 0;
}

AdderObject::AdderObject(float * leftInput, float * rightInput)
{
    readIndex = 0;
    leftInputBuffer = leftInput;
    rightInputBuffer = rightInput;
}

AdderObject::~AdderObject()
{
}

void AdderObject::tick(float *fillBuffer, int numSamples)
{
    float lVal, rVal;
    for (int i = 0; i < numSamples; i++) {
        
    
    	//If any channel is null pass in 0.0 as sample
        lVal = leftInputBuffer == nullptr ? constantLeftVal : leftInputBuffer[readIndex];
        rVal = rightInputBuffer == nullptr ? constantRightVal : rightInputBuffer[readIndex];
        
        float outVal = lVal + rVal;
        
        fillBuffer[i] = outVal;
        readIndex = (readIndex + 1) % MAX_SAMPLES;
	}
}