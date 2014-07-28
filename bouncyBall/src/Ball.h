//
//  Ball.h
//  emptyExample
//
//  Created by astomusic on 2014. 7. 28..
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
	void setup(float xin, float yin, float din, int idin, float springin, float graivityin, float frictionin);
    
	void move();
	void display();
    
public:
	float x;
	float y;
	float diameter;
	float vx;
	float vy;
	int id;
    
	float spring;
	float gravity;
	float friction;
    
	float width;
	float height;
    
};
