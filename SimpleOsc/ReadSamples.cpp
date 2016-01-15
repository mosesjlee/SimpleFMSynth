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
        
        //cout << "what is data: " << wav.data << endl;
        //cout << "minfOffSet: " << minfOffSet << endl;
        if(memcmp(wav.data, minf.data(), 4) == 0){
            minfOffSet = wav.sizeOfData;
            fseek(myFile, DEFAULT_DATA_LOC + minfOffSet, SEEK_SET);
            fread((void *) wav.data, sizeof(char), 4, myFile);
            fread((void *) &wav.sizeOfData, sizeof(int), 1, myFile);
            elm1OffSet = wav.sizeOfData;
            cout << "elm1OffSet: " << elm1OffSet << endl;
            cout << "what is data: " << wav.data << endl;
        }
        
        if(memcmp(wav.data, elm1.data(), 4) == 0){
            hasAdditionalHeaderInf = true;
            cout << "Detected elm1" << endl;
            fseek(myFile, DESCRIPTOR_OFFSET + DEFAULT_DATA_LOC + minfOffSet + elm1OffSet, SEEK_SET);
            fread((void *) wav.data, sizeof(char), 4, myFile);
            fread((void *) &wav.sizeOfData, sizeof(int), 1, myFile);
            regnOffSet = wav.sizeOfData;
            cout << "regnOffSet: " << regnOffSet << endl;
        }
        
        if(memcmp(wav.data, regn.data(), 4) == 0) {
            cout << "Detected region" << endl;
            fseek(myFile, (2 * DESCRIPTOR_OFFSET) + DEFAULT_DATA_LOC + minfOffSet + elm1OffSet + regnOffSet, SEEK_SET);
            fread((void *) wav.data, sizeof(char), 4, myFile);
            fread((void *) &wav.sizeOfData, sizeof(int), 1, myFile);
            umidOffSet = wav.sizeOfData;
            cout << "umidOffSet: " << umidOffSet << endl;
            
        }
        if(memcmp(wav.data, umid.data(), 4) == 0) {
            cout << "Detected region" << endl;
            fseek(myFile, (3 * DESCRIPTOR_OFFSET) + DEFAULT_DATA_LOC + minfOffSet + elm1OffSet + regnOffSet + umidOffSet, SEEK_SET);
            fread((void *) wav.data, sizeof(char), 4, myFile);
            fread((void *) &wav.sizeOfData, sizeof(int), 1, myFile);
            bextOffSet = wav.sizeOfData;
            cout << "bextOffSet: " << bextOffSet << endl;
        }
        if(memcmp(wav.data, bext.data(), 4) == 0) {
            cout << "Detected region" << endl;
            fseek(myFile,
                  (4 * DESCRIPTOR_OFFSET) + DEFAULT_DATA_LOC + minfOffSet + elm1OffSet + regnOffSet + umidOffSet + bextOffSet, SEEK_SET);
            fread((void *) wav.data, sizeof(char), 4, myFile);
            fread((void *) &wav.sizeOfData, sizeof(int), 1, myFile);
            padOffSet = wav.sizeOfData;
            cout << "padOffSet: " << padOffSet << endl;
        }
        
        finalOffset = (5 * DESCRIPTOR_OFFSET) + DEFAULT_DATA_LOC +
        minfOffSet + elm1OffSet + regnOffSet + umidOffSet + bextOffSet + padOffSet;
        
        if(memcmp(wav.data, pad.data(), 3) == 0) {
            cout << "Detected region" << endl;
            fseek(myFile, finalOffset, SEEK_SET);
            fread((void *) wav.data, sizeof(char), 4, myFile);
            fread((void *) &wav.sizeOfData, sizeof(int), 1, myFile);
        }

        if(hasAdditionalHeaderInf) {
            finalOffset =	(5 * DESCRIPTOR_OFFSET) + DEFAULT_DATA_LOC +
            minfOffSet + elm1OffSet + regnOffSet + umidOffSet + bextOffSet + padOffSet;
        }
        
        frames = wav.sizeOfData * BITS/ wav.bitsPerSample;
        //cout << "file name: " << pathname << " with sizeOfdata: " << wav.sizeOfData << " finaOffset: " << finalOffset << endl;
        cout << "data: " << wav.data << endl;
    } else {
        cout << "Could not open" << endl;
    }
}

void ReadSamples::fillSamples(){
    samples.reset(new float[frames]);
    data.reset(new char[wav.sizeOfData]);
    
    unsigned int seek_size = hasAdditionalHeaderInf ? finalOffset : DEFAULT_DATA_LOC;

    
    if(!fseek(myFile, seek_size + 8, SEEK_SET)){
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
    if (wav.numChannels == 1) {
        for (int i = 0; i < numFrames; i++) {
            float val = samples[outputIndex];
            //just output it to the left one
            for(int j = 0; j < 1; j++){
                buffer[i * channels + j] = val;
            }
            outputIndex = (outputIndex + 1) % frames;
        }
    } else if (wav.numChannels == 2){
        
        for (int i = 0; i < numFrames; i++) {
            for(int j = 0; j < channels; j++){
                float val = samples[outputIndex];
                buffer[i * channels + j] = val;
                outputIndex = (outputIndex + 1) % frames;
                //cout << "output index:" << outputIndex << endl;
            }
        }
    }
}

