#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numBalls = 10;
	spring = 1;
	gravity = 0.1;
	friction = -0.5;
    
	width = ofGetWidth();
	height= ofGetHeight();
    
	for(int i=0;i<numBalls;i++) {
        Ball test;
        test.setup(ofRandom(ofGetWidth()), 0, 10, spring, gravity, friction);
        balls.push_back(test);
        
	}
	
	ofSetFrameRate(60);
	ofBackground(100,100,100);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i=0;i<balls.size();i++) {
		
		balls[i].move();
	}
	checkCollision();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(100,100,100);
	for(int i=0;i<balls.size();i++) {
		ofSetColor(200,0,0,100);
		
		balls[i].display();
	}
    ofSetColor(0,0,200,100);
    ofRect(barStartx,batStarty,barWidth,barHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    printf("%d", key);
    if(key == 356) {
        barStartx -=10;
    } else if (key == 358 ) {
        barStartx +=10;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
    if(button == 0) {
        Ball test;
        test.setup(ofRandom(ofGetWidth()), 0, 10, spring, gravity, friction);
        balls.push_back(test);
    }
    
    
}
//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){
    
}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){
    
}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){
    
}

void ofApp::checkCollision(void) {
	for(int i=0;i<numBalls;i++) {
		for(int j=i+1;j<numBalls;j++) {
			float dx = balls[j].x - balls[i].x;
			float dy = balls[j].y - balls[i].y;
			float distance = ofDist(balls[i].x,balls[i].y,balls[j].x,balls[j].y);
			float minDist = balls[j].diameter/2 + balls[i].diameter/2;
            
			if (distance < minDist) {
				float angle = atan2(dy,dx);
				float targetX = balls[i].x + cos(angle) * minDist;
				float targetY = balls[i].y + sin(angle) * minDist;
				float ax = (targetX - balls[j].x) * spring;
				float ay = (targetY - balls[j].y) * spring;
				balls[i].vx -= ax;
				balls[i].vy -= ay;
				balls[j].vx += ax;
				balls[j].vy += ay;
                
			}
		}
        
//        bool up = balls[i].y + 5 < batStarty;
//        if (!up) {
//            balls[i].vx = -balls[i].vx;
//            balls[i].vy = -balls[i].vy;
//            
//        }
	}
}