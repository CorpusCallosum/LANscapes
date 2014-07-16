//
//  currentColor.cpp
//  
//
//  Created by curry on 11/8/13.
//
//

#include "currentColor.h"

//--------------------------------------------------------------
void currentColor::setup( int w, int h ) {
    
    width = w;
    height = h;
    
    //color timers
    startTime = ofGetSystemTime();
    currentTime = startTime;
    lastTime = 0;
    colorTime = 0;
    colorDuration = 1000 * 20; //how long each color lasts in ms
    
    colorPalette.resize( 6 );
    
    //AWESOME/BORING
    colorPalette[ 0 ] = ofColor( 237, 237, 237 ); //79, 211, 73 ); // 101, 252, 99 ); //wite
    colorPalette[ 1 ] = ofColor( 186, 255, 74 );   // 200, 23, 178 );   //
    colorPalette[ 2 ] = ofColor( 28, 255, 238 ); //14, 229, 184 ); //21, 70, 228 );   //ice blue green
    colorPalette[ 3 ] = ofColor( 40, 45, 250 ); //64, 52, 95 );    //blue
    colorPalette[ 4 ] = ofColor( 255, 74, 213 ); // 203, 103, 10 );  //magenta
    colorPalette[ 5 ] = ofColor( 0, 0, 0 );//52, 11, 64 );   // 200, 23, 178 );   //

    //RAINBOW
    /*colorPalette[ 0 ] = ofColor( 101, 252, 99 ); //green
    colorPalette[ 1 ] = ofColor( 21, 70, 228 );   //ice blue green
    colorPalette[ 2 ] = ofColor( 64, 52, 95 );    //blue
    colorPalette[ 3 ] = ofColor( 203, 103, 10 );  //magenta
    colorPalette[ 4 ] = ofColor( 200, 23, 178 );   //
     */


    
    lastColor = 0;
    nextColor = 1;
    cycles = 1;
    
    currentColor = colorPalette[ lastColor ];
    fromColor = colorPalette[ lastColor ];
    toColor = colorPalette[ nextColor ];
    
    colorGrid.resize( width * height );
    meshImage.allocate( width, height );
    lastMeshImage.allocate( width, height );
    
    for ( int i = 0; i < width * height; i ++ ) {
        colorGrid[ i ] = colorPalette[ 0 ];
    }

}

//--------------------------------------------------------------
//I think this returns a vector of colors that is the current vector of
//colors of the entire mesh
vector<ofColor> currentColor::getCurrentColor( ofxCvGrayscaleImage img) {
    
    meshImage = img;
    
    transSpeed = (float) colorTime / colorDuration;
    currentColor = fromColor.getLerped( toColor, transSpeed );
    
    currentTime = ofGetSystemTime() - startTime;//how long the sketch has been running in m
    
    if ( colorTime >= colorDuration ) {
        cycles ++;
        lastColor = nextColor;
        nextColor ++;
        if ( nextColor > colorPalette.size() - 1 ) {
            nextColor = 0;
        }
        fromColor = colorPalette[ lastColor ];
        toColor = colorPalette[ nextColor ];
    }
    if ( cycles > 1 ) {
        colorTime = currentTime - ((cycles - 1 ) * colorDuration );
    }
    else {
        colorTime = currentTime;
    }
    
    unsigned char * meshPix = meshImage.getPixels();
    unsigned char * lastPix = lastMeshImage.getPixels();
    for ( int i = 0; i < width * height; i ++ ) {
        if ( abs( meshPix[ i ] - lastPix[ i ] ) > 0 ) {
            colorGrid [ i ] = currentColor;
        }
    }
    
    lastMeshImage = meshImage;
    
    return colorGrid;
    
}