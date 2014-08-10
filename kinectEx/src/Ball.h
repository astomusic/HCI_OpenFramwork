//
//  Ball.h
//  openNiSample007
//
//  Created by astomusic on 2014. 8. 10..
//
//


#pragma once

#include "ofMain.h"

class Ball
{
public:
	Ball(void);
	~Ball(void);
    
    void setGravity(float springin);
	void setup(float xin, float yin, float din, float springin, float graivityin, float frictionin);
    
	void move();
	void display();
    
public:
	float x;
	float y;
	float diameter;
	float vx;
	float vy;
    
	float spring;
	float gravity;
	float friction;
    
	float width;
	float height;
    
    bool status = true;
    
};
