#include "ball.hpp"

Ball::Ball(){}

Ball::~Ball(){}

void Ball::move(GLfloat velX, GLfloat velY, GLfloat velZ){
  vX = velX;
  vY = velY;
  vZ = velZ;
}

void Ball::loadTexture(){  
  glGenTextures(1, &texture); 
  glBindTexture(GL_TEXTURE_2D, texture); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("sand.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
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
      x = 7.5 - radius - 2;
      vX*= 0.0f;
      vY*= 0.0f;
      vZ*= 0.0f;
    }
    if(z + radius > 15){
      if(y + radius < 4.4f){
	z = 15 - radius;
	vX*= 0.500f;
	vZ*= -0.500f;
	vY*= 0.700f;
      }
      
      //x 0 z= 14.65
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
  glColor3f(1.0,0.46,0.0);
  glTranslatef(x,y,z);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, texture);
  GLUquadric* barra;
  barra = gluNewQuadric();
  gluQuadricDrawStyle ( barra, GLU_FILL   );
  gluQuadricNormals   ( barra, GLU_SMOOTH );
  gluQuadricTexture   ( barra, GL_TRUE    );

  glutSolidSphere(radius, 50, 50);
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
}
