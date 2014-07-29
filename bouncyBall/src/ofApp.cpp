#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    numBalls = 10;
	spring = 1;
	gravity = 0.1;
	friction = -1;
    
	width = ofGetWidth();
	height= ofGetHeight();
    
	for(int i=0;i<numBalls;i++) {
        Ball *ball = new Ball();
        ball->setup(ofRandom(ofGetWidth()), 0, 10, spring, gravity, friction);
        balls.push_back(ball);
        
	}
	
	ofSetFrameRate(60);
	ofBackground(100,100,100);
	ofSetVerticalSync(true);
	ofEnableSmoothing();
}

//--------------------------------------------------------------
void ofApp::update(){
	for(int i=0;i<balls.size();i++) {
		
		balls[i]->move();
	}
	checkCollision();
    checkCollisionWithBar();
    checkOutofBall();
}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(100,100,100);
	for(int i=0;i<balls.size();i++) {
		ofSetColor(200,0,0,100);
		
		balls[i]->display();
	}
    ofSetColor(0,0,200,100);
    ofRect(barStartx,batStarty,barWidth,barHeight);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
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
        Ball *ball = new Ball();
        ball->setup(ofRandom(ofGetWidth()), 0, 10, spring, gravity, friction);
        balls.push_back(ball);
    }
    
    if(button == 1) {
        gravity = -0.3;
    }
    
    if(button == 2) {
        gravity = 0.3;
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

void ofApp::checkCollisionWithBar(void) {
    for(int i=0;i<balls.size();i++) {
        bool x = balls[i]->x > barStartx && balls[i]->x < barStartx+barWidth;
        if(balls[i]->y + balls[i]->diameter/2 > batStarty && x) {
            balls[i]->y = batStarty - balls[i]->diameter/2;
            balls[i]->vy *= friction;
        };
    }
}

void ofApp::checkOutofBall(void) {
    for(int i=0;i<balls.size();i++){
        if(balls[i]->status == false) {
            Ball* tmp = balls[i];
            balls.erase(balls.begin()+i);
            delete(tmp);
            break;
        }
        
    }
}




