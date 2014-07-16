//
//  processImage.h
//
//
//  Created by curry on 11/2/13.
//
//

#ifndef processImage_h
#define processImage_h

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "soundCalculations.h"

class processImage : public ofBaseApp {
    
public:
    
    //methods
    void                setup( int, int, int, int, ofxCvGrayscaleImage, int, int, float, float );
    void                update(float, float, float, int, int, float, float);

    ofxCvGrayscaleImage getProcessedImage( ofxCvGrayscaleImage, ofxCvGrayscaleImage );

    
    //constructor
    processImage();
    
    //variables
    
    int                     imgWidth, imgHeight;
    int                     moveThreshLow, flickerThreshold;
    ofxCvGrayscaleImage     kinectSource;
    ofxCvGrayscaleImage     modifiedImage;
    ofxCvGrayscaleImage     backgroundImage;
    
    unsigned char *         sourcePixels;
    unsigned char *         modifiedPixels;
    unsigned char *         backgroundPixels;
    vector <int>            difference;
    
    float                   _brightness, _contrast, alphaAmount;
    soundCalculations       soundCalculations;
    
    vector <float> getVolume(); //pass along to main app
    vector <float> getPan();

    
private:
    
};


#endif
