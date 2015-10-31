//
//  MathObject.h
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#ifndef MathObject_h
#define MathObject_h
#include "AudioSpec.h"

class MathObject{
protected:
    float * leftInputBuffer = nullptr;
    float * rightInputBuffer = nullptr;
    float constantLeftVal;
    float constantRightVal;
    unsigned int readIndex;
    
public:
    virtual ~MathObject() {};
    virtual void tick(float * fillBuffer, int numSamples) = 0;
    virtual void setLeftInput(float * input) {leftInputBuffer = input;}
    virtual void setRightInput(float * input) {rightInputBuffer = input;}
    virtual void setConstantLeftVal(float lVal) {constantLeftVal = lVal;}
    virtual void setConstantRightVal(float rVal) {constantRightVal = rVal;}
};

#endif /* MathObject_h */
