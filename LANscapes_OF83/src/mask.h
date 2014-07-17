//
//  mask.h
//  LANscapes_OF83
//
//  Created by curry on 7/16/14.
//
//

#ifndef __LANscapes_OF83__mask__
#define __LANscapes_OF83__mask__

#include <iostream>
#include "OfMain.h"

class mask : public ofBaseApp {
    
public:
    
    void setup( ofVec2f, ofVec2f, ofVec2f, ofVec2f );
    void update( ofVec2f, ofVec2f, ofVec2f, ofVec2f );
    void draw();
    
    ofVec2f vertex[ 4 ];
    
};


#endif /* defined(__LANscapes_OF83__mask__) */
