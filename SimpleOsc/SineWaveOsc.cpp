//
//  SineWaveOsc.cpp
//  NewProject
//
//  Created by Moses Lee on 10/22/15.
//
//

#include "SineWaveOsc.h"

SineWaveOsc::SineWaveOsc()
{
    table = new float[MAX_SAMPLES];
    outBuffer = new float[MAX_SAMPLES];
    index = 0.0;
    freq = 440.0;
    setFreq(freq);
    
    for(int i = 0; i < MAX_SAMPLES;i++)
    {
        table[i] = sin(2 * M_PI * (float) i/MAX_SAMPLES);
        outBuffer[i] = 0.0;
    }
}


SineWaveOsc::~SineWaveOsc()
{
    delete [] table;
}


void SineWaveOsc::setFreq(float newFreq)
{
    freq = newFreq;
    delta_i = freq * MAX_SAMPLES/SR;
}

float SineWaveOsc::tick()
{
    float val = table[(int) index];
    
    //Increment by delta_i
    index += delta_i;
    
    //Out of bounds check
    if(index >= MAX_SAMPLES) index -= MAX_SAMPLES;
    if(index < 0) index += MAX_SAMPLES;
    
    return val;
}

void SineWaveOsc::tick(float * buffer, const int numSamples)
{
    for (int i = 0; i < numSamples; i++)
    {
        buffer[i] = table[(int) index];
        index += delta_i;
        
        //Out of bounds check
        if(index >= MAX_SAMPLES) index -= MAX_SAMPLES;
        if(index < 0) index += MAX_SAMPLES;
    }
}