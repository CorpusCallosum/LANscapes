#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    
    //load settings xml data file
    //-----------
	//the string is printed at the top of the app
	//to give the user some feedback
	message = "loading settings.xml";
    
	//we load our settings file
	//if it doesn't exist we can still make one
	//by hitting the 's' key
	if( XML.loadFile("settings.xml") ){
		message = "settings.xml loaded!";
	}else{
		message = "unable to load settings.xml check data/ folder";
	}
    
    ofSetFullscreen( true );
    
    //setup gui and initial values from xml
    gui.setup();
    gui.setBrightness(XML.getValue("group:brightness", .2));
    gui.setContrast(XML.getValue("group:contrast", .2));
    gui.setExtrusion(XML.getValue("group:extrusion", .2));
    gui.setAlphaValue(XML.getValue("group:alphaValue", .2));
 	gui.setMovementThreshold(XML.getValue("group:movementThreshold", 10));
    gui.setFlickerThreshold(XML.getValue("group:flickerThreshold", 10));
    gui.setFarThreshold(XML.getValue("group:far_threshold", 108));
    
    gui.setRotX(XML.getValue("group:rot_x", 20));
    gui.setxOffset(XML.getValue("group:xOffset", 20));
    gui.setyOffset(XML.getValue("group:yOffset", 20));
    gui.setzOffset(XML.getValue("group:zOffset", 20));
    
    gui.mirrorV = XML.getValue("group:mirror_vertically", false);
    gui.mirrorH = XML.getValue("group:mirror_horizontally", false);
    
    gui.setUpSpeed(XML.getValue("group:soundUpSpeed", .00000001));
    gui.setDownSpeed(XML.getValue("group:soundDownSpeed", .001));
   // saveHour = ofToInt(XML.getValue("group:save_hour", "18"));
    
    //Set this to FALSE to use webcam
    //TODO: add this to the XML file
    useKinect = ofToBool(XML.getValue("group:use_kinect", "1"));
    
    
    //setup vars default values
    //PRESS B TO CAPTURE BACKGROUND//
    fullscreen = true; // f
    bDrawVideo = gui.drawVideo();  // v , should be false
    bWireframe = gui.isWireOn();  // w draw wireframe mesh, should be true
    bFaces = gui.drawFaces();// true;      // e draw faces of main mesh
    bColorWireframe = gui.colorWireframe();
    
    rotX = gui.getX();//set RotX value from the gui
    
    rotY = 0;
    rotZ = 0;
    transX = 0;
    transY = -75;
    transZ = 90;
    
    width =  600;
    height = 480;
    extrusionAmount = gui.getExtrusion();
    previousHour = 666;
    
    
    
    if ( useKinect ) {
        kinect.init( false, false );
        kinect.open();		// opens first available kinect
    }
    else {
        vidGrabber.setVerbose(true);
        vidGrabber.initGrabber( width, height );
    }
	
    //webcam images
    colorImg.allocate( width, height );
    grayImage.allocate( width, height );
    
    //image used to draw mesh
    modifiedImage.allocate( width, height );
    kinectImage.allocate( kinect.width, kinect.height );
    
    //thresholding
    nearThreshold = 255;
    //farThreshold = 55;
    kinect.setDepthClipping( 800, 5000 );
    
    //croping
    kinectImage.setROI(0, 0, width, height);
    croppedImg.allocate(width, height);
    
    //reference image
    snapShot.allocate( width, height, OF_IMAGE_GRAYSCALE );
    background.allocate( width, height );
    snapShot.loadImage( "background.jpg" );
    snapShotPix = snapShot.getPixels();
    background.setFromPixels( snapShotPix, width, height );
    
    modifiedImage.setFromPixels( background.getPixels(), width, height );
    
    
    mainMesh.setup( 64, 48, extrusionAmount, true, true );// ( width, height, extrusion amount, draw wireframe, draw faces );
    //processImage.setup( width, height, 10, 10, modifiedImage ); // (width, height, low threshold for movement, flicker);
    
    //set values from the xml file
    mainMesh.xOffset = XML.getValue("xOffset", 0);
    mainMesh.zOffset = XML.getValue("zOffset", 0);
    mainMesh.yOffset = XML.getValue("yOffset", 0);
    mainMesh.wireframeBrightness = XML.getValue("wireframe:brightness", 255);
    mainMesh.wireframeSaturation = XML.getValue("wireframe:saturation", 100);
    
    //setup camera starting position
    //move the camera around the mesh
    ofVec3f camDirection( 0, 0, 1 );
    ofVec3f centre( width / 2.f, height / 2.f, 128 / 2.f );
    camDirectionRotated = camDirection.rotated( rotX, rotY, rotZ );
    ofVec3f camPosition = centre + camDirectionRotated * extrusionAmount;
    camPosition += ofVec3f( transX, transY, transZ );
	
    cam.setPosition( camPosition );
    cam.lookAt( centre + ofVec3f( 0, -35, 0 ));
    
    // this sets the camera's distance from the object
    cam.setDistance(100);
    cam.disableMouseInput();
    
    //sound setup
    //soundCalculations.setup( width, height );
    
    whichOne = 2;
    numSounds = 3;
    volume.resize( numSounds );
    pan.resize( numSounds );
    
    //masking rectangles
    mask.resize( 4 );
    
    if ( whichOne == 1 ) { //north
        
        sound[ 0 ] = new ofSoundPlayer;
        sound[ 0 ]->loadSound( "sounds/bio_6_30.aiff" );
        sound[ 1 ] = new ofSoundPlayer;
        sound[ 1 ]->loadSound( "sounds/popaea_7_00.aiff" );
        sound[ 2 ] = new ofSoundPlayer;
        sound[ 2 ]->loadSound( "sounds/iceburg_6_14.aiff" );
        
        corners[ 0 ].set( 0.0, 0.0 ); //top left
        corners[ 1 ].set( 147.0, 0.0 );
        corners[ 2 ].set( 660.0, 0.0 );
        corners[ 3 ].set( 800.0, 0.0 ); //top right
        corners[ 4 ].set( 800.0, 210.0 );
        corners[ 5 ].set( 800.0, 1080.0 );
        corners[ 6 ].set( 800.0, 1280.0 ); //bottom right
        corners[ 7 ].set( 660.0, 1280.0 );
        corners[ 8 ].set( 147.0, 1280.0 );
        corners[ 9 ].set( 0.0, 1280.0 ); //bottom left
        corners[ 10 ].set( 0.0, 1080.0 );
        corners[ 11].set( 0.0, 210.0 );
        
    }
    
    if ( whichOne == 2 ) { //south
        
        sound[ 0 ] = new ofSoundPlayer;
        sound[ 0 ]->loadSound( "sounds/harp_6_00.aiff" );
        sound[ 1 ] = new ofSoundPlayer;
        sound[ 1 ]->loadSound( "sounds/creep_6_21.wav" );
        sound[ 2 ] = new ofSoundPlayer;
        sound[ 2 ]->loadSound( "sounds/bio_6_30.aiff" );
        
        corners[ 0 ].set( 0.0, 0.0 ); //top left
        corners[ 1 ].set( 147.0, 0.0 );
        corners[ 2 ].set( 660.0, 0.0 );
        corners[ 3 ].set( 800.0, 0.0 ); //top right
        corners[ 4 ].set( 800.0, 210.0 );
        corners[ 5 ].set( 800.0, 1080.0 );
        corners[ 6 ].set( 800.0, 1280.0 ); //bottom right
        corners[ 7 ].set( 660.0, 1280.0 );
        corners[ 8 ].set( 147.0, 1280.0 );
        corners[ 9 ].set( 0.0, 1280.0 ); //bottom left
        corners[ 10 ].set( 0.0, 1080.0 );
        corners[ 11].set( 0.0, 210.0 );
        
    }
    
    
    for ( int i = 0; i < numSounds; i ++ ) {
        sound[ i ]->setLoop( true );
        sound[ i ]->setVolume( 0.0 );
        sound[ i ]->play();
    }
    sound[ 0 ]->setPan( -1.0 );
    sound[ 1 ]->setPan( 0.0 );
    sound[ 2 ]->setPan( 1.0 );
    
    soundUpSpeed = gui.getUpSpeed();
    soundDownSpeed = gui.getDownSpeed();
    
    mask[ 0 ].setup( corners[ 0 ], corners[ 3 ], corners[ 4 ], corners[ 11 ] );
    mask[ 1 ].setup( corners[ 2 ], corners[ 3 ], corners[ 6 ], corners[ 7 ] );
    mask[ 2 ].setup( corners[ 10 ], corners[ 5 ], corners[ 6 ], corners[ 9 ] );
    mask[ 3 ].setup( corners[ 0 ], corners[ 1 ], corners[ 8 ], corners[ 9 ] );
    
    processImage.setup( width, height, 10, 10, modifiedImage, whichOne, numSounds,soundUpSpeed, soundDownSpeed ); // (width, height, low threshold for movement, flicker);
    
}


//----------------------------------------------------------
void ofApp::update(){
    
	ofBackground( 0 );
    
    farThreshold = gui.farThreshold;
    //cout << "farThreshold: " << farThreshold << endl;
    
    if ( useKinect ) {
        kinect.update();
        if(kinect.isFrameNew()) {
            // load grayscale depth image from the kinect source
            kinectImage.setFromPixels( kinect.getDepthPixels(),kinect.width, kinect.height);
            
            unsigned char * pix = kinectImage.getPixels();
			
			int numPixels = kinectImage.getWidth() * kinectImage.getHeight();
			for(int i = 0; i < numPixels; i++) {
				if(pix[i] > nearThreshold || pix[i] < farThreshold) {
					pix[i] = 0;
				}
                else{ pix[i] = ofMap( pix[i], farThreshold, 255, 0, 255 );}
			}
            
            croppedImg.scaleIntoMe(kinectImage);
            //mirror the image  - causese black line :(
            croppedImg.mirror(gui.mirrorV, gui.mirrorH);
            modifiedImage = processImage.getProcessedImage( croppedImg, background );
            mainMesh.update( modifiedImage , extrusionAmount, bColorWireframe );
            
        }
    }
    else {
        bool bNewFrame = false;
        vidGrabber.update();
        bNewFrame = vidGrabber.isFrameNew();
        
        if (bNewFrame){
            colorImg.setFromPixels( vidGrabber.getPixels(), width, height );
            colorImg.mirror(gui.mirrorV, gui.mirrorH);
            grayImage = colorImg;
            modifiedImage = processImage.getProcessedImage( grayImage, background );
            mainMesh.update( modifiedImage , extrusionAmount, bColorWireframe);
        }
        
    }
    
    //SAVE the mesh
    int currentHour = ofGetHours();
    if( currentHour != previousHour){
        cout<<"currentHour != previousHour"<<endl;
        XML.pushTag("group");
        XML.pushTag("save_times");
        for (int i=0; i<XML.getNumTags("hour"); i++){
            cout<<"current hour: "<<currentHour<<endl;
            saveHour = ofToInt(XML.getValue("hour", "18", i));
            cout<<"save hour: "<<saveHour<<endl<<endl;

            if(currentHour == saveHour )
                mainMesh.save();
        }
        XML.popTag();
        XML.popTag();
        previousHour = currentHour;
    }
    
    //get  data from gui
    float b = gui.getBrightness();
    float c = gui.getContrast();
    extrusionAmount  = gui.getExtrusion();
    float a = gui.getAlpha();
    rotX = gui.getX();
    int m = gui.getMovementThreshold();
    int t = gui.getFlickerThreshold();
    soundUpSpeed = gui.getUpSpeed();
    soundDownSpeed = gui.getDownSpeed();
    processImage.update( b, c, a, m, t, soundUpSpeed, soundDownSpeed);
    
    //wireframe
    bWireframe = gui.isWireOn();
    bDrawVideo = gui.drawVideo();
    bColorWireframe = gui.colorWireframe();
    bFaces = gui.drawFaces();//   e draw faces of main mesh
    mainMesh.yOffset = gui.getyOffset();
    mainMesh.zOffset = gui.getzOffset();
    mainMesh.xOffset = gui.getxOffset();
    
    //update sound soundCalculations is updated through processImage, so we pass volumes through
    volume = processImage.getVolume();
    pan = processImage.getPan();
    
    
    
    for ( int i = 0; i < numSounds; i ++ ) {
        sound[ i ]->setVolume( volume[ i ] );
        sound[ i ]->setPan( pan[ i ] );
        //cout << "volume[ " << i << " ]: " << volume[ i ]  << endl;
        //cout << "pan[ " << i << " ]: " << pan[ i ]  << endl;
        //sound[ i ]->setSpeed( speed[ i ] );
    }
    
    
}

//--------------------------------------------------------------
void ofApp::draw(){

    
    ////DRAW THE MESH
	//but we want to enable it to show the mesh
	ofEnableDepthTest();
	cam.begin();
    //rotate the camera
    ofRotateX(rotX);
    
    mainMesh.draw( bWireframe, bFaces );
	cam.end();
    
    
    
    ////DRAW DEPTH IMAGES
    //we have to disable depth testing to draw the video frame
    ofDisableDepthTest();
    if ( bDrawVideo ) {
        
        if ( useKinect ) {
            int margin = 20;
            int w = 320;
            int h = 230;
            kinectImage.draw( margin, 20, w, h );
            ofEnableAlphaBlending();
            modifiedImage.draw( 20 + w+margin, margin, w, h );
            soundCalculations.draw( 20 + w + margin, margin, w, h );
            ofDisableAlphaBlending();
            background.draw( 20 + (w+margin)*2, margin, w, h );
            
        }
        
        else {
            
            colorImg.draw( 20, 20, 320, 240 );
            grayImage.draw( 20 + 320, 20, 320, 240 );
            ofEnableAlphaBlending();
            modifiedImage.draw( 20 + 2 * 320, 20, 320, 240 );
            soundCalculations.draw( 20 + 2 * 320, 20, 320, 240 );
            ofDisableAlphaBlending();
            background.draw( 20 + 3 * 320, 20, 320, 240 );
            
        }
        
        
    }
    
    else {
        //draw the masks
        for ( int i = 0; i < 4; i ++ ) {
            mask[ i ].draw();
        }
    }
    
    
    
    ////DRAW THE GUI
    gui.draw();
    
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    
	switch (key){
        case 'f':
			fullscreen = !fullscreen;
            ofSetFullscreen( fullscreen );
			break;
            
        case '>':
		case '.':
			farThreshold ++;
			if (farThreshold > 255) farThreshold = 255;
            cout<< farThreshold<< endl;
			break;
			
		case '<':
		case ',':
			farThreshold --;
			if (farThreshold < 0) farThreshold = 0;
            cout<< farThreshold<< endl;
			break;
			
		case '+':
		case '=':
			nearThreshold ++;
			if (nearThreshold > 255) nearThreshold = 255;
            cout<< nearThreshold<< endl;
			break;
			
		case '-':
			nearThreshold --;
			if (nearThreshold < 0) nearThreshold = 0;
            cout<< nearThreshold<< endl;
			break;
            
        case ']':
            rotY += 10;
            break;
            
        case '[':
            rotY -= 10;
            break;
            
        case 'w':
            bWireframe = !bWireframe;
            break;
            
        case 'e':
            bFaces = !bFaces;
            break;
            
        case 'v':
            bDrawVideo = !bDrawVideo;
            break;
            
        case 'k':
            useKinect = !useKinect;
            break;
            
        case 'g':
            if(gui.hidden){
                gui.show();
            }
            else{
                gui.hide();
            }
            break;
            
        case 'p':
            cout << "( transX, transY, transZ ): ( " << transX << ", " << transY << ", " << transZ << " )" << endl;
            cout << "( rotX, rotY, rotZ ): ( " << rotX << ", " << rotY << ", " << rotZ << " )" << endl;
            cout << "( yOffset, zOffset ): ( " << mainMesh.yOffset << ", " << mainMesh.zOffset << ", "<<mainMesh.xOffset<<" )" << endl;
			break;
            
        case 's':
            //save the mesh and color data
            mainMesh.save();
			break;
        case 'b':
            if ( useKinect ) {
                snapShotPix = croppedImg.getPixels();
            }
            else {
                snapShotPix = grayImage.getPixels();
            }
            snapShot.setFromPixels( snapShotPix, width, height, OF_IMAGE_GRAYSCALE );
            snapShot.saveImage( "background.jpg" );
            background.setFromPixels( snapShotPix, width, height );
            break;
        case OF_KEY_UP:
            mainMesh.zOffset -= 1;
            break;
        case OF_KEY_DOWN:
            mainMesh.zOffset += 1;
            break;
        case OF_KEY_LEFT:
            mainMesh.yOffset += 1;
            break;
        case OF_KEY_RIGHT:
            mainMesh.yOffset -= 1;
            break;
            
        case 'l':
            //save the mesh and color data
            corners[ 4 ].y ++;
            mask[ 0 ].update( corners[ 0 ], corners[ 3 ], corners[ 4 ], corners[ 11 ] );
            cout << "4 y: " << corners[ 4 ].y << endl;
			break;
            
        case 'j':
            //save the mesh and color data
            corners[ 4 ].y ++;
            mask[ 0 ].update( corners[ 0 ], corners[ 3 ], corners[ 4 ], corners[ 11 ] );
            cout << "4 y: " << corners[ 4 ].y << endl;
			break;
            
        case 'i':
            //save the mesh and color data
            corners[ 11 ].y ++;
            mask[ 0 ].update( corners[ 0 ], corners[ 3 ], corners[ 4 ], corners[ 11 ] );
            cout << "11 y: " << corners[ 11 ].y << endl;
			break;
            
        case 'm':
            //save the mesh and color data
            corners[ 11 ].y ++;
            mask[ 0 ].update( corners[ 0 ], corners[ 3 ], corners[ 4 ], corners[ 11 ] );
            cout << "11 y: " << corners[ 11 ].y << endl;
			break;
            
	}
    
}