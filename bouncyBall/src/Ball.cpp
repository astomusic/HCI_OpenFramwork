//
//  Ball.cpp
//  emptyExample
//
//  Created by astomusic on 2014. 7. 28..
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
        status = false;
//        y = height - diameter/2;
//        vy *= friction;
    }
    if (y - diameter/2 < 0) {
        y = diameter/2;
        vy *= friction;
    }   
}

void Ball::display()
{
	ofCircle(x, y, diameter/2);
}