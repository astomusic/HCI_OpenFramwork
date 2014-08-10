#include "testApp.h"

//--------------------------------------------------------------
void testApp::setup() {
    
    ofSetLogLevel(OF_LOG_VERBOSE);

    openNIDevice.setup();
    openNIDevice.addImageGenerator();
    openNIDevice.addDepthGenerator();
    openNIDevice.setRegister(true);
    openNIDevice.setMirror(true);
    
    // setup the hand generator
    openNIDevice.addHandsGenerator();
    
    // add all focus gestures (ie., wave, click, raise arm)
    openNIDevice.addAllHandFocusGestures();
    
    // or you can add them one at a time
    //vector<string> gestureNames = openNIDevice.getAvailableGestures(); // you can use this to get a list of gestures
                                                                         // prints to console and/or you can use the returned vector
    //openNIDevice.addHandFocusGesture("Wave");
    
    openNIDevice.setMaxNumHands(MAX_NUMBER_OF_HAND);
    
    openNIDevice.start();
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 24);

	for (int i = 0; i < MAX_NUMBER_OF_HAND; ++i)
	{
		detectingEffectList[i] = new DetectingEffect();
	}

	detectingEffectIdx = 0;

	// hand event를 담당하는 리스너 등록
	ofAddListener(openNIDevice.handEvent, this, &testApp::handEvent);
    
    numBalls = 10;
	spring = 0.5;
	gravity = 0.1;
	friction = -1.0;
    
    width = ofGetWidth();
	height= ofGetHeight();
    
	for(int i=0;i<numBalls;i++) {
        Ball *ball = new Ball();
        ball->setup(ofRandom(ofGetWidth()), 0, 10, spring, gravity, friction);
        balls.push_back(ball);
	}
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    for(int i=0;i<balls.size();i++) {
		balls[i]->move();
	}
    checkCollision();
    checkCollisionWithBar();

}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    //openNIDevice.drawDebug();
	openNIDevice.drawDepth();
    ofPopMatrix();
    
    ofPushMatrix();
    // get number of current hands
    int numHands = openNIDevice.getNumTrackedHands();
    
    // iterate through users
    for (int i = 0; i < numHands; i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
        
        // get hand position
        ofPoint & handPosition = hand.getPosition();
        // do something with the positions like:
        
        // draw a rect at the position (don't confuse this with the debug draw which shows circles!!)
        ofSetColor(255,0,0);
        barStartx = handPosition.x-(barWidth/2);
        barStarty = handPosition.y;
        ofRect(barStartx, barStarty, barWidth, barHeight);
        
        
    }
    ofPopMatrix();

	for (int i = 0; i < MAX_NUMBER_OF_HAND; ++i)
	{
		detectingEffectList[i]->display();
	}
    
    for(int i=0;i<balls.size();i++) {
		ofSetColor(200,0,0);
		
		balls[i]->display();
	}
//    
//    ofSetColor(255,255,255);
//    ofRect(100, 100, 100, 100);
    
    // draw some info regarding frame counts etc
	ofSetColor(0, 255, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
    
	verdana.drawString(msg, 20, openNIDevice.getNumDevices() * 480 - 20);

}

//--------------------------------------------------------------
void testApp::handEvent(ofxOpenNIHandEvent & event){
    // show hand event messages in the console
    // ofLogNotice() << getHandStatusAsString(event.handStatus) << "for hand" << event.id << "from device" << event.deviceID;

	// add detecting effect
	if (event.handStatus == HAND_TRACKING_STARTED)
	{
		detectingEffectList[detectingEffectIdx]->startEffect(event.position.x, event.position.y);
		detectingEffectIdx = (detectingEffectIdx + 1) % MAX_NUMBER_OF_HAND;
	}
}

//--------------------------------------------------------------
void testApp::exit(){
    openNIDevice.stop();
}

//--------------------------------------------------------------
void testApp::keyPressed(int key){

}

//--------------------------------------------------------------
void testApp::keyReleased(int key){

}

//--------------------------------------------------------------
void testApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void testApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void testApp::windowResized(int w, int h){

}

void testApp::checkCollision(void) {
	for(int i=0;i<balls.size();i++) {
		for(int j=i+1;j<balls.size();j++) {
			float dx = balls[j]->x - balls[i]->x;
			float dy = balls[j]->y - balls[i]->y;
			float distance = ofDist(balls[i]->x,balls[i]->y,balls[j]->x,balls[j]->y);
			float minDist = balls[j]->diameter/2 + balls[i]->diameter/2;
            
			if (distance < minDist) {
				float angle = atan2(dy,dx);
				float targetX = balls[i]->x + cos(angle) * minDist;
				float targetY = balls[i]->y + sin(angle) * minDist;
				float ax = (targetX - balls[j]->x) * spring;
				float ay = (targetY - balls[j]->y) * spring;
				balls[i]->vx -= ax;
				balls[i]->vy -= ay;
				balls[j]->vx += ax;
				balls[j]->vy += ay;
			}
		}
    }
}

void testApp::checkCollisionWithBar(void) {
    for(int i=0;i<balls.size();i++) {
        bool x = balls[i]->x + balls[i]->diameter/2 > barStartx && balls[i]->x - balls[i]->diameter/2 < barStartx + barWidth;
        bool y = balls[i]->y + balls[i]->diameter/2 > barStarty && balls[i]->y - balls[i]->diameter/2 < barStarty + barHeight;
        int half = barStartx + barWidth/2;
        if(x && y) {
            if(balls[i]->y < barStarty){
                balls[i]->y = barStarty - balls[i]->diameter/2;
                balls[i]->vy *= friction;
            } else {
                balls[i]->y = barStarty + barHeight + balls[i]->diameter/2;
                balls[i]->vy *= friction;
            }
            
            if(half > balls[i]->x) {
                balls[i]->vx -= 1;
            } else {
                balls[i]->vx += 1;
            }
        }
    }
    
//    if (y - diameter/2 > height) {
//        y = height - diameter/2;
//        vy *= friction;
//    }
//    if (y - diameter/2 < 0) {
//        y = diameter/2;
//        vy *= friction;
//    }
}