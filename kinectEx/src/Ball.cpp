//
//  Ball.cpp
//  openNiSample007
//
//  Created by astomusic on 2014. 8. 10..
//
//

#include "Ball.h"

Ball::Ball(void)
{
}


Ball::~Ball(void)
{
}

void Ball::setGravity(float gravityin)
{
    gravity = gravityin;
}

void Ball::setup(float xin, float yin, float din, float springin, float graivityin, float frictionin)
{
	vx = 0;
	vy = 0;
    
	x = xin;
	y = yin;
	diameter = din;
	
	spring = springin;
	gravity = graivityin;
	friction = frictionin;
    
	width = ofGetWidth();
	height= ofGetHeight();
}

void Ball::move()
{
	vy += gravity;
    if(vx > 10) {
        vx = 10;
    }
    if(vy > 10) {
        vy = 10;
    }
    x += vx;
    y += vy;
    if (x + diameter/2 > width) {
        x = width - diameter/2;
        vx *= friction;
    }
    else if (x - diameter/2 < 0) {
        x = diameter/2;
        vx *= friction;
    }
    if (y - diameter/2 > height) {
        //status = false;
        y = height - diameter/2;
        vy *= friction;
    }
    if (y - diameter/2 < 0) {
        y = diameter/2;
        vy *= friction;
    }
}

void Ball::setColor(int r, int g, int b) {
    red = r;
    green = g;
    blue = b;
}

int Ball::getRed() {
    return red;
}
int Ball::getGreen() {
    return green;
}
int Ball::getBlue() {
    return blue;
}

void Ball::display()
{
    ofSetColor(red,green,blue);
	ofCircle(x, y, diameter/2);
}