#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
	fontMessage.loadFont("vag.ttf",10);
	ofBackground(255,255,255);
}

//--------------------------------------------------------------
void ofApp::update(){
    
}

//--------------------------------------------------------------
void ofApp::draw(){
    
	//ofCircle(mousePoint, 50);
	for(int i=0;i<circlePosition.size();i++) {
        ofSetColor(circlePosition[i].red, circlePosition[i].green, circlePosition[i].blue, 80);
		ofCircle(circlePosition[i].x, circlePosition[i].y, circlePosition[i].size);
	}
    
    ofSetColor(255,0,0);
	fontMessage.drawString(eventMessage,20,20);
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
	cout << "key press: " << key << endl;
	sprintf(eventMessage, "key press: %d", key);
    switch(key) {
        case 114:
            red = 200;
            green = 0;
            blue = 0;
            break;
        case 103:
            red = 0;
            green = 200;
            blue = 0;
            break;
        case 98:
            red = 0;
            green = 0;
            blue = 200;
            break;
        case 61:
            circleSize = circleSize + 10;
            break;
        case 45:
            if(circleSize>10) {
                circleSize = circleSize - 10;
            }
            break;
        case 99:
            sprintf(eventMessage,"clear all");
            circlePosition.clear();
            break;
        default:
            break;
    }
    sprintf(eventMessage,"size:%d red:%d green:%d blue:%d",circleSize,red,green,blue);
    
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){
    
}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){
    
}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){
    
}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){
	cout << "X: " << x << " Y: " << y << " button: " << button << endl;
    Circle circle;
	switch(button) {
        case 0:
            sprintf(eventMessage,"(%d,%d) size:%d red:%d green:%d blue:%d",x,y,circleSize,red,green,blue);
            circle.x = x;
            circle.y = y;
            circle.size = circleSize;
            circle.red = red;
            circle.green = green;
            circle.blue = blue;
            circlePosition.push_back(circle);
            break;
        case 1:
            sprintf(eventMessage,"clear all");
            circlePosition.clear();
            break;
        case 2:
            sprintf(eventMessage,"removed at (%d,%d)",x,y);
            int tempX, tempY, temp;
            int min;
            min = circleSize;
            int nearPosition;
            for(int i=0;i<circlePosition.size();i++) {
                tempX = circlePosition[i].x - x;
                tempY = circlePosition[i].y - y;
                
                temp = sqrt(tempX*tempX + tempY*tempY);
                
                if(temp < min) {
                    min = temp;
                    nearPosition = i;
                }
            }
            if(circleSize > min ) {
                circlePosition.erase(circlePosition.begin()+nearPosition);
            }
            break;
        default:
            sprintf(eventMessage,"mouse pressed at (%d,%d)",x,y);
            break;
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
