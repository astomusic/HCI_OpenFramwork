#ifndef _TEST_APP
#define _TEST_APP

#include "ofxOpenNI.h"
#include "ofMain.h"
#include "Ball.h"
#include "DetectingEffect.h"
#include <tr1/array>

#define MAX_DEVICES 1
#define MAX_NUMBER_OF_HAND 1

class testApp : public ofBaseApp{

public:
    
	void setup();
	void update();
	void draw();
    void exit();
    
	void keyPressed  (int key);
	void keyReleased(int key);
	void mouseMoved(int x, int y );
	void mouseDragged(int x, int y, int button);
	void mousePressed(int x, int y, int button);
	void mouseReleased(int x, int y, int button);
	void windowResized(int w, int h);

private:
    
    void handEvent(ofxOpenNIHandEvent & event);
    
	ofxOpenNI openNIDevice;
    ofTrueTypeFont verdana;
    
	std::tr1::array<DetectingEffect*, MAX_NUMBER_OF_HAND> detectingEffectList;
    
	unsigned int detectingEffectIdx;
    
    vector<Ball*> balls;
    
    int numBalls;
    float spring;
    float gravity;
    float friction;
    
    float width;
    float height;
    
    int barStartx = 0;
    int barStarty = 0;
    int barWidth = 100;
    int barHeight = 20;
    
    void checkCollision();
    void checkCollisionWithBar();

};

#endif
