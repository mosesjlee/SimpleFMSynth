//
//  SineWrapper.h
//  SoundStuff
//
//  Created by Moses Lee on 10/30/15.
//  Copyright © 2015 Moses Lee. All rights reserved.
//

#ifndef SineWrapper_h
#define SineWrapper_h
#import <Foundation/Foundation.h>

@interface SineWrapper : NSObject

- (instancetype) init;
- (float) tick;
- (void) setFreq:(float) newFreq;
- (void) dealloc;


@end
#endif /* SineWrapper_h */
