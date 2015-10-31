//
//  FMSynthesis.hpp
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#ifndef FMSynthesis_hpp
#define FMSynthesis_hpp

#include "SineWaveOsc.h"
#include "AdderObject.hpp"
#include "MultiplierObject.hpp"

class FMSynthesis {
private:
    SineWaveOsc fmOsc;
    SineWaveOsc freqOsc;
    MultiplierObject modulationTimesDelta;
    AdderObject freqControl;
    int fm_writeIndex = 0;
    int freqOsc_writeIndex = 0;
    int outputIndex = 0;
    float fmOscBuffer[MAX_SAMPLES];
    float freqOscBuffer[MAX_SAMPLES];
    float multiplierOutBuffer[MAX_SAMPLES];
    float adderOutBuffer[MAX_SAMPLES];
    float readerBuffer[MAX_SAMPLES];
    
public:
    FMSynthesis();
    ~FMSynthesis();
    void setModulationFrequency(float mod);
    void setOscFrequency(float freq);
    void setDeltaFactor(float delta);
    void tick(float * fillBuffer, int numSamples, int channels);
    float tick();
    void fillAllBuffers();
};

#endif /* FMSynthesis_hpp */
