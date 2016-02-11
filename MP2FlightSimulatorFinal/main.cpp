//
//  main.cpp
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
#include "mountain.cpp"
#include "Camera.cpp"
#include <iostream>

int FPS = 60;
float sun = 1; //position of sun;
float dSun = 0.01;
float sunsetHeight = 0.5;
float radiansToDegrees = 57.2957795;
GLfloat day[] = {0.3, 0.5, 1.0, 1.0};

void init(){
    glShadeModel(GL_SMOOTH);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);
    camera_init();
    mountain_init();
}

void display(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glColor3f(1.0, 1.0, 0.0);
    
    update_view();
    mountain_display();
    
    glTranslatef(5, 1, 0);
    GLfloat sunAmbient[] = {0.5,0.5,0.5,1};
    float sunIntensity = sin(sun)*10;
    GLfloat sunColor[] = {sunIntensity/2, sunIntensity/2, sunIntensity/2, 1};
    GLfloat sunPos[] = {1,1,1,0.0};
    
    glLightfv(GL_LIGHT0, GL_POSITION, sunPos);
    glLightfv(GL_LIGHT0, GL_AMBIENT, sunAmbient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, sunColor);
    glLightfv(GL_LIGHT0, GL_SPECULAR, sunColor);
    
    GLfloat sunamb[] = {1.0,1.0,1.0,1.0};

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, sunamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, sunamb);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, sunamb);
    glMaterialf(GL_FRONT_AND_BACK, GL_SHININESS, 0.0);
    
    
    glEnd();
    glFlush();
    glutSwapBuffers();
    glutPostRedisplay();
    
}

void reshape(int w, int h){
    float aspectRatio = ((float)w)/h;
    glViewport (0, 0, (GLsizei) w, (GLsizei) h);
    glMatrixMode (GL_PROJECTION);
    glLoadIdentity ();
    gluPerspective(90.0,aspectRatio,0.01,10.0);
    glMatrixMode (GL_MODELVIEW);
}

void keyboard(unsigned char key, int x, int y){
    mountain_keyboard(key, x, y);
    camera_keyboard(key,x, y);
}

void keyboard_up(unsigned char key, int x, int y){
    camera_keyboard_up(key, x, y);
}

void timer(int v){
    camera_timer(v);
    glClearColor(day[0], day[1], day[2], 1.0);
    glutPostRedisplay();
    glutTimerFunc(1000/FPS, timer, v);
}


int main(int argc, char * argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (500, 500);
    glutInitWindowPosition (100, 100);
    glutCreateWindow (argv[0]);
    init ();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutKeyboardUpFunc(keyboard_up);
    glutTimerFunc(100, timer, FPS);
    glutMainLoop();
    return 0;
}
