//
//  Camera.cpp
//  MP2FlightSimulatorFinal
//
//  Created by Shaun Chung on 3/8/15.
//  Copyright (c) 2015 Shaun Chung. All rights reserved.
//

#ifndef __MAC__
#define __MAC__ 1
#endif

#ifdef __MAC__
# include <GLUT/glut.h>
#else
# include <GL/glut.h>
#endif
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "vector.h"
#include <iostream>

/*Plane Vectors*/
Vector wing;
Vector up;
Vector view;
Vector translate;

float speed;
float roll;
float pitch;

bool button_pressed[] = {false, false, false, false};

void camera_init(){
    speed = 0.001;
    roll = 0.03;
    pitch = 0.03;
    translate = (Vector){0.0,0.0,0.10};
    wing = (Vector){0.0,1.0,0.0};
    up = (Vector){0.0,0.0,1.0};
    view = (Vector){1.0,0.0,0.0};
}

void camera_keyboard(unsigned char key, int x, int y){
	   switch (key) {
           case 'w':
               button_pressed[0] = true;
               break;
           case 'a':
               button_pressed[1] = true;
               break;
           case 's':
               button_pressed[2] = true;
               break;
           case 'd':
               button_pressed[3] = true;
               break;
           default:
               break;
       }
}

void camera_keyboard_up(unsigned char key, int x, int y){
	   switch (key) {
           case 'w':
               button_pressed[0] = false;
               break;
           case 'a':
               button_pressed[1] = false;
               break;
           case 's':
               button_pressed[2] = false;
               break;
           case 'd':
               button_pressed[3] = false;
               break;
           default:
               break;
       }
}

Vector rotate_point(Vector point, Vector vec, float angle){
    float x, y, z, xVec, yVec, zVec, xRot, yRot, zRot;
    x = point.x;
    y = point.y;
    z = point.z;
    xVec = vec.x; //u
    yVec = vec.y; //v
    zVec = vec.z; //w
    xRot = xVec*(xVec*x+yVec*y+zVec*z) + (x*(yVec*yVec+zVec*zVec)-xVec*(yVec*y+zVec*z))*cos(angle) + sqrt(xVec*xVec+yVec*yVec+zVec*zVec) * (-zVec*y+yVec*z) * sin(angle);
    yRot = yVec*(xVec*x+yVec*y+zVec*z) + (y*(xVec*xVec+zVec*zVec)-yVec*(xVec*x+zVec*z))*cos(angle) + sqrt(xVec*xVec+yVec*yVec+zVec*zVec) * (zVec*x-xVec*z) * sin(angle);
    zRot = zVec*(xVec*x+yVec*y+zVec*z) + (z*(xVec*xVec+yVec*yVec)-zVec*(xVec*x+yVec*y))*cos(angle) + sqrt(xVec*xVec+yVec*yVec+zVec*zVec) * (-yVec*x+xVec*y) * sin(angle);
    float mag = xVec*xVec + yVec* yVec + zVec*zVec;
    return (Vector){xRot/mag,yRot/mag,zRot/mag};
}

//rolls the plane around the view vector
void roll_plane(float roll){
    up = rotate_point(up, view, roll);
    wing = rotate_point(wing, view, roll);
}

//pitches the plane around the wing vector
void pitch_plane(float pitch){
    up = rotate_point(up, wing, pitch);
    view = rotate_point(view, wing, pitch);
}

void roll_left(){
    roll_plane(-roll);
}
void roll_right(){
    roll_plane(roll);
}
void pitch_up(){
    pitch_plane(pitch);
}
void pitch_down(){
    pitch_plane(-pitch);
}

void move(){
    translate.x += speed*view.x;
    translate.y += speed*view.y;
    translate.z += speed*view.z;
}

void camera_timer(int v)
{
    if(button_pressed[0])
    {
        pitch_down();
    }
    if(button_pressed[1])
    {
        roll_left();
    }
    if(button_pressed[2])
    {
        pitch_up();
    }
    if(button_pressed[3])
    {
        roll_right();
    }
    move();
}

void update_view(){
    glLoadIdentity();
    gluLookAt(translate.x,translate.y,translate.z,translate.x + view.x,translate.y + view.y, translate.z + view.z,up.x,up.y,up.z);
}











