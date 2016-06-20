#ifndef BALL_HPP
#define BALL_HPP


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<cmath>
#include<stdio.h>
#include "RgbImage.h"

using namespace std;

class Ball {
public:
  Ball();
  ~Ball();
  GLfloat x = 0, y = 1.8, z = 0;
  GLfloat vel = 0.1;
  GLfloat vX = 0.0, vY = 0.0, vZ = 0.0;
  GLfloat radius = 0.1215;
  bool locked = false;
  GLuint texture;
  RgbImage imag;
  void move(GLfloat velX, GLfloat velY, GLfloat velZ);
  void update();
  void draw();
  void loadTexture();
};

#endif
