#include "ofApp.h"
#include "ofMain.h"
#include "ofAppGlutWindow.h"
#include "ofxWatchdog.h"


//========================================================================
int main( ){
    
    // ofxWatchdog::watch(msec, reboot, override, verbose)
    //
    //     msec : how long does the watchdog wait, when the process hangs-up in milli seconds
    //   reboot : automatically restart the process
    // override : use internal signal handler (optional)
    //  verbose : print more log information (optional)
    ofxWatchdog::watch(3000, true, true, true);
    
	//ofSetupOpenGL(1024,768, OF_WINDOW);			// <-------- setup the GL context
    
    //ofSetCurrentRenderer(ofGLProgrammableRenderer::TYPE); //for use with shader
    //ofSetupOpenGL(1024,768, OF_WINDOW);
    
    ofAppGlutWindow window;                         //switched back to glut window to allow ofHideCursor()
    ofSetupOpenGL(&window, 1024,768, OF_WINDOW);
    
	// this kicks off the running of my app
	// can be OF_WINDOW or OF_FULLSCREEN
	// pass in width and height too:
	ofRunApp( new ofApp());
}
