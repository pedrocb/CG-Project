#include "ball.hpp"

Ball::Ball(){}

Ball::~Ball(){}

void Ball::move(GLfloat velX, GLfloat velY, GLfloat velZ){
  vX = velX;
  vY = velY;
  vZ = velZ;
}

void Ball::update(){
  if(!locked){
    vY -= 0.015833f; //Gravity
    x+=vX;
    y+=vY;
    z+=vZ;
    if(y <= radius){
      y = radius;
      vY*= -1.0f;
      vY*=0.800f;
    }
  }
}

void Ball::draw(){
  glPushMatrix();
  glColor3f(1.0,1.0,0.0);
  glTranslatef(x,y,z);
  glutSolidSphere(radius, 50, 50);
  glPopMatrix();
}
