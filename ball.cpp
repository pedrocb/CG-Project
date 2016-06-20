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
    if(y < radius){
      y = radius;
      vY*=-0.800f;
      vZ*=0.98f;
      vX*=0.98f;
    }
    if(x - radius< -7.5){
      x = -7.5 + radius + 2;
      vX*= 0.0f;
      vY*= 0.0f;
      vZ*= 0.0f;
    }
    if(x + radius > 7.5){
      x = 7.5 - radius;
      vX*= 0.0f;
      vY*= 0.0f;
      vZ*= 0.0f;
    }
    if(z + radius > 15){
      z = 15 - radius;
      vX*= 0.500f;
      vZ*= -0.500f;
      vY*= 0.700f;
    }
    if(z - radius < 0){
      z = radius;
      vX= 0.0f;
      vZ= 0.0f;
      vY= 0.0f;
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
