//
//  gui.h
//  LANscapes
//
//  Created by gabriella levine on 11/13/13.
//
//
#pragma once

#ifndef __LANscapes__gui__
#define __LANscapes__gui__

#include <iostream>
#include "ofMain.h"
#include "ofxGui.h"




class gui :  public ofBaseApp{

public:
    void setup();
    void draw();    
	bool hidden; //hide or show gui
    //set the initial gui parameters
    void setBrightness(float);
    void setContrast(float);
    void setExtrusion(float);
    void setAlphaValue(float);
    void setMovementThreshold(int);
    void setFlickerThreshold(int);
    void setRotX(int);
    void setxOffset(int);
    void setzOffset(int);
    void setyOffset(int);
    void setFarThreshold(int);
    void setUpSpeed( float );
    void setDownSpeed( float );
    void hide();
    void show();

    ofxPanel gui_panel;//initialize the gui panel
    
    //return parameters
    float getBrightness();
    float getContrast();
    float getExtrusion();
    float getAlpha();
    int getMovementThreshold();
    int getFlickerThreshold();
    int getX();
    int getyOffset();
    int getxOffset();
    int getzOffset();
    float getUpSpeed();
    float getDownSpeed();
    bool isWireOn();
    bool drawVideo();
    bool drawFaces();
    bool colorWireframe();
    
    //parameters
    ofParameter<float> brightness;
    ofParameter<float> contrast;
    ofParameter<float> alphaValue;
	ofParameter<float> extrusion;
    ofParameter<int> movementThreshold;
    ofParameter<int> flickerThreshold;
    ofParameter<int> rot_x;
    ofParameter<int> zOffset;
    ofParameter<int> xOffset;
    ofParameter<int> yOffset;
    ofParameter<int> farThreshold;
    ofParameter<float> soundUpSpeed;
    ofParameter<float> soundDownSpeed;
    
	ofxToggle wireframe;
    ofxToggle video;
    ofxToggle faces;
    ofxToggle bColorWireframe;
    ofxToggle mirrorH;
    ofxToggle mirrorV;
};
 

#endif /* defined(__LANscapes__gui__) */
