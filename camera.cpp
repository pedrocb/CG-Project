#include "camera.hpp"

Camera::Camera(){}

Camera::~Camera(){}

void Camera::draw(){
  gluLookAt(x, y, z, tX, tY, tZ, 0, 1, 0);
}

void Camera::move(GLfloat angle){
  GLfloat deltaX = (tX - x);
  GLfloat deltaZ = (tZ - z);
  GLfloat radianAngle = (PI * angle) / 180.0f;
  GLfloat new_vecX = deltaX * cos(radianAngle) + deltaZ * sin(radianAngle);
  GLfloat new_vecZ = -deltaX * sin(radianAngle) + deltaZ * cos(radianAngle);
  
  GLfloat magnitude = sqrt(pow(deltaX, 2.0f) + pow(deltaZ, 2.0f));
  GLfloat auxX = vel * new_vecX/magnitude;
  GLfloat auxZ = vel * new_vecZ/magnitude;
  x += auxX;
  z += auxZ;
  
  tX += auxX;
  tZ += auxZ;
}

void Camera::rotate(GLfloat angle, bool horizontal){
  GLfloat radianAngle = (PI * angle) / 180.0f;
  GLfloat deltaX = (tX - x);
  GLfloat deltaZ = (tZ - z);
  if(horizontal){
    tX = x + (deltaX * cos(radianAngle) + deltaZ * sin(radianAngle));
    tZ = z + (-deltaX * sin(radianAngle) + deltaZ * cos(radianAngle));
    
  }
  else{
    tY += angle; //Mudar  
  }
}
