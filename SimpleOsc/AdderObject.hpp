//
//  AdderObject.hpp
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#ifndef AdderObject_hpp
#define AdderObject_hpp

#include <stdio.h>
#include "MathObject.h"

class AdderObject : public MathObject
{
public:
    AdderObject();
    AdderObject(float * leftInput, float * rightInput);
    ~AdderObject();
    void tick(float * fillBuffer, int numSamples);
};

#endif /* AdderObject_hpp */
