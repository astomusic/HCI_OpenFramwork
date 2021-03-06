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
    void setColor(int red, int green, int blue);
    
    int getRed();
    int getGreen();
    int getBlue();
    
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
    
    int red, green, blue;
    
    bool status = true;
    
};
