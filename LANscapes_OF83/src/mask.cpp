//
//  mask.cpp
//  LANscapes_OF83
//
//  Created by curry on 7/16/14.
//
//

#include "mask.h"

void mask::setup( ofVec2f p0, ofVec2f p1, ofVec2f p2, ofVec2f p3 ){
    
    vertex[ 0 ].set( p0.x, p0.y );
    vertex[ 1 ].set( p1.x, p1.y );
    vertex[ 2 ].set( p2.x, p2.y );
    vertex[ 3 ].set( p3.x, p3.y );
    
}

void mask::update( ofVec2f dVert0, ofVec2f dVert1, ofVec2f dVert2, ofVec2f dVert3 ) {
    
    vertex[ 0 ].set( dVert0.x, dVert0.y );
    vertex[ 1 ].set( dVert1.x, dVert1.y );
    vertex[ 2 ].set( dVert2.x, dVert2.y );
    vertex[ 3 ].set( dVert3.x, dVert3.y );
    
}

void mask::draw() {
    
    ofSetColor( 0, 0, 0 );
    ofSetPolyMode(OF_POLY_WINDING_NONZERO);
	ofBeginShape();
    ofEnableAntiAliasing();
    for ( int i = 0; i < 4; i ++ ) {
        ofVertex( vertex[ i ].x, vertex[ i ].y );
    }
    ofDisableAntiAliasing();
	ofEndShape();
    
}