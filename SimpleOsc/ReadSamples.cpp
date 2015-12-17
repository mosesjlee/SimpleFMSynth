//
//  ReadSamples.cpp
//  SimpleOsc
//
//  Created by Moses Lee on 12/15/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#include "ReadSamples.hpp"

ReadSamples::ReadSamples(string pathname){
    myFile = fopen(pathname.c_str(), "r");
    header.reset(new char[44]);
    outputIndex = 0;
    
    if(myFile != NULL){
        fread((void *)header.get(), sizeof(char), 44, myFile);
        
        memcpy(&wav.riff, &header[0], 4);
        memcpy(&wav.size, &header[4], 4);
        memcpy(&wav.type, &header[8], 4);
        memcpy(&wav.chunk, &header[12], 4);
        memcpy(&wav.length, &header[16], 4);
        memcpy(&wav.pcm, &header[20], 2);
        memcpy(&wav.numChannels, &header[22], 2);
        memcpy(&wav.sampleRate, &header[24], 4);
        memcpy(&wav.sR_BPM_Channels, &header[28], 4);
        memcpy(&wav.bPM_Channels, &header[32], 2);
        memcpy(&wav.bitsPerSample, &header[34], 2);
        memcpy(&wav.data, &header[36], 4);
        memcpy(&wav.sizeOfData, &header[40], 4);
        
        frames = wav.sizeOfData * BITS/ wav.bitsPerSample;
    } else {
        cout << "Could not open" << endl;
    }
}

void ReadSamples::fillSamples(){
    samples.reset(new float[frames]);
    data.reset(new char[wav.sizeOfData]);
    
    if(!fseek(myFile, 44, SEEK_SET)){
        cout << "Size of float: " << sizeof(float) << endl;
        fread((void *) data.get(), sizeof(char), wav.sizeOfData, myFile);
        
        short s = 0x0000, fs, ss;
        for(int i = 0; i < frames; i++){
            
            
            ss = ((0x0000 | data[i*2+1]) & 0xff) << 8;
            fs = (0x0000 | data[i*2]) & 0xff;
            s = fs | ss;
            
            //First attempt was just use memcpy
            //memcpy(&s, &data[i*2], 2);
            samples[i] = (float) s/32768.0000;
            
            //cout << samples[i] << endl;
        }
        
    }
    
}

void ReadSamples::tick(float * buffer, int numFrames, int channels){
    for (int i = 0; i < numFrames; i++) {
        float val = samples[outputIndex];
        for(int j = 0; j < channels; j++){
            buffer[i * channels + j] = val;
        }
        outputIndex = (outputIndex + 1) % frames;
    }
}

