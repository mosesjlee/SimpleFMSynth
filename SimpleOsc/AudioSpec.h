//
//  AudioSpec.h
//  NewProject
//
//  Created by Moses Lee on 10/23/15.
//
//

#include <TargetConditionals.h>

#ifndef AudioSpec_h
#define AudioSpec_h
#define SR 44100

#if (TARGET_IPHONE_SIMULATOR)
#define MAX_SAMPLES 1024
#else
#define MAX_SAPMPLES 512
#endif


#endif /* AudioSpec_h */
