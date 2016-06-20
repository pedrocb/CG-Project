#include "main.hpp"
#include "camera.hpp"
#include "ball.hpp"
#include "render.hpp"
#include <cstdlib>

Camera mainCamera;
Ball ball;
Render render;
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
bool scored = false;
bool keep = false;
GLfloat playerX[2], playerZ[2];
int currentPlayer = 0;
int points[] = {3, 3};
bool night = false;
bool fog = false;
bool keys[256];
bool leftKey = false, rightKey = false, upKey = false, downKey = false;

GLfloat distance(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
void changePosition(GLfloat x, GLfloat z);
GLfloat random(GLfloat minimo, GLfloat maximo){	
  GLfloat y;
  y = rand()%1000;
  return (minimo+ 0.001*y*(maximo-minimo));
}

void changeView(){
  playerX[currentPlayer] = mainCamera.x;
  playerZ[currentPlayer] = mainCamera.z;
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
  mainCamera.tY = 3;
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
  if(night){
    ambientColor[0] = 0.2f;
    ambientColor[1] = 0.2f;
    ambientColor[2] = 0.2f;
  }
  else{
    ambientColor[0] = 0.8f;
    ambientColor[1] = 0.8f;
    ambientColor[2] = 0.8f;
  }
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
  GLfloat Foco_ak = 1.0;
  GLfloat Foco_al = 0.05f;
  GLfloat Foco_aq = 0.0f;
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,	Foco_aq);

  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, angle);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, direction);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 5.0);
  if(mode == TURNING_MODE){
    glEnable(GL_LIGHT0);
  }
  else{
    glDisable(GL_LIGHT0);
  }
  angle = 180.0f;
  GLfloat position1[4] = {8.0,5.0,-15,1.0f};
  GLfloat color1[3] = {1.0,1.0,1.0};
  GLfloat direction1[4] = {-12.25f,-5.0f,4.0f,1.0f};
  glPushMatrix();
  if(scored){
    glColor3f(0.5,1.0,0.5);
  }else{
    glColor3f(1.0,0.5,0.5);
  }
  glTranslatef(position1[0],position1[1],position1[2]);
  glutSolidSphere(0.5,50,50);
  glPopMatrix();
  glEnable(GL_LIGHT1);
  glLightfv(GL_LIGHT1,GL_POSITION, position1);
  glLightfv(GL_LIGHT1,GL_DIFFUSE,color1);
  
  glLightf(GL_LIGHT1,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT1,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT1,GL_QUADRATIC_ATTENUATION,	Foco_aq);
  
  glLightf(GL_LIGHT1,GL_SPOT_CUTOFF, angle);
  glLightfv(GL_LIGHT1,GL_SPOT_DIRECTION, direction1);
  glLightf(GL_LIGHT1,GL_SPOT_EXPONENT, 3.0);

  GLfloat position2[4] = {-8,5.0,-15,1.0f};
  GLfloat color2[3] = {1.0,1.0,1.0};
  GLfloat direction2[4] = {12.75f,-5.0f,4.0f,1.0f};
  glPushMatrix();
  glTranslatef(position2[0],position2[1],position2[2]);
  glutSolidSphere(0.5,50,50);
  glPopMatrix();
  glEnable(GL_LIGHT2);
  glLightfv(GL_LIGHT2,GL_POSITION, position2);
  glLightfv(GL_LIGHT2,GL_DIFFUSE,color2);
  
  glLightf(GL_LIGHT2,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT2,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT2,GL_QUADRATIC_ATTENUATION,	Foco_aq);
  
  glLightf(GL_LIGHT2,GL_SPOT_CUTOFF, angle);
  glLightfv(GL_LIGHT2,GL_SPOT_DIRECTION, direction2);
  glLightf(GL_LIGHT2,GL_SPOT_EXPONENT, 3.0);
  
  GLfloat position3[4] = {-8,5.0,15,1.0f};
  GLfloat color3[3] = {1.0,1.0,1.0};
  GLfloat direction3[4] = {12.75f,-5.0f,-4.0f,1.0f};
  glPushMatrix();
  glTranslatef(position3[0],position3[1],position3[2]);
  glutSolidSphere(0.5,50,50);
  glPopMatrix();
  glEnable(GL_LIGHT3);
  glLightfv(GL_LIGHT3,GL_POSITION, position3);
  glLightfv(GL_LIGHT3,GL_DIFFUSE,color3);
  
  glLightf(GL_LIGHT3,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT3,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT3,GL_QUADRATIC_ATTENUATION,	Foco_aq);
  
  glLightf(GL_LIGHT3,GL_SPOT_CUTOFF, angle);
  glLightfv(GL_LIGHT3,GL_SPOT_DIRECTION, direction3);
  glLightf(GL_LIGHT3,GL_SPOT_EXPONENT, 3.0);

  GLfloat position4[4] = {8,5.0,15,1.0f};
  GLfloat color4[3] = {1.0,1.0,1.0};
  GLfloat direction4[4] = {-12.75f,-5.0f,-4.0f,1.0f};
  glPushMatrix();
  glTranslatef(position4[0],position4[1],position4[2]);
  glutSolidSphere(0.5,50,50);
  glPopMatrix();
  glEnable(GL_LIGHT4);
  glLightfv(GL_LIGHT4,GL_POSITION, position4);
  glLightfv(GL_LIGHT4,GL_DIFFUSE,color4);
  
  glLightf(GL_LIGHT4,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT4,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT4,GL_QUADRATIC_ATTENUATION,	Foco_aq);
  
  glLightf(GL_LIGHT4,GL_SPOT_CUTOFF, angle);
  glLightfv(GL_LIGHT4,GL_SPOT_DIRECTION, direction4);
  glLightf(GL_LIGHT4,GL_SPOT_EXPONENT, 3.0);
  if(night){
    glEnable(GL_LIGHT1);
    glEnable(GL_LIGHT2);
    glEnable(GL_LIGHT3);
    glEnable(GL_LIGHT4);
  } else {
    glDisable(GL_LIGHT1);
    glDisable(GL_LIGHT2);
    glDisable(GL_LIGHT3);
    glDisable(GL_LIGHT4);
  }
}

void init(void)
{
  glClearColor(1.0,1.0,1.0,1.0);
  glShadeModel(GL_SMOOTH);
  render.loadTextures();
  ball.loadTexture();
  glEnable(GL_TEXTURE_2D);
  glEnable(GL_COLOR_MATERIAL);
  glEnable(GL_BLEND);
  glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
  glEnable(GL_DEPTH_TEST);
  lights();
  glEnable(GL_LIGHTING);
  glEnable(GL_LIGHT0);
  GLfloat _x = random(-7.5, 7.5);
  GLfloat _z = random(0, 13);
  changePosition(_x,_z);

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
  if(keys['a']){
    if(mode == ADJUST_MODE){
      strength -= 0.01;
      if(strength<0.5) strength = 0.5;
    }
    else if(mode == CATCH_MODE){
      mainCamera.move(90);
    }
  }
  if(keys['d']){
    if(mode == ADJUST_MODE){
      strength+=0.01;
      if(strength>10) strength = 10;
    }
    else if(mode == CATCH_MODE){
      mainCamera.move(-90);
    }
  }
    
  if(keys['x'] && mode ==CATCH_MODE)
    mainCamera.move(180);
  if(leftKey){
    mainCamera.rotate(2, true);
  }
  if(rightKey){
    mainCamera.rotate(-2, true);
  }
  if(upKey){
    mainCamera.rotate(1.5, false);
  }
  if(downKey)
    mainCamera.rotate(-1.5, false);
}

void update(){
  handleKeys();
  GLfloat oldX = ball.x;
  GLfloat oldY = ball.y;
  GLfloat oldZ = ball.z;
  if(oldZ + ball.radius >= 15 && !keep){
    scored = false;
  }
  ball.update();
  if(distance(oldX, 0, oldZ, 0, 0, 14.65) < ball.radius + 0.35){
    if(oldY > 3.05 && ball.y<= 3.05){
      scored = true;
    }
  }
  if(ball.z + ball.radius > 15){
    if(ball.y + ball.radius >= 4.4f){
      GLfloat _x = random(-7.5, 7.5);
      GLfloat _z = random(0, 13);
      ball.move(0,0,0);
      ball.y = ball.radius;
      changePosition(_x,_z);
    }
  }
  if(distance(mainCamera.x, 0, mainCamera.z, ball.x, 0, ball.z) < 1.0f && !ball.locked){
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


void draw(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  
  
  //Perspective

  
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, wScreen/hScreen, 0.1, 400.0);
  glEnable(GL_COLOR_MATERIAL);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  
  mainCamera.draw();
  render.drawSkybox();

  
  render.drawField();
  ball.draw();
  
  lights();
  glEnable(GL_LIGHTING);
  if(mode == ADJUST_MODE){
    drawArrow();
  }
  
  
  if(mainCamera.z > 0){
    glPushMatrix();
    glEnable(GL_BLEND);
    glColor4f(0.5,0.5,0.5,0.5);
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
    glColor4f(0.5,0.5,0.5,0.5f);
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
    glEnable(GL_BLEND);	
    glColor4f(0.5,0.5,0.5,0.5f);
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
    glColor4f(0.5,0.5,0.5,0.5);
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
  GLfloat colorN[3] = {0.2,0.2,0.2};
  glFogfv(GL_FOG_COLOR, colorN); //Cor do nevoeiro
  glFogi(GL_FOG_MODE, GL_EXP); //Equa‹o do nevoeiro - linear
  glFogf(GL_FOG_START, 40.0); // Dist‰ncia a que ter‡ in’cio o nevoeiro
  glFogf(GL_FOG_END, 60.0); // Dist‰ncia a que o nevoeiro terminar‡
  glFogf (GL_FOG_DENSITY, 0.05);
  if(fog)glEnable(GL_FOG);
  else glDisable(GL_FOG);
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

void change_player(int){
  ball.locked = false;
  shootBall();
  keep = false;
}

void keyboardUp(unsigned char key, int x, int y){
  if(key == ' ' && mode == ADJUST_MODE){
    glutTimerFunc(5000, change_player, 0);
    currentPlayer++;
    if(currentPlayer == 2){
      currentPlayer = 0;
    }
    mainCamera.x = playerX[currentPlayer];
    mainCamera.y = 1.8;
    mainCamera.z = playerZ[currentPlayer];
    mainCamera.tX = ball.x;
    mainCamera.tY = ball.y;
    mainCamera.tZ = ball.z;
    mode = CATCH_MODE;
  }
  if(key == 'n'){
    night = !night;
  }
  if(key == 'f'){
    fog = !fog;
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
