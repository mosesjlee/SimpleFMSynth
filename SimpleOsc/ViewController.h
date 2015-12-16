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

@interface ViewController : UIViewController

@property (nonatomic, strong) Novocaine *audioManager;
@property (nonatomic, strong) AudioFileReader *fileReader;
@property (nonatomic, strong) AudioFileWriter *fileWriter;
@property (nonatomic, strong) SineWrapper * sineWave;
@property (nonatomic) FMSynthesis * fmSynth;
@property (nonatomic) ReadSamples * guitarSound;
@end

