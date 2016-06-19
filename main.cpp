#include "main.hpp"
#include "camera.hpp"
#include "ball.hpp"

Camera mainCamera;
Ball ball;

bool ball_inside;

GLfloat worldLimitX = 100.0, worldLimitZ = 50.0;
GLfloat wScreen = 800.0, hScreen = 600.0;
GLfloat ambientColor[4] =  {1.0,1.0,1.0};

GLfloat draw_interval = 1000.0 / 30.0;
GLfloat zoneRadius = 1.3f;

int mode = CATCH_MODE;

GLfloat playerX, playerZ = 0;

bool keys[256];
bool leftKey = false, rightKey = false, upKey = false, downKey = false;

GLfloat random(GLfloat minimo, GLfloat maximo){	
  GLfloat y;
  y = rand()%1000;
  return (minimo+ 0.001*y*(maximo-minimo));
}

void changeView(){
  playerX = mainCamera.x;
  playerZ = mainCamera.z;
  mainCamera.x = -10;
  mainCamera.y = 3.5;
  mainCamera.tX = ball.x;
  if(ball.z < 0){
    mainCamera.tZ = mainCamera.z +  (-16 - ball.z)/2.0;
    mainCamera.z = mainCamera.z + (-16 - ball.z)/2.0;
  }
  else{
    mainCamera.tZ = mainCamera.z + (16 - ball.z)/2.0;
    mainCamera.z = mainCamera.z + (16 - ball.z)/2.0;
  }
}

void lights(void){
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);
  GLfloat position[] = { mainCamera.x,1.8,mainCamera.z, 1.0};
  GLfloat direction[] = { 0.0, -1.0, 0.0 };
  GLfloat color[] = {0.0,1.0,1.0,1.0};
  
  glEnable(GL_LIGHT0);
  glLightfv(GL_LIGHT0,GL_POSITION, position);
  glLightfv(GL_LIGHT0,GL_DIFFUSE,color);
  GLfloat Foco_ak			= 1.0;
  GLfloat Foco_al			= 0.05f;
  GLfloat Foco_aq			= 0.0f;
  glLightf(GL_LIGHT0,GL_CONSTANT_ATTENUATION,	Foco_ak);
  glLightf(GL_LIGHT0,GL_LINEAR_ATTENUATION,		Foco_al);
  glLightf(GL_LIGHT0,GL_QUADRATIC_ATTENUATION,	Foco_aq);

  glLightf(GL_LIGHT0,GL_SPOT_CUTOFF, 30.0);
  glLightfv(GL_LIGHT0,GL_SPOT_DIRECTION, direction);
  glLightf(GL_LIGHT0,GL_SPOT_EXPONENT, 3.0);
}

void init(void)
{
  glClearColor(0.0,1.0,0.0,1.0);
  glEnable(GL_DEPTH_TEST);
  glShadeModel(GL_FLAT);
  glEnable(GL_COLOR_MATERIAL);
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
  if(mode == CATCH_MODE){
    if(keys['w']){
      mainCamera.move(0);
    }
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
    //mode = TURNING_MODE;
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
  GLfloat deltaX = mainCamera.tX - mainCamera.x;
  GLfloat deltaY = mainCamera.tY - mainCamera.y;
  GLfloat deltaZ = mainCamera.tZ - mainCamera.z;
  GLfloat magnitude = sqrt(pow(deltaX, 2.0f) + pow(deltaY, 2.0f) + pow(deltaZ, 2.0f));
  GLfloat strength = 1.5f;
  
  ball.move(strength * deltaX/magnitude, strength * deltaY/magnitude,strength * deltaZ/magnitude);
}

void drawArrow(){
  glPushMatrix();
  glColor3f(0.0,0.0,1.0);
  GLfloat size = 2.0f;
  GLfloat vetorX = (mainCamera.tX - ball.x);
  GLfloat vetorZ = (mainCamera.tZ - ball.z);
  GLfloat magnitude = sqrt(pow(vetorX, 2.0f) + pow(vetorZ, 2.0f));
  
  
  glLineWidth(5.0f);
  
  //glBegin(GL_LINES);
  //glVertex3f(ball.x, 0, ball.z);
  //  glVertex3f(ball.x + vetorX*size/magnitude, arrowAngle, ball.z + vetorZ*size/magnitude);
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
  glColor3f(1,0,0);
  glLineWidth(20);
  glPushMatrix();
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
  glColor3f(1,0,0);
  glLineWidth(20);
  glPushMatrix();
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

void drawField(){
  
  glPushMatrix();

  glColor4f(0.2,0.2,0.2,1);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);

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

  if(mode == TURNING_MODE){
    glColor4f(1.0,0.0,1.0,0.5f);
    DrawCircle(mainCamera.x, mainCamera.z, zoneRadius, 360);
  }

  
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


}

void draw(void){
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
  

  //Perspective
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(60.0, wScreen/hScreen, 1.0, 50.0);



  mainCamera.draw();
  
  
  
  ball.draw();
 
    
  lights();
  glEnable(GL_LIGHTING);
  glPushMatrix();
  drawField();
  glPopMatrix();
  glutSwapBuffers();
  
}



void keyboard(unsigned char key, int x, int y){
  GLfloat distanceToBall = distance(mainCamera.x, 0, mainCamera.z, ball.x, 0, ball.z);
  if(key == 'r'){
    GLfloat _x = random(-7.5, 7.5);
    GLfloat _z = random(-7.5, 7.5);
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
  if(key == ' '){
    ball.locked = true;
    changeView();
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
