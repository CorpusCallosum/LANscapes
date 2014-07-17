//
//  meshGenerator.h
//  
//
//  Created by curry on 11/7/13.
//
//

#ifndef meshGenerator_h
#define meshGenerator_h

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "currentColor.h"

class meshGenerator : public ofBaseApp{
	
public:
    
    //methods
	void setup( int, int, float, bool, bool );
    ofVboMesh update( ofxCvGrayscaleImage , float, bool);
	void draw( bool, bool );
    void save();

    
	//variables
    ofxCvGrayscaleImage meshImage;
    
	float extrusionAmount;
	ofVboMesh mainMesh, wireframeMesh;
    bool    bDrawWireframe, bDrawFaces, bColorWireframe;
    int width, height, xOffset, zOffset, yOffset, wireframeBrightness, wireframeSaturation;
    
    vector<ofColor> colorGrid;
    
    currentColor    currentColor;
    
    ofImage noiseImage;
    
    int minNoise;
    
	
};




#endif
