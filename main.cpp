#include "main.hpp"
#include "camera.hpp"
#include "ball.hpp"
#include "RgbImage.h"


Camera mainCamera;
Ball ball;

GLfloat worldLimitX = 100.0, worldLimitZ = 50.0;
GLfloat wScreen = 800.0, hScreen = 600.0;
GLfloat ambientColor[4] =  {0.7,0.7,0.7,1.0};

GLfloat draw_interval = 1000.0 / 30.0;

GLuint  textures[5];
RgbImage imag;


bool keys[256];
bool leftKey = false, rightKey = false, upKey = false, downKey = false;

GLfloat random(GLfloat minimo, GLfloat maximo){	
  GLfloat y;
  y = rand()%1000;
  return (minimo+ 0.001*y*(maximo-minimo));
}
void defineTextures(){

  glGenTextures(1, &textures[0]); 
  glBindTexture(GL_TEXTURE_2D, textures[0]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("grass.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());



  glGenTextures(1, &textures[1]); 
  glBindTexture(GL_TEXTURE_2D, textures[1]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("sand.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[2]); 
  glBindTexture(GL_TEXTURE_2D, textures[2]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("cim.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[3]); 
  glBindTexture(GL_TEXTURE_2D, textures[3]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("calcada.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[4]); 
  glBindTexture(GL_TEXTURE_2D, textures[4]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("pista.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());


}

void initLights(void){
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);
}

void init(void)
{
  glClearColor(1.0,1.0,1.0,1.0);
  glShadeModel(GL_SMOOTH);
  defineTextures(); 
  glEnable(GL_TEXTURE_2D);
  
  initLights();
  glEnable(GL_LIGHTING);
  glEnable(GL_DEPTH_TEST);
  glEnable(GL_COLOR_MATERIAL);
}

GLfloat distance(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2){
  return sqrt(pow(x2 - x1, 2.0f) + pow(y2 - y1, 2.0f) + pow(z2 - z1, 2.0f));
}



void changePosition(GLfloat x, GLfloat z){
  mainCamera.x = x;
  mainCamera.z = z;

  mainCamera.tX = 0;
  mainCamera.tY = 3.05;
  if(z <= 0){
    mainCamera.tZ = -15;
  }
  else{
    mainCamera.tZ = 15;
  }

  GLfloat deltaX = (mainCamera.tX - mainCamera.x);
  GLfloat deltaZ = (mainCamera.tZ - mainCamera.z);
  GLfloat magnitude = sqrt(pow(deltaX, 2.0f) + pow(deltaZ, 2.0f));
  ball.x = x + 2 * deltaX/magnitude;
  ball.z = z + 2 * deltaZ/magnitude;
  ball.y = 1.3;
  ball.vY = 0;
}

void handleKeys(){
  if(keys['w'])
    mainCamera.move(0);
  if(keys['s'])
    mainCamera.move(180);
  if(leftKey)
    mainCamera.rotate(1, true);
  if(rightKey)
    mainCamera.rotate(358, true);
  if(upKey)
    mainCamera.rotate(2, false);
  if(downKey)
    mainCamera.rotate(-1, false);
}

void update(){
  handleKeys();
  ball.update();
}


GLvoid resize(GLsizei width, GLsizei height)
{
  wScreen=width;
  hScreen=height;
  glViewport(0,0,width,height);
  glutPostRedisplay();
}




void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius, int rot){
  glPushMatrix();

  glRotatef(-90,rot,0,0);
  int i;
  int lineAmount = 100; //# of triangles used to draw circle
  //GLfloat radius = 0.8f; //radius
  GLfloat twicePi = 2.0f * PI;
  glBegin(GL_LINE_STRIP);
  for(i = 0; i <= lineAmount/2;i++) {
    glVertex2f(
    x + (radius * cos(i * twicePi / lineAmount)),
    y + (radius* sin(i * twicePi / lineAmount))
    );
  }
  glEnd();
  glPopMatrix();
}


void drawFieldLines(){

  glLineWidth(20);
  glPushMatrix();
  glColor3f(1,0,0);
  glBegin(GL_LINES);
  glVertex3f(-6.1, 0, -15);
  glVertex3f(-6.1, 0, -12.0);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(6.1, 0, -15);
  glVertex3f(6.1, 0, -12.0);
  glEnd();
  glPopMatrix();

  drawHollowCircle(0,-12, 6.1, -1);
  drawHollowCircle(0,0, 1.8,-1);
  drawHollowCircle(0,-9.2, 1.8,-1);

  /*garrafao*/
  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(2.45, 0, -9.2);
  glVertex3f(-2.45, 0, -9.2);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(2.45, 0, -15);
  glVertex3f(2.45, 0, -9.2);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(-2.45, 0, -15);
  glVertex3f(-2.45, 0, -9.2);
  glEnd();
  glPopMatrix();

  /*Linha central*/
  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(7.5, 0, 0);
  glVertex3f(-7.5, 0, 0);
  glEnd();
  glPopMatrix();

  /*2 METADE*/
  glPushMatrix();
  glColor3f(1,0,0);
  glLineWidth(20);
  glBegin(GL_LINES);
  glVertex3f(-6.1, 0, 15);
  glVertex3f(-6.1, 0, 12.0);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(6.1, 0, 15);
  glVertex3f(6.1, 0, 12.0);
  glEnd();
  glPopMatrix();

  drawHollowCircle(0,-12, 6.1, 1);
  drawHollowCircle(0,0, 1.8,1);
  drawHollowCircle(0,-9.2, 1.8,1);

  /*garrafao*/
  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(2.45, 0, 9.2);
  glVertex3f(-2.45, 0, 9.2);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(2.45, 0, 15);
  glVertex3f(2.45, 0, 9.2);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(-2.45, 0, 15);
  glVertex3f(-2.45, 0, 9.2);
  glEnd();
  glPopMatrix();

  /*Linhas exteriores*/

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(7.5, 0, -15);
  glVertex3f(7.5, 0, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(-7.5, 0, -15);
  glVertex3f(-7.5, 0, 15);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(-7.5, 0, 15);
  glVertex3f(7.5, 0, 15);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glBegin(GL_LINES);
  glLineWidth(10);
  glVertex3f(-7.5, 0, -15);
  glVertex3f(7.5, 0, -15);
  glEnd();
  glPopMatrix();
}

void drawSits(int side){

  int i;
  glPushMatrix();
  glColor4f(1.0,1.0,0.0,0.0);
  glTranslatef(-9.5,0.0,3.5*side);
  
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();
  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,0.0);
  glTranslatef(-10.5,0.5,3.5*side);
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();

  glPushMatrix();
  glColor4f(1.0,1.0,0.0,0.0);
  glTranslatef(-11.5,0.0,3.5*side);
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();


  glPushMatrix();
  glColor4f(1.0,1.0,0.0,0.0);
  glTranslatef(-11.5,1.0,3.5*side);
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();

}


void drawPaisagem(){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[4]);
  glPushMatrix();
  glTranslatef(11.5,0,0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-3, 0, -16);
  glTexCoord2f(20.0f,0.0f); glVertex3f(-3, 0, 16);
  glTexCoord2f(20.0f,10.0f); glVertex3f(3, 0, 16);
  glTexCoord2f(0.0f,10.0f); glVertex3f(3, 0, -16);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glTranslatef(11.5,0,0);
  glLineWidth(10);
  glColor4f(1,0,0,0);
  glBegin(GL_LINES);
  glVertex3f(-1.5, 0, -16);
  glVertex3f(-1.5, 0, 16);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(1.5, 0, -16);
  glVertex3f(1.5, 0, 16);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(-3, 0, -16);
  glVertex3f(-3, 0, 16);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(3, 0, -16);
  glVertex3f(3, 0, 16);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(0, 0, -16);
  glVertex3f(0, 0, 16);
  glEnd();


  glBegin(GL_LINES);
  glVertex3f(3, 0, -16);
  glVertex3f(-3, 0, -16);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(3, 0, 16);
  glVertex3f(-3, 0, 16);
  glEnd();

  glBegin(GL_LINES);
  glVertex3f(3, 0, -15);
  glVertex3f(-3, 0, -15);
  glEnd();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[1]);

  glTranslatef(0,0,-19);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-3, 0, -3);
  glTexCoord2f(2.0f,0.0f); glVertex3f(-3, 0, 3);
  glTexCoord2f(2.0f,2.0f); glVertex3f(3, 0, 3);
  glTexCoord2f(0.0f,2.0f); glVertex3f(3, 0, -3);
  glEnd();
  

  glPopMatrix();

  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(16.5,0,0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-2, 0, -23);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-2, 0, 16);
  glTexCoord2f(10.0f,10.0f); glVertex3f(2, 0, 16);
  glTexCoord2f(0.0f,10.0f); glVertex3f(2, 0, -23);
  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);

  glPushMatrix();

  glTranslatef(-10.5,0,0);
  glColor4f(0,0,0,0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-2, 0, -16);
  glTexCoord2f(2.0f,0.0f);glVertex3f(-2, 0, 16);
  glTexCoord2f(2.0f,2.0f);glVertex3f(2, 0, 16);
  glTexCoord2f(0.0f,2.0f);glVertex3f(2, 0, -16);
  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(0,0,18);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-12.5, 0, -2);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-12.5, 0, 2);
  glTexCoord2f(10.0f,10.0f); glVertex3f(18.5, 0, 2);
  glTexCoord2f(0.0f,10.0f); glVertex3f(18.5, 0, -2);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,0,-18);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-12.5, 0, -4);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-12.5, 0, 2);
  glTexCoord2f(10.0f,10.0f); glVertex3f(8.5, 0, 2);
  glTexCoord2f(0.0f,10.0f); glVertex3f(8.5, 0, -4);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,0,-22.5);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-12.5, 0, -0.5);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-12.5, 0, 0.5);
  glTexCoord2f(10.0f,10.0f); glVertex3f(14.5, 0, 0.5);
  glTexCoord2f(0.0f,10.0f); glVertex3f(14.5, 0, -0.5);
  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  drawSits(-1);
  drawSits(1);
}


void drawBullding(int x, int y, int z, int xi, int zi){

  glPushMatrix();
  glTranslatef(xi, y, zi);

   glBegin(GL_QUADS);                // Begin drawing the color cube with 6 quads
      // Top face (y = 1.0f)
      // Define vertices in counter-clockwise (CCW) order with normal pointing out
      glColor3f(0.0f, 1, 0);     // Green
      glVertex3f( x, y, -z);
      glVertex3f(-x, y, -z);
      glVertex3f(-x, y,  z);
      glVertex3f( x, y,  z);
 
      // Bottom face (y = -1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Orange
      glVertex3f( x, -y,  z);
      glVertex3f(-x, -y,  z);
      glVertex3f(-x, -y, -z);
      glVertex3f( x, -y, -z);
 
      // Front face  (z = 1.0f)
      glColor3f(1.0f, 0.0f, 0.0f);     // Red
      glVertex3f( x,  y, z);
      glVertex3f(-x,  y, z);
      glVertex3f(-x, -y, z);
      glVertex3f( x, -y, z);
 
      // Back face (z = -1.0f)
      glColor3f(1.0f, 1.0f, 0.0f);     // Yellow
      glVertex3f( x, -y, -z);
      glVertex3f(-x, -y, -z);
      glVertex3f(-x,  y, -z);
      glVertex3f( x,  y, -z);
 
      // Left face (x = -1.0f)
      glColor3f(0.0f, 0.0f, 1.0f);     // Blue
      glVertex3f(-x,  y,  z);
      glVertex3f(-x,  y, -z);
      glVertex3f(-x, -y, -z);
      glVertex3f(-x, -y,  z);
 
      // Right face (x = 1.0f)
      glColor3f(1.0f, 0.5f, 0.0f);     // Magenta
      glVertex3f(x,  y, -z);
      glVertex3f(x,  y,  z);
      glVertex3f(x, -y,  z);
      glVertex3f(x, -y, -z);
    glEnd();

    int i, j;

    glColor3f(1.0f, 0.0f, 1.0f);
    int zaux = (-z)+1;
    int yaux = (-y)+3;
    while(yaux<(y)){
      zaux = (-z)+1;
      while(zaux < z){

      glBegin(GL_QUADS);
      glVertex3f(-x-0.01,  yaux+0.5,  zaux+0.5);
      glVertex3f(-x-0.01,  yaux+0.5, zaux-0.5);
      glVertex3f(-x-0.01, yaux-0.5, zaux-0.5);
      glVertex3f(-x-0.01, yaux-0.5,  zaux+0.5);
      glEnd();
      zaux += 2;
      }
    
      yaux += 2;
    }

    int xaux = (-x)+1;
    yaux = (-y)+3;
    while(yaux<(y)){
      xaux = (-x)+1;
      while(xaux < x){

      glBegin(GL_QUADS);
      glVertex3f(xaux+0.5,  yaux+0.5,-z-0.01);
      glVertex3f(xaux-0.5,  yaux+0.5,-z-0.01);
      glVertex3f(xaux-0.5, yaux-0.5,-z-0.01);
      glVertex3f(xaux+0.5, yaux-0.5,-z-0.01);
      glEnd();
      xaux += 2;
      }
    
      yaux += 2;
    }

    zaux = (z)-1;
    yaux = (-y)+3;
    while(yaux<(y)){
      while(zaux > -z){

      glBegin(GL_QUADS);
      glVertex3f(x+0.01,  yaux+0.5,  zaux-0.5);
      glVertex3f(x+0.01,  yaux+0.5, zaux+0.5);
      glVertex3f(x+0.01, yaux-0.5, zaux+0.5);
      glVertex3f(x+0.01, yaux-0.5,  zaux-0.5);
      glEnd();
      zaux -= 2;
      }
    
      zaux = (z)-1;
      yaux += 2;
    }

    xaux = (x)-1;
    yaux = (-y)+3;
    while(yaux<(y)){
      while(xaux > -x){

      glBegin(GL_QUADS);
      glVertex3f(xaux+0.5, yaux+0.5, z+0.01);
      glVertex3f(xaux-0.5, yaux+0.5, z+0.01);
      glVertex3f(xaux-0.5, yaux-0.5, z+0.01);
      glVertex3f(xaux+0.5, yaux-0.5, z+0.01);
      glEnd();
      xaux -= 2;
      }
    
      xaux = (x)-1;
      yaux += 2;
    }

  glPopMatrix();


}

void drawRoad(){
  /*PASSEIO*/
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -23);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -23);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(20.5, 0, -25);
  glVertex3f(20.5, 0, 22);
  glEnd();
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(24.5, 0, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -25);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 22);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 22);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -25);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  int i;
  glPushMatrix();
  glColor4f(1,1,1,0);
  glTranslatef(24.5, 0, -23);
  for(i = 0; i<9; i++){
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 3);
    glEnd();
    glTranslatef(0, 0, 5);
  }
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(29.5, 0, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -25);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 22);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 22);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -25);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(20.5, 0, -25);
  glVertex3f(20.5, 0, 22);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(28.5, 0, -25);
  glVertex3f(28.5, 0, 22);
  glEnd();
  glPopMatrix();

  /*PASSEIO*/
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-13.5, 0, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -23);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -23);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -25);
  glVertex3f(-14.5, 0, 22);
  glEnd();
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(-18.5, 0, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -25);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 22);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 22);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -25);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,0);
  glTranslatef(-18.5, 0, -23);
  for(i = 0; i<9; i++){
    glBegin(GL_LINES);
    glVertex3f(0, 0, 1);
    glVertex3f(0, 0, 3);
    glEnd();
    glTranslatef(0, 0, 5);
  }
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-23.5, 0, 0);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -25);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 22);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 22);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -25);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -25);
  glVertex3f(-14.5, 0, 22);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-22.5, 0, -25);
  glVertex3f(-22.5, 0, 22);
  glEnd();
  glPopMatrix();

   /*PASSEIO*/
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(0, 0, -24);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(0, 0, 21);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -25);
  glVertex3f(20.5, 0, -25);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, 22);
  glVertex3f(20.5, 0, 22);
  glEnd();
  glPopMatrix();
  

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(0, 0, -29);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-45.5, 0, -4);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-45.5, 0, 4);
  glTexCoord2f(20.0f,10.0f);glVertex3f(50.5, 0, 4);
  glTexCoord2f(0.0f,10.0f);glVertex3f(50.5 , 0, -4);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(0, 0, 26);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-45.5, 0, -4);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-45.5, 0, 4);
  glTexCoord2f(20.0f,10.0f);glVertex3f(50.5, 0, 4);
  glTexCoord2f(0.0f,10.0f);glVertex3f(50.5 , 0, -4);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glPushMatrix();
  glColor4f(1,1,1,0);
  glTranslatef(-18.5, 0, -29);
  for(i = 0; i<13; i++){
    glBegin(GL_LINES);
    glVertex3f(1, 0, 0);
    glVertex3f(3, 0, 0);
    glEnd();
    glTranslatef(5, 0, 0);
  }
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,0);
  glTranslatef(-18.5, 0, 26);
  for(i = 0; i<13; i++){
    glBegin(GL_LINES);
    glVertex3f(1, 0, 0);
    glVertex3f(3, 0, 0);
    glEnd();
    glTranslatef(5, 0, 0);
  }
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(0, 0, -34);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(0, 0, 31);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, 52);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 22);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 22);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-14, 0, 52);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 22);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 22);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, -55);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 22);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 22);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-14, 0, -55);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 22);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 22);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-43, 0, -24);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-45, 0, 21);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(43, 0, -24);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(45, 0, 21);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-14.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);




  /*CANTEIRO DE RELVA*/

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(0, 0, 42);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -85);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(44, 0, -14);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13.5, 0, -9);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13.5, 0, 34);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 34);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -9);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-43, 0, -14);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13.5, 0, -9);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13.5, 0, 34);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 34);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -9);
  glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);



  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -33);
  glVertex3f(20.5, 0, -33);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,0);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, 30);
  glVertex3f(20.5, 0, 30);
  glEnd();
  glPopMatrix();


}

void drawField(){
  glPushMatrix();
  glColor3f(1,1,1);
  
  glBegin(GL_QUADS);  
  glVertex3f(-8.5, 0, -16);
  glVertex3f(-8.5, 0, 16);
  glVertex3f(8.5, 0, 16);
  glVertex3f(8.5, 0, -16);
  glEnd();
  
  glPopMatrix();

  drawFieldLines();
  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,1.0);
  glTranslatef(0.0,0.0,15);
  glRotatef(-90,1,0,0);
  
  GLUquadric *quadric;
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,2.9,50,50);
  glPopMatrix();
  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,1.0);
  glTranslatef(0.0,0.0,-15);
  glRotatef(-90,1,0,0);
  
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,2.9,50,50);
  glPopMatrix();

  /*tabela*/
  glPushMatrix();

  glColor4f(1,1,1,1);
  glRotatef(-90,1,0,0);
  glTranslatef(0.0,0.0,(2.9+0.75));
  glBegin(GL_QUADS);
  glVertex3f(-1.5, 15, -0.75);
  glVertex3f(-1.5, 15, 0.75);
  glVertex3f(1.5, 15, 0.75);
  glVertex3f(1.5, 15, -0.75);
  glEnd();
  glPopMatrix();

  /*quadrado tabela*/
  glPushMatrix();
  glColor4f(1,0,0,1);
  glLineWidth(5);
  glRotatef(-90,1,0,0);
  glTranslatef(0.0,0.0,(2.9+0.375));
  glBegin(GL_LINES);
  glVertex3f(-0.3, 15, 0.225);
  glVertex3f(-0.3, 15, -0.225);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(-0.3, 15, -0.225);
  glVertex3f(0.3, 15, -0.225);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0.3, 15, -0.225);
  glVertex3f(0.3, 15, 0.225);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(-0.3, 15, 0.225);
  glVertex3f(0.3, 15, 0.225);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glTranslatef(0, (2.9+0.15),-14.65);
  drawHollowCircle(0, 0, 0.35, 1);
  drawHollowCircle(0, 0, 0.35, -1);
	glPopMatrix();

  /*2tabela*/
  glPushMatrix();

  glColor4f(1,1,1,1);
  glRotatef(-90,1,0,0);
  glTranslatef(0.0,0.0,(2.9+0.75));
  glBegin(GL_QUADS);
  glVertex3f(-1.5, -15, -0.75);
  glVertex3f(-1.5, -15, 0.75);
  glVertex3f(1.5, -15, 0.75);
  glVertex3f(1.5, -15, -0.75);
  glEnd();
  glPopMatrix();

  /*quadrado tabela*/
  glPushMatrix();
  glColor4f(1,0,0,1);
  glLineWidth(5);
  glRotatef(-90,1,0,0);
  glTranslatef(0.0,0.0,(2.9+0.375));
  glBegin(GL_LINES);
  glVertex3f(-0.3, -15, 0.225);
  glVertex3f(-0.3, -15, -0.225);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(-0.3, -15, -0.225);
  glVertex3f(0.3, -15, -0.225);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(0.3, -15, -0.225);
  glVertex3f(0.3, -15, 0.225);
  glEnd();
  glBegin(GL_LINES);
  glVertex3f(-0.3, -15, 0.225);
  glVertex3f(0.3, -15, 0.225);
  glEnd();
  glPopMatrix();


  glPushMatrix();
  glTranslatef(0, (2.9+0.15),14.65);
  drawHollowCircle(0, 0, 0.35, 1);
  drawHollowCircle(0, 0, 0.35, -1);
  glPopMatrix();
  drawPaisagem();

  drawBullding(4, 9, 5, 36, 13);
  drawBullding(9, 9, 6, -36, -15);

  drawBullding(4, 9, 6, 36, -6);
  drawBullding(9, 9, 6, -36, 10);

  drawBullding(4, 9, 6, -8, -45);
  drawBullding(9, 11, 6, 7, 45);

  drawBullding(6, 12, 6, 12, -45);
  drawBullding(3, 7, 6, -9, 45);

  drawRoad();
}

void draw(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

  //Perspective
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, wScreen/hScreen, 0.1, 50.0);


  mainCamera.draw();

  drawField();
  ball.draw();
  
  glutSwapBuffers();

}

void keyboard(unsigned char key, int x, int y){
  if(key == 'r'){
    GLfloat _x = random(-7.5, 7.5);
    GLfloat _z = random(-7.5, 7.5);
    changePosition(_x,_z);
    return;
  }
  if(key == 'e'){
    ball.move(0,-0.08,0);
  }
  keys[key] = true;
}


void keyboard2Up(int key, int x, int y){
  if(key == GLUT_KEY_LEFT){
    leftKey = false;
  }
  if(key == GLUT_KEY_RIGHT){
    rightKey = false;
  }
  if(key == GLUT_KEY_UP){
    upKey = false;
  }
  if(key == GLUT_KEY_DOWN){
    downKey = false;
  }

}

void keyboard2(int key, int x, int y){
  if(key == GLUT_KEY_LEFT){
    leftKey = true;
  }
  if(key == GLUT_KEY_RIGHT){
    rightKey = true;
  }
  if(key == GLUT_KEY_UP){
    upKey = true;
  }
  if(key == GLUT_KEY_DOWN){
    downKey = true;
  }
}

void timer(int) {
  update();
  glutPostRedisplay();
  glutTimerFunc(draw_interval, timer, 0);
}

void keyboardUp(unsigned char key, int x, int y){
  keys[key] = false;
}

int main(int argc, char** argv){

  glutInit(&argc, argv);
  glutInitDisplayMode (GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH );
  glutInitWindowSize (1200.0, 900.0); 
  glutInitWindowPosition (400, 100); 
  glutCreateWindow ("Projeto de CG");
  init();
  
  glutReshapeFunc(resize);
  glutDisplayFunc(draw); 
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(keyboard2);
  glutSpecialUpFunc(keyboard2Up);
  glutKeyboardUpFunc(keyboardUp);

  glutTimerFunc(draw_interval, timer, 0);
  glutMainLoop();

  return 0;
}
