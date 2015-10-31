//
//  SineWaveOsc.hpp
//  NewProject
//
//  Created by Moses Lee on 10/22/15.
//
//

#ifndef SineWaveOsc_h
#define SineWaveOsc_h
#include <math.h>
#include "AudioSpec.h"

class SineWaveOsc{
public:
    SineWaveOsc();
    ~SineWaveOsc();
    void setFreq(float freq);
    float tick();
    void tick(float * buffer, const int numSamples);
    
private:
    float * table;
    float * outBuffer;
    float initialPhase;
    float delta_i;
    float index;
    float freq;
};

#endif /* SineWaveOsc_hpp */
