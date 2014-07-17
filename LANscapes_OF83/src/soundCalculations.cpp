//
//  soundCalculations.cpp
//  
//
//  Created by curry on 6/12/14.
//
//

#include "soundCalculations.h"

void soundCalculations::setup( int w, int h, int which, int n, float u, float d ) {
    
    frameWidth = w;
    frameHeight = h;
    soundUpSpeed = u;
    soundDownSpeed = d;
    whichOne = which;
    
    numSounds = n;
    
    soundCenter.resize( numSounds );
    soundRadius.resize( numSounds );
    
    if ( whichOne == 1 ) {
        soundCenter[ 0 ].set( 140.0, 200.0 );
        soundCenter[ 1 ].set( 340.0, 600.0 );
        soundCenter[ 2 ].set( 540.0, 100.0 );

        soundRadius[ 0 ] = 550;
        soundRadius[ 1 ] = 406;
        soundRadius[ 2 ] = 456;
    }
    
    if ( whichOne == 2 ) {
        soundCenter[ 0 ].set( 500.0, 280.0 );
        soundCenter[ 1 ].set( 300.0, -120.0 );
        soundCenter[ 2 ].set( 100.0, 380.0 );
        
        soundRadius[ 0 ] = 583;
        soundRadius[ 1 ] = 406;
        soundRadius[ 2 ] = 356;
    }
    
    soundPan.resize( numSounds );
    soundVolume.resize( numSounds);
    distance.resize( numSounds );
    panDistance.resize( numSounds );
    
    for ( int i = 0; i < numSounds; i ++ ) {
        soundVolume[ i ] = 0.0;
    }
    
    soundPan[ 0 ] = -1.0;
    soundPan[ 1 ] = 0.0;
    soundPan[ 2 ] = 1.0;
    
}

void soundCalculations::calculateSound( int location ) { //if there is motion, increase the volume of sounds based on location of movement

    loc = location;
    float y = loc / 600;
    float x = loc - y * 600;
        
    for ( int i = 0; i < numSounds; i ++ ){
        distance[ i ] = ofDist( x, y, soundCenter[ i ].x, soundCenter[ i ].y );
        panDistance[ i ] = x - soundCenter[ i ].x;
        
        if ( distance[ i ] < soundRadius[ i ] && ofRandom( 0.0, 50.0 ) < 5 ) {
            soundVolume[ i ] += ( soundRadius[ i ] - distance[ i ] ) * soundUpSpeed;
            //cout << "soundVolume[ " << i << " ]: " << soundVolume[ i ]  << endl;
            
            if ( soundVolume[ i ] >= 0.8 ) {
                soundVolume[ i ] = 0.8;
            }
        }
        if ( panDistance[ i ] > 0.0 ) {
            soundPan[ i ] += .000001;
            if ( soundPan[ i ] >= 0.9 ) {
                soundPan [ i ] = 0.9;
                }
        }
        if ( panDistance[ i ] < 0.0 ) {
            soundPan[ i ] -= .000001;
            if ( soundPan[ i ] <= -0.90 ) {
                soundPan [ i ] = -0.90;
            }
        }
    }
}

void soundCalculations::update( float up, float down ) { //volume slowly returns to silence with stillness
    
    for ( int i = 0; i < numSounds; i ++ ){
        soundVolume[ i ] -= soundDownSpeed;
        if ( soundVolume[ i ] <= 0.0 ) {
            soundVolume[ i ] = 0.0;
        }
    }
    soundUpSpeed = up;
    soundDownSpeed = down;
}

void soundCalculations::draw( int x, int y, int w, int h ) {
    for ( int i = 0; i < numSounds; i ++ ) {
        float scalingFactor =  w /frameWidth;
    
        
        ofEnableAlphaBlending();
        ofSetColor( 255 - numSounds * 100,  255 - numSounds * 100, 255 - numSounds * 100, 50 );
        ofCircle( x + soundCenter[ numSounds ].x * scalingFactor , y + soundCenter[ numSounds ].y * scalingFactor, soundRadius[ numSounds ] * scalingFactor );
        ofDisableAlphaBlending();
    }
}

vector <float> soundCalculations::getVolume() {
    return soundVolume;
}

vector <float> soundCalculations::getPan() {
    return soundPan;
}



