#ifndef CAMERA_HPP
#define CAMERA_HPP


#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include<cmath>
#include<stdio.h>

#include "main.hpp"

using namespace std;

class Camera {
public:
  Camera();
  ~Camera();
  GLfloat x = 5, y = 1.8, z = 4;
  GLfloat vel = 0.1;
  GLfloat tX = 0.0, tY = 1.8, tZ = 0.0;
  int mode = 0;
  void move(GLfloat angle);
  void rotate(GLfloat angle, bool horizontal);
  void draw();
};

#endif
