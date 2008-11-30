//
//  DTMFDecoder.h
//  dtmfdecode
//
//  Created by Veghead on 14/11/2008.
//  Copyright 2008 __MyCompanyName__. All rights reserved.
//

#import <UIKit/UIKit.h>
#import <AudioToolbox/AudioQueue.h>
#import <AudioToolbox/AudioFile.h>

#define SAMPLING_RATE       8000
#define MAX_BINS            8
#define GOERTZEL_N          100
#define DETECTBUFFERLEN		8192

/*
 * coef = 2.0 * cos( (2.0 * PI * k) / (float)GOERTZEL_N)) ;
 * Where k = (int) (0.5 + ((float)GOERTZEL_N * target_freq) / SAMPLING_RATE));
 * 
 * More simply: coef = 2.0 * cos( (2.0 * PI * target_freq) / SAMPLING_RATE );
 */

@interface DTMFDecoder : NSObject {	
	AudioStreamBasicDescription audioFormat;
	int         sample_count;
	double      q1[ MAX_BINS ];
	double      q2[ MAX_BINS ];
	double      r[ MAX_BINS ];
	double      coefs[ MAX_BINS ] ;
	double		*currentFreqs;
	char		last;
	char		*detectBuffer;
	bool		running;
}

@property (assign) double *currentFreqs;
@property (assign) char *detectBuffer;
@property (readwrite) bool running;

- (id) init;
- (void) calc_coeffs;
- (bool) goertzel:(short)sample;
- (void) setDTMF:(int)freqset;
- (void) resetBuffer;
- (bool) post_testing;
@end