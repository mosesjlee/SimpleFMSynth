//
//  SineWrapper.m
//  SoundStuff
//
//  Created by Moses Lee on 10/30/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//
#import "SineWrapper.h"
#import "SineWaveOsc.h"

@interface SineWrapper ()

@property(nonatomic, readonly) SineWaveOsc * sineWave;


@end

@implementation SineWrapper

- (instancetype) init
{
    self = [super init];
    if (self != nil)
    	_sineWave = new SineWaveOsc();
    return self;
}

- (float) tick
{
    return _sineWave->tick();
}

- (void) setFreq:(float) newFreq
{
    _sineWave->setFreq(newFreq);
}

- (void) dealloc
{
    delete _sineWave;
}

@end