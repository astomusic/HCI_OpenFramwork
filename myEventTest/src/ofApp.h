#pragma once

#include "ofMain.h"

class ofApp : public ofBaseApp{

struct Circle {
    int x;
    int y;
    int size;
    int red;
    int green;
    int blue;
};
    
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y );
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    ofTrueTypeFont fontMessage;
    char eventMessage[255];
    
    //ofPoint mousePoint;
    vector<Circle> circlePosition;
    
    int circleSize = 10;
    int red = 0;
    int green = 200;
    int blue = 0;
		
};
