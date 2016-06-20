#include "main.hpp"
#include "camera.hpp"
#include "ball.hpp"
#include "RgbImage.h"
#include <cstdlib>

Camera mainCamera;
Ball ball;

bool ball_inside;

GLfloat worldLimitX = 100.0, worldLimitZ = 50.0;
GLfloat wScreen = 800.0, hScreen = 600.0;
GLfloat ambientColor[4] =  {0.8,0.8,0.8};
GLfloat directionVector[3];

GLfloat draw_interval = 1000.0 / 30.0;
GLfloat zoneRadius = 1.3f;
GLfloat arrowAngle = 30.0f;;
GLfloat strength = 1.0f;

int mode = CATCH_MODE;

GLfloat playerX, playerZ = 0;

GLuint  textures[8];
RgbImage imag;


bool keys[256];
bool leftKey = false, rightKey = false, upKey = false, downKey = false;

GLfloat distance(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);

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

  glGenTextures(1, &textures[5]); 
  glBindTexture(GL_TEXTURE_2D, textures[5]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("wall1.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[6]); 
  glBindTexture(GL_TEXTURE_2D, textures[6]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("wall2.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[7]); 
  glBindTexture(GL_TEXTURE_2D, textures[7]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_DECAL); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("wall3.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

}
void changeView(){
  playerX = mainCamera.x;
  playerZ = mainCamera.z;
  GLfloat radianAngle = (PI * -90) / 180.0f;
  GLfloat deltaX = (0 - ball.x);
  GLfloat deltaZ;
  if(ball.z < 0){
    deltaZ = (-16 - ball.z);
  }
  else{
    deltaZ = 16 - ball.z;
  }
  
  mainCamera.tX = ball.x + deltaX/2.0f;
  mainCamera.tY = ball.y;
  mainCamera.tZ = ball.z + deltaZ/2.0f;
  
  GLfloat auxX = (deltaX * cos(radianAngle) + deltaZ * sin(radianAngle));
  GLfloat auxZ = (-deltaX * sin(radianAngle) + deltaZ * cos(radianAngle));

  mainCamera.x = mainCamera.tX + auxX;
  mainCamera.y = 3.0f;
  mainCamera.z = mainCamera.tZ + auxZ;
}

void drawArrow(){
  glColor3f(1.0,1.0,1.0);
  GLfloat deltaX = (0 - ball.x);
  GLfloat deltaZ;
  if(ball.z < 0){
    deltaZ = (-15 - ball.z);
  }
  else{
    deltaZ = 15 - ball.z;
  }
  GLfloat magnitude = sqrt(pow(deltaX, 2.0f) + pow(deltaZ, 2.0f));
  GLfloat angleY = acos(deltaZ / magnitude);  

  
  glColor3f(0.3,0.6,2.0);
  glPushMatrix();
  glTranslatef(ball.x, ball.y, ball.z);
  GLfloat aux;
  if(ball.x > 0)
    aux = -angleY;
  else
    aux = angleY;
  
  glRotatef(aux * 180.0/PI,0,1,0);
  glRotatef(-arrowAngle,1,0,0);

  GLfloat rad = -arrowAngle * PI/180.0;
  directionVector[0] = sin(aux) * cos(rad);
  directionVector[1]= -sin(rad);
  directionVector[2] = cos(aux)*cos(rad);
  
  glBegin(GL_LINES);
  glVertex3f(0, 0, 0);
  glVertex3f(0, 0, strength);
  glEnd();
  glPopMatrix();

  glColor3f(1.0,0.0,0.0);
  /*glBegin(GL_LINES);
    glVertex3f(ball.x , ball.y, ball.y);*/
}

void lights(void){
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);
  GLfloat position[] = { mainCamera.x,1.8,mainCamera.z, 1.0};
  GLfloat direction[] = { 0.0, -1.0, 0.0 };
  GLfloat color[] =  {0.0,0.0,0.0,1.0};
  if(distance(ball.x, 0, ball.z, 0,0,15) < distance(mainCamera.x, 0, mainCamera.z, 0, 0, 15)){
    color[1] = 1.0;
  }
  else{
    color[0] = 1.0;
  }

  GLfloat angle = atan(zoneRadius/1.8f) * 180.0f/PI;
  
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0,GL_POSITION, position);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,color);
  GLfloat Foco_ak			= 1.0;
  GLfloat Foco_al			= 0.05f;
  GLfloat Foco_aq			= 0.0f;
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,	Foco_aq);

  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, angle);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, direction);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 3.0);
  if(mode == TURNING_MODE){
    glEnable(GL_LIGHT0);
  }
  else{
    glDisable(GL_LIGHT0);
  }
}

void init(void)
{
  glClearColor(1.0,1.0,1.0,1.0);
  glShadeModel(GL_SMOOTH);
  defineTextures(); 
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  lights();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
}


void DrawCircle(float cx, float cz, float r, int num_segments)
{
  
  glBegin(GL_POLYGON);
    for(int ii = 0; ii < num_segments; ii++)
    {
      float theta = 2.0f * PI * float(ii) / float(num_segments);//get the current angle
	
      float x = r * cosf(theta);//calculate the x component
      float z = r * sinf(theta);//calculate the y component
      
      glVertex3f(x + cx, 0.01f, z + cz);//output vertex

    }
    glEnd();
}

GLfloat distance(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2){
  return sqrt(pow(x2 - x1, 2.0f) + pow(y2 - y1, 2.0f) + pow(z2 - z1, 2.0f));
}



void changePosition(GLfloat x, GLfloat z){
  mainCamera.x = x;
  mainCamera.y = 1.8f;
  mainCamera.z = z;
  mainCamera.tX = 0;
  mainCamera.tY = 3.05;
  if(z <= 0){
    mainCamera.tZ = -15;
  }
  else{
    mainCamera.tZ = 15;
  }
  mode = CATCH_MODE;
  ball.locked = false;
  GLfloat deltaX = (mainCamera.tX - mainCamera.x);
  GLfloat deltaZ = (mainCamera.tZ - mainCamera.z);
  GLfloat magnitude = sqrt(pow(deltaX, 2.0f) + pow(deltaZ, 2.0f));
  ball.x = x + 2 * deltaX/magnitude;
  ball.z = z + 2 * deltaZ/magnitude;
  ball.y = 1.3;
  ball.vY = 0;
}

void handleKeys(){
  if(keys['w']){
    if(mode == CATCH_MODE){
      mainCamera.move(0);
    }
    else if(mode == ADJUST_MODE){
      arrowAngle++;
    }
  }
  if(keys['s'] && mode == ADJUST_MODE){
    arrowAngle--;
  }
  if(keys['a'] && mode == ADJUST_MODE){
    strength -= 0.01;
    if(strength<0.5) strength = 0.5;
  }
  if(keys['d'] && mode == ADJUST_MODE){
    strength+=0.01;
    if(strength>10) strength = 10;
  }
    
  if(keys['x'])
    mainCamera.move(180);
  if(leftKey){
    mainCamera.rotate(1, true);
  }
  if(rightKey){
    mainCamera.rotate(-1, true);
  }
  if(upKey){
    mainCamera.rotate(1, false);
  }
  if(downKey)
    mainCamera.rotate(-1, false);
}

void update(){
  handleKeys();
  ball.update();
  if(distance(mainCamera.x, 0, mainCamera.z, ball.x, 0, ball.z) < 1.0f){
    mode = TURNING_MODE;
  }
}


GLvoid resize(GLsizei width, GLsizei height)
{
  wScreen=width;
  hScreen=height;
  glViewport(0,0,width,height);
  glutPostRedisplay();
}

void shootBall(){
  strength/=4.0f;
  ball.move(directionVector[0]*strength, directionVector[1]*strength, directionVector[2]*strength);
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
    x + (radius * cos(i * twicePi / lineAmount)),y + (radius* sin(i * twicePi / lineAmount))
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
  glColor4f(1.0,1.0,0.0,1.0);
  glTranslatef(-9.5,0.0,3.5*side);
  
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();
  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,1.0);
  glTranslatef(-10.5,0.5,3.5*side);
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();

  glPushMatrix();
  glColor4f(1.0,1.0,0.0,1.0);
  glTranslatef(-11.5,0.0,3.5*side);
  for(i = 0; i < 10;i++){
    glTranslatef(0,0,1*side);
    glutSolidCube(1);

  } 
  glPopMatrix();


  glPushMatrix();
  glColor4f(1.0,1.0,0.0,1.0);
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
  glColor4f(1,0,0,1);
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

  glColor3f(1.0,1.0,1.0);
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(16.5,0,0);
  glBegin(GL_QUADS);
  glNormal3f(0.0f,1.0f,0.0f);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-2, 0, -23);
  glNormal3f(0.0f,1.0f,0.0f);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-2, 0, 16);
  glNormal3f(0.0f,1.0f,0.0f);
  glTexCoord2f(10.0f,10.0f); glVertex3f(2, 0, 16);
  glNormal3f(0.0f,1.0f,0.0f);
  glTexCoord2f(0.0f,10.0f); glVertex3f(2, 0, -23);
  glEnd();

  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D,0);
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);

  glPushMatrix();

  glTranslatef(-10.5,0,0);
  glColor3f(1,1,1);
  glBegin(GL_QUADS);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-2, 0, -16);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(2.0f,0.0f);glVertex3f(-2, 0, 16);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(2.0f,2.0f);glVertex3f(2, 0, 16);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,2.0f);glVertex3f(2, 0, -16);
  glEnd();

  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(0,0,18);
  glBegin(GL_QUADS);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-12.5, 0, -2);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-12.5, 0, 2);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(10.0f,10.0f); glVertex3f(18.5, 0, 2);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,10.0f); glVertex3f(18.5, 0, -2);
  glEnd();

  glPopMatrix();

  glPushMatrix();
  glTranslatef(0,0,-18);
  glBegin(GL_QUADS);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-12.5, 0, -4);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(10.0f,0.0f); glVertex3f(-12.5, 0, 2);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(10.0f,10.0f); glVertex3f(8.5, 0, 2);
  glNormal3f(0,1.0f,0);
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

void drawLights(int x, int z){

  glPushMatrix();
  glTranslatef(x, 0, z);

  glColor4f(1.0,1.0,0.0,1.0);
  glRotatef(-90,1,0,0);
  
  GLUquadric *quadric;
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,5,50,50);

  //glTranslatef(0,5,0);
  
  //gluCylinder(quadric,0.05,0.05,5,50,50);

  glPopMatrix();

}


void drawBullding(int x, int y, int z, int xi, int zi){

  int tex = (rand()%3)+4;

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[5]);

  glPushMatrix();
  glTranslatef(xi, y, zi);

   glBegin(GL_QUADS);               
      
      glVertex3f( x, y, -z);
      glVertex3f(-x, y, -z);
      glVertex3f(-x, y,  z);
      glVertex3f( x, y,  z);
 
      glVertex3f( x, -y,  z);
      glVertex3f(-x, -y,  z);
      glVertex3f(-x, -y, -z);
      glVertex3f( x, -y, -z);
 
      glVertex3f( x,  y, z);
      glVertex3f(-x,  y, z);
      glVertex3f(-x, -y, z);
      glVertex3f( x, -y, z);
 
      glVertex3f( x, -y, -z);
      glVertex3f(-x, -y, -z);
      glVertex3f(-x,  y, -z);
      glVertex3f( x,  y, -z);
 
      glVertex3f(-x,  y,  z);
      glVertex3f(-x,  y, -z);
      glVertex3f(-x, -y, -z);
      glVertex3f(-x, -y,  z);
 
      glVertex3f(x,  y, -z);
      glVertex3f(x,  y,  z);
      glVertex3f(x, -y,  z);
      glVertex3f(x, -y, -z);
    glEnd();
    
    glDisable(GL_TEXTURE_2D);
    int zaux = (-z)+1;
    int yaux = (-y)+3;
    while(yaux<(y)){
      zaux = (-z)+1;
      while(zaux < z){
      glShadeModel(GL_SMOOTH);
      glBegin(GL_QUADS);
      glColor3f(0.6, 0.6, 1);
      glVertex3f(-x-0.01,  yaux+0.5,  zaux+0.5);
      glVertex3f(-x-0.01,  yaux+0.5, zaux-0.5);
      glColor3f(1, 1, 1);
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
      glShadeModel(GL_SMOOTH);
      glBegin(GL_QUADS);
      glColor3f(0.6, 0.6, 1);
      glVertex3f(xaux+0.5,  yaux+0.5,-z-0.01);
      glVertex3f(xaux-0.5,  yaux+0.5,-z-0.01);
      glColor3f(1, 1, 1);
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
      glShadeModel(GL_SMOOTH);
      glBegin(GL_QUADS);
      glColor3f(0.6, 0.6, 1);
      glVertex3f(x+0.01,  yaux+0.5,  zaux-0.5);
      glVertex3f(x+0.01,  yaux+0.5, zaux+0.5);
      glColor3f(1, 1, 1);
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
      glShadeModel(GL_SMOOTH);
      glBegin(GL_QUADS);
      glColor3f(0.6, 0.6, 1);
      glVertex3f(xaux+0.5, yaux+0.5, z+0.01);
      glVertex3f(xaux-0.5, yaux+0.5, z+0.01);
      glColor3f(1, 1, 1);
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
  glNormal3f(0,1,0);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, 0);
  glBegin(GL_QUADS);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -23);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glNormal3f(0,1.0f,0);
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

  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix(); 
  glTranslatef(24.5, 0, 0);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -25);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 22);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 22);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -25);

  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix(); 
  glTranslatef(24.5, 0, 40);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -10);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -10);

  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix(); 
  glTranslatef(24.5, 0, -85);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -10);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -10);

  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix(); 
  glTranslatef(-19, 0, -85);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -10);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -10);

  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D); glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix(); 
  glTranslatef(-19, 0, 40);

  glBegin(GL_QUADS);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-4, 0, -10);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(20.0f,10.0f);glVertex3f(4, 0, 52);
  glNormal3f(0,1,0);
  glTexCoord2f(0.0f,10.0f);glVertex3f(4 , 0, -10);

  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  int i;
  glPushMatrix();
  glColor4f(1,1,1,1);
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
  glColor4f(1,1,1,1);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(20.5, 0, -25);
  glVertex3f(20.5, 0, 22);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,1);
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
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -23);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glNormal3f(0,1.0f,0);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -23);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glPushMatrix();
  glColor4f(1,1,1,1);
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
  glColor4f(1,1,1,1);
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
  glColor4f(1,1,1,1);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -25);
  glVertex3f(-14.5, 0, 22);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,1);
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
  glColor4f(1,1,1,1);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -25);
  glVertex3f(20.5, 0, -25);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,1);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, 22);
  glVertex3f(20.5, 0, 22);
  glEnd();
  glPopMatrix();
  
  /*ESTRADA FRONTAL*/
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(0, 0, -29);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-60.5, 0, -4);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-60.5, 0, 4);
  glTexCoord2f(20.0f,10.0f);glVertex3f(65.5, 0, 4);
  glTexCoord2f(0.0f,10.0f);glVertex3f(65.5 , 0, -4);
  glEnd();
  glPopMatrix();

  glDisable(GL_TEXTURE_2D);

  /*ESTRADA FRONTAL*/
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(0, 0, 26);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-60.5, 0, -4);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-60.5, 0, 4);
  glTexCoord2f(20.0f,10.0f);glVertex3f(65.5, 0, 4);
  glTexCoord2f(0.0f,10.0f);glVertex3f(65.5 , 0, -4);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);


  glPushMatrix();
  glColor4f(1,1,1,1);
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
  glColor4f(1,1,1,1);
  glTranslatef(-18.5, 0, 26);
  for(i = 0; i<13; i++){
    glBegin(GL_LINES);
    glVertex3f(1, 0, 0);
    glVertex3f(3, 0, 0);
    glEnd();
    glTranslatef(5, 0, 0);
  }
  glPopMatrix();
  /*CANTOS EXTERNOS*/
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(0, 0, -34);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-15, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-15, 0, 1);
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
  glTexCoord2f(0.0f,0.0f); glVertex3f(-15, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-15, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, 53);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 32);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 32);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(29.5, 0, 53);
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
  glTranslatef(-14, 0, 53);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 32);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 32);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-24, 0, 53);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -21);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 32);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 32);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -21);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, -55);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -33);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -33);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(29.5, 0, -55);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -33);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -33);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-14, 0, -55);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -33);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -33);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-24, 0, -55);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-1, 0, -33);
  glTexCoord2f(15.0f,0.0f);glVertex3f(-1, 0, 20);
  glTexCoord2f(15.0f,1.0f);glVertex3f(1, 0, 20);
  glTexCoord2f(0.0f,1.0f);glVertex3f(1, 0, -33);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-43, 0, -24);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-18.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-18.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(18.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(18.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-43, 0, -34);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-18.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-18.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-45, 0, 21);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-18.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-18.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(20.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(20.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(-45, 0, 31);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-18.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-18.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(22, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(22, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(43, 0, -24);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-12.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-12.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(28.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(28.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(43, 0, -34);
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

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(45, 0, 31);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-16.5, 0, -1);
  glTexCoord2f(0.5f,0.0f);glVertex3f(-16.5, 0, 1);
  glTexCoord2f(0.5f,17.0f);glVertex3f(22.5, 0, 1) ;
  glTexCoord2f(0.0f,17.0f);glVertex3f(22.5, 0, -1);
  glEnd();
  glPopMatrix();
  glDisable(GL_TEXTURE_2D);



  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(45, 0, 42);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-14.5, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(-43.5, 0, 42);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-14.5, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();


  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(45, 0, -85);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-14.5, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[0]);
  glPushMatrix();
  glTranslatef(-43.5, 0, -85);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-14.5, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-14.5, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

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
  glBindTexture(GL_TEXTURE_2D,0);
  glDisable(GL_TEXTURE_2D);



  glPushMatrix();
  glColor4f(1,1,1,1);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, -33);
  glVertex3f(20.5, 0, -33);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glColor4f(1,1,1,1);
  glLineWidth(7);
  glBegin(GL_LINES);
  glVertex3f(-14.5, 0, 30);
  glVertex3f(20.5, 0, 30);
  glEnd();
  glPopMatrix();


}

void drawField(){  
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glColor4f(0.2,0.2,0.2,1);
  //  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glBindTexture(GL_TEXTURE_2D, 0); 
  GLfloat num_pol = 200.0f;
  glNormal3f(0.0, 1.0, 0.0);
  for(GLfloat line = 0.0f; line< num_pol; line++){
    for(GLfloat col = 0.0f; col < num_pol; col++){
      glBegin(GL_POLYGON);
      glVertex3f(-8.5f + line* 17.0f/num_pol,0,  -16.0f + col*32.0f/num_pol);
      glVertex3f(-8.5f + (line+1)* 17.0f/num_pol,0, -16.0f + col*32.0f/num_pol);
      glVertex3f(-8.5f + (line+1)* 17.0f/num_pol,0, -16.0f + (col+1)*32.0f/num_pol);
      glVertex3f(-8.5f + line* 17.0f/num_pol,0, -16.0f + (col+1)*32.0f/num_pol);
      glEnd();
    }
  }
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

  
  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,1.0);
  glTranslatef(0.0,0.0,-15);
  glRotatef(-90,1,0,0);
  
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,2.9,50,50);
  glPopMatrix();
  

  /*tabela*/

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

  drawBullding(6, 9, 6, -33, -45);
  drawBullding(9, 11, 6, 45, 45);

  drawBullding(6, 12, 6, -33, 45);
  drawBullding(5, 7, 6, 38, -43);

  drawLights(8.5, 15.5);
  drawLights(-8.5, -15.5);
  drawLights(8.5, -15.5);
  drawLights(-8.5, 15.5);

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
  
  lights();
  glEnable(GL_LIGHTING);
  glPushMatrix();
  glPopMatrix();
  //  if(mode == ADJUST_MODE){
  drawArrow();
    //}
  if(mainCamera.z > 0){
    glPushMatrix();
    glEnable(GL_BLEND);
    glColor4f(0.1,0.1,0.1,0.5);
    glRotatef(-90,1,0,0);
    glTranslatef(0.0,0.0,(2.9+0.75));
    glBegin(GL_QUADS);
    glVertex3f(-1.5, 15, -0.75);
    glVertex3f(-1.5, 15, 0.75);
    glVertex3f(1.5, 15, 0.75);
    glVertex3f(1.5, 15, -0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glColor4f(0,1,0,0.5f);
    glRotatef(-90,1,0,0);
    glTranslatef(0.0,0.0,(2.9+0.75));
    glBegin(GL_QUADS);
    glVertex3f(-1.5, -15, -0.75);
    glVertex3f(-1.5, -15, 0.75);
    glVertex3f(1.5, -15, 0.75);
    glVertex3f(1.5, -15, -0.75);
    glEnd();
    glPopMatrix();

  }
  else{
    glPushMatrix();
    glColor4f(0,1,0,0.5f);
    glRotatef(-90,1,0,0);
    glTranslatef(0.0,0.0,(2.9+0.75));
    glBegin(GL_QUADS);
    glVertex3f(-1.5, -15, -0.75);
    glVertex3f(-1.5, -15, 0.75);
    glVertex3f(1.5, -15, 0.75);
    glVertex3f(1.5, -15, -0.75);
    glEnd();
    glPopMatrix();

    glPushMatrix();
    glEnable(GL_BLEND);
    glColor4f(0.1,0.1,0.1,0.5);
    glRotatef(-90,1,0,0);
    glTranslatef(0.0,0.0,(2.9+0.75));
    glBegin(GL_QUADS);
    glVertex3f(-1.5, 15, -0.75);
    glVertex3f(-1.5, 15, 0.75);
    glVertex3f(1.5, 15, 0.75);
    glVertex3f(1.5, 15, -0.75);
    glEnd();
    glPopMatrix();

  }
  glDisable(GL_BLEND);
  
  glutSwapBuffers();
  
}



void keyboard(unsigned char key, int x, int y){
  GLfloat distanceToBall = distance(mainCamera.x, 0, mainCamera.z, ball.x, 0, ball.z);
  if(key == 'r'){
    GLfloat _x = random(-7.5, 7.5);
    GLfloat _z = random(0, 13);
    changePosition(_x,_z);
    return;
  }
  if(key == 'a' && distanceToBall <= zoneRadius){
     GLfloat radianAngle = (PI * 0.8f) / 180.0f;
     GLfloat deltaX = (ball.x - mainCamera.x);
     GLfloat deltaZ = (ball.z - mainCamera.z);
     GLfloat finalX= mainCamera.x + (deltaX * cos(radianAngle) + deltaZ * sin(radianAngle));
     GLfloat finalZ = mainCamera.z + (-deltaX * sin(radianAngle) + deltaZ * cos(radianAngle));
     ball.move(finalX - ball.x,  -0.15, finalZ - ball.z);
  }
  else if(key == 'd' && distanceToBall <= zoneRadius){
    GLfloat radianAngle = (PI * -0.8f) / 180.0f;
    GLfloat deltaX = (ball.x - mainCamera.x);
    GLfloat deltaZ = (ball.z - mainCamera.z);
    GLfloat finalX= mainCamera.x + (deltaX * cos(radianAngle) + deltaZ * sin(radianAngle));
    GLfloat finalZ = mainCamera.z + (-deltaX * sin(radianAngle) + deltaZ * cos(radianAngle));
    ball.move(finalX - ball.x,  -0.15 , finalZ - ball.z);
  }
  else if(key == 's'  && distanceToBall <= zoneRadius){
    ball.move(0,-0.15,0);
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
  if(key == ' ' && mode == ADJUST_MODE){
    ball.locked = false;
    shootBall();
    mode = -1;
  }
  if(key == ' ' && mode == TURNING_MODE){
    if(distance(ball.x, 0, ball.z, 0,0,15) < distance(mainCamera.x, 0, mainCamera.z, 0, 0, 15)){
      ball.locked = true;
      mode = ADJUST_MODE;
      changeView();
    }
  }

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
