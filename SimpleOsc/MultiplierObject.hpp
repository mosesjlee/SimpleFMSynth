//
//  MultiplierObject.hpp
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#ifndef MultiplierObject_hpp
#define MultiplierObject_hpp

#include "MathObject.h"

class MultiplierObject : public MathObject
{
public:
    MultiplierObject();
    MultiplierObject(float * leftInput, float * rightInput);
    ~MultiplierObject();
    void tick(float * fillBuffer, int numSamples);
};

#endif /* MultiplierObject_hpp */
