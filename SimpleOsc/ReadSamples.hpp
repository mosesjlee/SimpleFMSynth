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
#include <string>
#include "AudioSpec.h"

#define BITS 8
#define DEFAULT_DATA_LOC 44
#define DESCRIPTOR_OFFSET 8

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
    
    //For Pro Tools generated wav
    string minf = "minf" ;
    int minfOffSet = 0;
    string elm1 = "elm1";
    int elm1OffSet = 0;
    string regn = "regn";
    int regnOffSet = 0;
    string umid = "umid";
    int umidOffSet = 0;
    string bext = "bext";
    int bextOffSet = 0;
    string pad = "PAD";
    int padOffSet = 0;
    int finalOffset = 0;
    bool hasAdditionalHeaderInf = false;
    
public:
    ReadSamples(string pathname);
    void fillSamples();
    void tick(float * buffer, int numFrames, int channels);
    
};

#endif /* ReadSamples_hpp */
