//
//  FMSynthesis.cpp
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//
#define DEBUG 0
#include <iostream>
#include "FMSynthesis.hpp"
FMSynthesis::FMSynthesis()
{
    for (int i = 0; i < MAX_SAMPLES; i++) {
        multiplierOutBuffer[i] = adderOutBuffer[i] =
        readerBuffer[i] = freqOscBuffer[i] = fmOscBuffer[i] = 0.0;
    }
    
    modulationTimesDelta.setLeftInput(fmOscBuffer);
    freqControl.setLeftInput(multiplierOutBuffer);
    
}

FMSynthesis::~FMSynthesis()
{
    
}

void FMSynthesis::setModulationFrequency(float mod)
{
#if DEBUG
    std::cout << "new mod: " << mod << std::endl;
#endif
    fmOsc.setFreq(mod);
}

void FMSynthesis::setOscFrequency(float freq)
{
    freqControl.setConstantRightVal(freq);
}

void FMSynthesis::setDeltaFactor(float delta)
{
#if DEBUG
    std::cout << "new delta: " << delta << std::endl;
#endif
    modulationTimesDelta.setConstantRightVal(delta);
}

void FMSynthesis::tick(float * fillBuffer, int numSamples, int channels)
{
    fillAllBuffers();
    for (int i = 0; i < numSamples; i++) {
        float val = freqOscBuffer[outputIndex];
        for(int j = 0; j < channels; j++){
            fillBuffer[i * channels + j] = val;
        }
        outputIndex = (outputIndex + 1) % MAX_SAMPLES;
    }
}

float FMSynthesis::tick()
{
    float val = freqOscBuffer[outputIndex];
    outputIndex = (outputIndex + 1) % MAX_SAMPLES;
    if (val > 1.0) val = 1.0;
    if (val < -1.0) val = -1.0;
    return val;
}



void FMSynthesis::fillAllBuffers()
{
    for(int i = 0; i < MAX_SAMPLES; i++){
        fmOscBuffer[fm_writeIndex] = fmOsc.tick();
        fm_writeIndex = (fm_writeIndex + 1) % MAX_SAMPLES;
    }
    
    modulationTimesDelta.tick(multiplierOutBuffer, MAX_SAMPLES);
    freqControl.tick(adderOutBuffer, MAX_SAMPLES);
    
    for(int i = 0; i < MAX_SAMPLES; i++){
        freqOsc.setFreq(adderOutBuffer[freqOsc_writeIndex]);
        freqOscBuffer[freqOsc_writeIndex] = freqOsc.tick();
        freqOsc_writeIndex = (freqOsc_writeIndex + 1) % MAX_SAMPLES;
    }
}