//
//  currentColor.h
//  
//
//  Created by curry on 11/8/13.
//
//

#ifndef currentColor_h
#define currentColor_h


#include "ofMain.h"
#include "ofxOpenCv.h"


class currentColor : public ofBaseApp{
	
public:
    
    //methods
	void setup( int, int );
    vector<ofColor> getCurrentColor( ofxCvGrayscaleImage );
    
	//variables
    vector<ofColor> colorPalette;
    vector<ofColor> colorGrid;
    
    ofxCvGrayscaleImage meshImage, lastMeshImage;
    
    ofColor fromColor;
    ofColor toColor;
    ofColor currentColor;
    int nextColor;
    int lastColor;

    float transSpeed; // moves 0 - 1 to transition fromColor toColor
    
    //color timers
    long startTime;
    long currentTime;
    long lastTime;
    long colorTime;
    int colorDuration; //how long each color lasts in ms
    int cycles;
    
    int width, height;
    
	
	
};


#endif
