#pragma once

#include "ofMain.h"
#include "ofxOpenCv.h"
#include "ofxKinect.h"
#include "ofxGui.h"

#include "meshGenerator.h"
#include "processImage.h"
#include "gui.h"
#include "ofxXmlSettings.h"
#include "soundCalculations.h"


class lanscapes : public ofBaseApp{
    
public:
    void setup();
    void update();
    void draw();
    void keyPressed( int );
    void saveXML();
    
    
    ofVideoGrabber          vidGrabber;
    ofxKinect               kinect;
    
    ofxCvColorImage			colorImg;
    ofxCvGrayscaleImage 	grayImage;
    ofxCvGrayscaleImage     modifiedImage;
    ofxCvGrayscaleImage     kinectImage, croppedImg;
    int nearThreshold;
	int farThreshold;
    
    ofImage                 snapShot;
    ofxCvGrayscaleImage     background;
    unsigned char *         snapShotPix;
    
    bool                    fullscreen, bDrawVideo, bWireframe, bFaces, bColorWireframe;
    bool                    useKinect;
    
    float b,c,e,a;
    
    meshGenerator           mainMesh;
    processImage            processImage;
    soundCalculations       soundCalculations;
    gui                     gui;
    
    ofVec3f camDirectionRotated;
       
    ofEasyCam cam; // add mouse controls for camera movement
    
    
    int                     rotX, rotY, rotZ, transX, transY, transZ, width, height;
    float                   extrusionAmount;
    
    int                     previousHour, saveHour;
    
    ofxXmlSettings          XML;
    
    string                  message;
    int                     numSounds;
    ofSoundPlayer           *sound[ 6 ];
    vector <float>          volume;
    vector <float>          pan;
    vector <float>          speed;
    float                   soundUpSpeed, soundDownSpeed;
    int                     whichOne;
    
    ofFbo                  display;
    
    vector <ofRectangle>    rectangle;
};
