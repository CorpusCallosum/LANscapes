//
//  processImage.cpp
//
//
//  Created by curry on 11/2/13.
//
//

#include "processImage.h"

processImage::processImage()
{
    
    
}

void processImage::setup( int w, int h, int low, int flicker, ofxCvGrayscaleImage background, int which , int n, float u, float d) {
    
    imgWidth = w;
    imgHeight = h;
    moveThreshLow = low;
    flickerThreshold = flicker;
    kinectSource.allocate( imgWidth, imgHeight );
    kinectSource.set( 0.0 );//initialize all pixels black
    modifiedImage.allocate( imgWidth, imgHeight );
    modifiedImage = background;
    
    backgroundPixels = background.getPixels();
    difference.resize( imgWidth * imgHeight );
    
    
    soundCalculations.setup( w, h, which, n, u, d );
    
}

void processImage::update(float _b, float _c, float _a, int m, int t, float up, float down){
    _brightness = _b;
    _contrast = _c;
    alphaAmount = _a;
    moveThreshLow = m;
    flickerThreshold = t;
    
    soundCalculations.update( up, down );
   
    
}


ofxCvGrayscaleImage processImage::getProcessedImage( ofxCvGrayscaleImage img, ofxCvGrayscaleImage background ) {

    
    
    kinectSource = img;
    kinectSource.mirror( true, false ); // mirror( bool bFlipVertically, bool bFlipHorizontally )
    kinectSource.brightnessContrast( _brightness, _contrast );
    kinectSource.blurGaussian( 3 );
	kinectSource.dilate();
    sourcePixels = kinectSource.getPixels();
    
    modifiedPixels = modifiedImage.getPixels();
    
    background.mirror( true, false ); // mirror( bool bFlipVertically, bool bFlipHorizontally )
    background.brightnessContrast( _brightness, _contrast );
    background.blurGaussian( 3 );
    background.dilate();
    backgroundPixels = background.getPixels();

    float add;
    for ( int i = 0; i < imgWidth; i ++ ) {
        for ( int j = 0; j < imgHeight; j ++ ) {
            int loc = i + j * imgWidth;
            difference[ loc ] = sourcePixels[ loc ] - modifiedPixels[ loc ];
            if ( abs( sourcePixels[ loc ] - backgroundPixels[ loc ] ) > moveThreshLow && sourcePixels[ loc ] > flickerThreshold ) { //if the incoming pixel is different enough from the background image
                difference[ loc ] = sourcePixels[ loc ] - modifiedPixels[ loc ];
                soundCalculations.calculateSound( loc ); //if there is a difference at a location, send location to soundCalculations to increase volume
                
                if ( difference[ loc ] < 0 ) {
                    add = difference[ loc ] * 0.08;
                }
                else{
                    add = difference[ loc ] * alphaAmount;
                }
                float modifiedPixel = modifiedPixels[ loc ];
                if ( add + modifiedPixel > 255.0 )
                    modifiedPixels[ loc ] = 255;
                else if ( add + modifiedPixel < 0.0 )
                    modifiedPixels[ loc ] = 0;
                else
                    modifiedPixels[ loc ] += add;
            }
        }
    }
    
    
    modifiedImage.setFromPixels( modifiedPixels, imgWidth, imgHeight );
   
    return modifiedImage;
    
    
}

vector <float> processImage::getVolume() {
    return soundCalculations.getVolume();
}

vector <float> processImage::getPan() {
    return soundCalculations.getPan();
}


