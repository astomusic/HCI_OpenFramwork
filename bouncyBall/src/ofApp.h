#pragma once

#include "ofMain.h"
#include "Ball.h"

class ofApp : public ofBaseApp{
public:
    void setup();
    void update();
    void draw();
    
    void keyPressed(int key);
    void keyReleased(int key);
    void mouseMoved(int x, int y);
    void mouseDragged(int x, int y, int button);
    void mousePressed(int x, int y, int button);
    void mouseReleased(int x, int y, int button);
    void windowResized(int w, int h);
    void dragEvent(ofDragInfo dragInfo);
    void gotMessage(ofMessage msg);
    
    int numBalls;
    float spring;
    float gravity;
    float friction;
    
    vector<Ball*> balls;
    
    float width;
    float height;
    
    int barStartx = 100;
    int batStarty = 330;
    int barWidth = 100;
    int barHeight = 20;
    
    void checkCollision();
    void checkCollisionWithBar();
    void checkOutofBall();
};
