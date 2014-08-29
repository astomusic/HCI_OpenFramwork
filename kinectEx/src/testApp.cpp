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
    
    verdana.loadFont(ofToDataPath("verdana.ttf"), 15);

	for (int i = 0; i < MAX_NUMBER_OF_HAND; ++i)
	{
		detectingEffectList[i] = new DetectingEffect();
	}

	detectingEffectIdx = 0;

	// hand event를 담당하는 리스너 등록
	ofAddListener(openNIDevice.handEvent, this, &testApp::handEvent);
    
    numBalls = 10;
	spring = 0.1;
	gravity = 0.1;
	friction = -1.0;
    
    width = ofGetWidth();
	height= ofGetHeight();
    
	for(int i=0;i<numBalls;i++) {
        Ball *ball = new Ball();
        ball->setup(ofRandom(ofGetWidth()), 0, 20, spring, gravity, friction);
        ball->setColor(0, 0, 0);
        balls.push_back(ball);
	}
    
    for(int i=0;i<MAX_NUMBER_OF_HAND;i++) {
        Ball* myhand = new Ball();

        myhands.push_back(myhand);
    }

    
    
}

//--------------------------------------------------------------
void testApp::update(){
    openNIDevice.update();
    for(int i=0;i<balls.size();i++) {
		balls[i]->move();
	}
    checkCollision();
    checkCollisionWithHand();
    checkCollisionMeetHand();
}

//--------------------------------------------------------------
void testApp::draw(){
	ofSetColor(255, 255, 255);
    
    ofPushMatrix();
    // draw debug (ie., image, depth, skeleton)
    //openNIDevice.drawDebug();
    //openNIDevice.drawSkeletons();
	openNIDevice.drawDepth();
    ofPopMatrix();
    
    ofPushMatrix();
    // get number of current hands
    numHands = openNIDevice.getNumTrackedHands();
    
    // iterate through users
    for (int i = 0; i < numHands; i++){
        
        // get a reference to this user
        ofxOpenNIHand & hand = openNIDevice.getTrackedHand(i);
        
        // get hand position
        ofPoint & handPosition = hand.getPosition();
        // do something with the positions like:
        
        // draw a rect at the position (don't confuse this with the debug draw which shows circles!!)
        if(i%2==0) {
            myhands[i]->setColor(255, 0, 0);
        } else {
            myhands[i]->setColor(0, 255, 0);
        }
        myhands[i]->setup(handPosition.x, handPosition.y, 100, spring, gravity, friction);

        myhands[i]->display();
    }
    ofPopMatrix();

	for (int i = 0; i < MAX_NUMBER_OF_HAND; ++i)
	{
		detectingEffectList[i]->display();
	}
    
    for(int i=0;i<balls.size();i++) {
		
		balls[i]->display();
	}

    
    // draw some info regarding frame counts etc
	ofSetColor(0, 0, 0);
	string msg = " MILLIS: " + ofToString(ofGetElapsedTimeMillis()) + " FPS: " + ofToString(ofGetFrameRate()) + " Device FPS: " + ofToString(openNIDevice.getFrameRate());
	verdana.drawString(msg, 10, openNIDevice.getNumDevices() * 480 - 20);
    
    ofSetColor(255, 0, 0);
    string redScore = "RED: " + ofToString(countRed());
    verdana.drawString(redScore, 50, 50);
    
    ofSetColor(0, 255, 0);
    string greenScore = "GREEN: " + ofToString(countGreen());
    verdana.drawString(greenScore, 500, 50);
    
    if(countRed() == 10) {
        ofSetColor(255, 0, 0);
        redScore = "RED WIN";
        verdana.drawString(redScore, 250, 50);
        openNIDevice.stop();
    }
    
    if(countGreen() == 10) {
        ofSetColor(0, 255, 0);
        greenScore = "GREEN WIN";
        verdana.drawString(greenScore, 250, 50);
        openNIDevice.stop();
    }
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

int testApp::countRed() {
    int red = 0;
    int count = 0;
    for(int i=0;i<balls.size();i++) {
        red = balls[i]->getRed();
        if(red == 255) {
            count++;
        }
    }
    
    return count;
}

int testApp::countGreen() {
    int green = 0;
    int count = 0;
    for(int i=0;i<balls.size();i++) {
        green = balls[i]->getGreen();
        if(green == 255) {
            count++;
        }
    }
    
    return count;
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

void testApp::checkCollisionWithHand(void) {
    for(int i=0;i<balls.size();i++) {
        for (int j = 0; j < numHands; j++){
            float dx = myhands[j]->x - balls[i]->x;
            float dy = myhands[j]->y - balls[i]->y;
            float distance = ofDist(balls[i]->x,balls[i]->y,myhands[j]->x,myhands[j]->y);
            float minDist = myhands[j]->diameter/2 + balls[i]->diameter/2;
        
            if (distance < minDist) {
                float angle = atan2(dy,dx);
                float targetX = balls[i]->x + cos(angle) * minDist;
                float targetY = balls[i]->y + sin(angle) * minDist;
                float ax = (targetX - myhands[j]->x) * spring;
                float ay = (targetY - myhands[j]->y) * spring;
                balls[i]->vx -= ax;
                balls[i]->vy -= ay;
                if(j%2 ==0) {
                    balls[i]->setColor(255, 0, 0);
                } else {
                    balls[i]->setColor(0, 255, 0);
                }
                
            }
        }
    }
}

void testApp::checkCollisionMeetHand(void) {
    if(numHands < 2) {
        return;
    }
    int i = 0;
    int j = i+1;

    float dx = myhands[j]->x - myhands[i]->x;
    float dy = myhands[j]->y - myhands[i]->y;
    float distance = ofDist(myhands[i]->x,myhands[i]->y,myhands[j]->x,myhands[j]->y);
    float minDist = myhands[j]->diameter/2 + myhands[i]->diameter/2;
            
    if (distance < minDist) {
        for(int k=0;k<balls.size();k++) {
            balls[k]->setColor(0, 0, 0);
        }
    }

}
