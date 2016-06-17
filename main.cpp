#include "main.hpp"
#include "camera.hpp"
#include "ball.hpp"

Camera mainCamera;
Ball ball;

GLfloat worldLimitX = 100.0, worldLimitZ = 50.0;
GLfloat wScreen = 800.0, hScreen = 600.0;
GLfloat ambientColor[4] =  {0.7,0.7,0.7,1.0};

GLfloat draw_interval = 1000.0 / 30.0;

bool keys[256];
bool leftKey = false, rightKey = false, upKey = false, downKey = false;

GLfloat random(GLfloat minimo, GLfloat maximo){	
  GLfloat y;
  y = rand()%1000;
  return (minimo+ 0.001*y*(maximo-minimo));
}


void initLights(void){
  glLightModelfv(GL_LIGHT_MODEL_AMBIENT,ambientColor);
}

void init(void)
{
  glClearColor(0.0,1.0,0.0,1.0);
  glShadeModel(GL_SMOOTH);
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
    mainCamera.tZ = -14.325;
  }
  else{
    mainCamera.tZ = 14.325;
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

void drawField(){
  glPushMatrix();
  glColor3f(1,1,1);
  
  glBegin(GL_QUADS);
  glVertex3f(-7.62, 0, -14.325);
  glVertex3f(-7.62, 0, 14.325);
  glVertex3f(7.62, 0, 14.325);
  glVertex3f(7.62, 0, -14.325);
  glEnd();
  
  glPopMatrix();

  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,1.0);
  glTranslatef(0.0,0.0,14.325);
  glRotatef(-90,1,0,0);
  
  GLUquadric *quadric;
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,3.05,50,50);
  glPopMatrix();
  
  glPushMatrix();
  glColor4f(1.0,0.0,0.0,1.0);
  glTranslatef(0.0,0.0,-14.325);
  glRotatef(-90,1,0,0);
  
  quadric = gluNewQuadric();
  gluQuadricNormals(quadric, GLU_SMOOTH);
  
  gluCylinder(quadric,0.05,0.05,3.05,50,50);
  glPopMatrix();
		
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
    GLfloat _x = random(-7.62, 7.62);
    GLfloat _z = random(-7.62, 7.62);
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
