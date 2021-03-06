//
//  ViewController.h
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "Novocaine.h"
#import "RingBuffer.h"
#import "AudioFileReader.h"
#import "AudioFileWriter.h"
#import "SineWrapper.h"
#import "FMSynthesis.hpp"
#import "ReadSamples.hpp"
#import "SimpleEq.hpp"

@interface ViewController : UIViewController

enum soundSource{
    monoGuitar,
    stereoGuitarSource,
    fmSynth,
    lowPass
};

@property (nonatomic, strong) Novocaine *audioManager;
@property (nonatomic, strong) AudioFileReader *fileReader;
@property (nonatomic, strong) AudioFileWriter *fileWriter;
@property (nonatomic, strong) SineWrapper * sineWave;
@property (nonatomic) SimpleEq * lowPassFilter;
@property (nonatomic) FMSynthesis * fmSynth;
@property (nonatomic) ReadSamples * guitarSound;
@property (nonatomic) ReadSamples * stereoGuitar;
@property (nonatomic) soundSource source;
@end

