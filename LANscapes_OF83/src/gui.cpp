//
//  gui.cpp
//  LANscapes
//
//  Created by gabriella levine on 11/13/13.
//
//

//--------------------------------------------------------------


#include "gui.h"

void gui::setup(){
    ofSetVerticalSync(true);
    
    gui_panel.setup();
    
    gui_panel.add(brightness.set("brightness", 0.3, -1, 1));
    gui_panel.add(contrast.set("contrast", 0.2 , -1, 1));
    gui_panel.add(extrusion.set("extrusion", 65, 0, 500));
    gui_panel.add(alphaValue.set("alphaValue", 0.05, 0.01, 0.1));
    gui_panel.add(movementThreshold.set("movementThreshold", 10, 0, 100 ));
    gui_panel.add(flickerThreshold.set("flickerThreshold", 10, 0, 100 ));
    gui_panel.add(farThreshold.set("far_threshold", 100, 0, 255 ));
    
    gui_panel.add(rot_x.set("rot_x", -20,-360,360));
    gui_panel.add(xOffset.set("xOffset", -20, -100,100));
    gui_panel.add(yOffset.set("yOffset", -20, -100,100));
    gui_panel.add(zOffset.set("zOffset", -20, -100,100));
    gui_panel.add(wireframe.setup("wireframe", true));
    gui_panel.add(faces.setup("faces", true));
    gui_panel.add(video.setup("video", false));
    gui_panel.add(bColorWireframe.setup("colored wireframe", false));
    gui_panel.add(mirrorH.setup("mirror horizontally", false));
    gui_panel.add(mirrorV.setup("mirror vertically", false));
    gui_panel.add(soundUpSpeed.set("soundUpSpeed", .0000001, .00000000001, .00001));
    gui_panel.add(soundDownSpeed.set("soundDownSpeed", .001, .0001, .01));
    
    hidden = true;
    ofHideCursor();
}

//set the parameters
void gui::setBrightness(float b){
    brightness.set(b);
}
void gui::setContrast(float c){
    contrast.set(c);
}
void gui::setExtrusion(float e){
    extrusion.set(e);
}
void gui::setAlphaValue(float a){
    alphaValue.set(a);
}
void gui::setMovementThreshold(int m){
    movementThreshold.set(m);
}
void gui::setFlickerThreshold(int f){
    flickerThreshold.set(f);
}
void gui::setFarThreshold(int f){
    farThreshold.set(f);
}
void gui::setRotX(int r){
    rot_x.set(r);
}
void gui::setzOffset(int z){
    zOffset.set(z);
}
void gui::setxOffset(int x){
    xOffset.set(x);
}
void gui::setyOffset(int y){
    yOffset.set(y);
}
void gui::setUpSpeed( float u ) {
    soundUpSpeed.set( u );
}
void gui::setDownSpeed( float d ) {
    soundDownSpeed.set( d );
}


//
void gui::draw(){
    if(!hidden){
        gui_panel.draw();
        //draw framerate for fun
        ofSetColor(255);
        string msg = "fps: " + ofToString(ofGetFrameRate(), 2);
        ofDrawBitmapString(msg, 10, 20);
    }
}

void gui::show(){
    ofShowCursor();
    hidden = false;
}

void gui::hide(){
    ofHideCursor();
    hidden = true;
}

float gui::getBrightness(){
    return brightness;
    
}

float gui::getExtrusion(){
    return extrusion;
    
}

float gui::getContrast(){
    return contrast;
    
}
float gui::getAlpha(){
    return alphaValue;
    
}

int gui::getMovementThreshold() {
    return movementThreshold;
}
int gui::getFlickerThreshold() {
    return flickerThreshold;
}

int gui::getX(){
    return rot_x;
}

int gui::getyOffset(){
    return yOffset;
}
int gui::getzOffset(){
    return zOffset;
}
int gui::getxOffset(){
    return xOffset;
}

bool gui::isWireOn(){
    return wireframe;
}

bool gui::drawVideo(){
    return video;
}

bool gui::drawFaces(){
    return faces;
    
}
bool gui::colorWireframe() {
    return bColorWireframe;
}

float gui::getUpSpeed() {
    return soundUpSpeed;
}

float gui::getDownSpeed() {
    return soundDownSpeed;
}