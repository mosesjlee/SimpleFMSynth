//
//  ViewController.m
//  SimpleOsc
//
//  Created by Moses Lee on 10/31/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#import "ViewController.h"

@interface ViewController ()
@property (strong, nonatomic) IBOutlet UILabel *freqLabel;
@property (strong, nonatomic) IBOutlet UISlider *freqSlider;
@property (strong, nonatomic) IBOutlet UIButton *playButton;
@property (strong, nonatomic) IBOutlet UISlider *modulationSlider;
@property (strong, nonatomic) IBOutlet UISlider *deltaFreqSlider;
@property (weak, nonatomic) IBOutlet UISwitch *guitarOrSynthSwitch;
@property (weak, nonatomic) IBOutlet UISegmentedControl *soundMode;
@property bool play;
@property bool guitar;

@property (nonatomic, assign) RingBuffer * ringBuffer;

@end

@implementation ViewController

- (void)viewDidLoad {
    _play = NO;
    _guitar = NO;
    [super viewDidLoad];
    // Do any additional setup after loading the view, typically from a nib.
    _sineWave = [[SineWrapper alloc] init];
    _fmSynth = new FMSynthesis();
    
    NSString * path = [[NSBundle mainBundle] pathForResource:  @"guitar1" ofType: @"wav"];
    _guitarSound = new ReadSamples([path cStringUsingEncoding:1]);
    _guitarSound->fillSamples();
    
    NSString * path2 = [[NSBundle mainBundle] pathForResource:  @"stereo_guitar" ofType: @"wav"];
    _stereoGuitar = new ReadSamples([path2 cStringUsingEncoding:1]);
    _stereoGuitar->fillSamples();
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}

- (void)viewWillAppear:(BOOL)animated
{
    [super viewWillAppear:animated];
    
    self.audioManager = [Novocaine audioManager];
    self.ringBuffer = new RingBuffer(4096,1);
    
        [self.audioManager setOutputBlock:^(float *data, UInt32 numFrames, UInt32 numChannels)
         {
//             _fmSynth->fillAllBuffers();
    		
//            for (int i=0; i < numFrames; ++i)
//            {
//                float val = _fmSynth->tick();
//                for (int iChannel = 0; iChannel < numChannels; ++iChannel)
//                {
//                    data[i*numChannels + iChannel] = val;
//                }
//            }
//           //Need to figure out for stereo
             //NSLog(@"numframes: %d", numFrames);
//             if (_guitar) {
//                 
//                 _guitarSound->tick(data, numFrames, numChannels);
//             } else {
//                 _fmSynth->tick(data, numFrames, numChannels);
//             }
             switch (_source) {
                 case fmSynth:
                     _fmSynth->tick(data, numFrames, numChannels);
                     break;
                 case monoGuitar:
                     _guitarSound->tick(data, numFrames, numChannels);
                     break;
                 case stereoGuitarSource:
                     _stereoGuitar->tick(data, numFrames, numChannels);
                 default:
                     break;
             }
         }];
}

- (void)viewDidDisappear:(BOOL)animated{
    
}


- (IBAction)changeFreq:(id)sender {
    _fmSynth->setOscFrequency(_freqSlider.value);
    _freqLabel.text = [NSString stringWithFormat:@"%.2f", _freqSlider.value];
}

- (IBAction)changeModFreq:(id)sender {
    _fmSynth->setModulationFrequency(_modulationSlider.value);
    //NSLog(@"%f", _modulationSlider.value);
}

- (IBAction)changeDeltaFreq:(id)sender {
    _fmSynth->setDeltaFactor(_deltaFreqSlider.value);
    //NSLog(@"%f", _deltaFreqSlider.value);
}

- (IBAction)playSomeNoise:(id)sender {
    _play = !_play;
    _play ? [_audioManager pause] : [_audioManager play];
    NSLog(@"Play button value of play: %@", _play ? @"YES" : @"NO" );
}

- (IBAction)switchDifferentModes:(id)sender {
    //[soundMode ];
    NSInteger mode = [_soundMode selectedSegmentIndex];
    NSLog(@"Mode value: %ld", (long)mode);
    switch (mode) {
        case 0:
            _source = fmSynth;
            break;
        case 1:
            _source = monoGuitar;
            break;
        case 2:
            _source = stereoGuitarSource;
            break;
        default:
            _source = fmSynth;
            break;
    }
}


@end
