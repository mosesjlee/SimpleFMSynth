//
//  ReadSamples.hpp
//  SimpleOsc
//
//  Created by Moses Lee on 12/15/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#ifndef ReadSamples_hpp
#define ReadSamples_hpp

#include <stdio.h>
#include <memory>
#include <iostream>
#include <fstream>
#include "AudioSpec.h"

#define BITS 8

using namespace std;

struct wavHeader {
    char  riff[4];
    int   size;
    char  type[4];
    char  chunk[4];
    int   length;
    short pcm;
    short numChannels;
    int   sampleRate;
    int   sR_BPM_Channels;
    short bPM_Channels;
    short bitsPerSample;
    char  data[4];
    int   sizeOfData;
};

class ReadSamples {
private:
    unique_ptr<char[]> header;
    unique_ptr<char[]> data;
    unique_ptr<float[]> samples;
    FILE * myFile;
    struct wavHeader wav;
    unsigned int frames;
    int outputIndex;
    
public:
    ReadSamples(string pathname);
    void fillSamples();
    void tick(float * buffer, int numFrames, int channels);
    
};

#endif /* ReadSamples_hpp */
