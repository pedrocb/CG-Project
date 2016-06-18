#include "main.hpp"
#include "camera.hpp"
#include "ball.hpp"

Camera mainCamera;
Ball ball;

bool ball_inside;

GLfloat worldLimitX = 100.0, worldLimitZ = 50.0;
GLfloat wScreen = 800.0, hScreen = 600.0;
GLfloat ambientColor[4] =  {0.7,0.7,0.7,1.0};

GLfloat draw_interval = 1000.0 / 30.0;
GLfloat zoneRadius = 2.5;

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
  mainCamera.tX = ball.x;
  if(ball.z < 0){
    mainCamera.z = (-14.325 - ball.z)/2.0;
    mainCamera.tZ = (-14.325 - ball.z)/2.0;
    
  }
  else{
    mainCamera.z = (14.325 - ball.z)/2.0;
    mainCamera.tZ = (14.325 - ball.z)/2.0;
  }
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


void DrawCircle(float cx, float cz, float r, int num_segments)
{
    glBegin(GL_LINE_LOOP);
    for(int ii = 0; ii < num_segments; ii++)
    {
      float theta = 2.0f * PI * float(ii) / float(num_segments);//get the current angle
	
      float x = r * cosf(theta);//calculate the x component
      float z = r * sinf(theta);//calculate the y component
      
      glVertex3f(x + cx, 0, z + cz);//output vertex

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
  if(keys['w']){
    if(!(distance(mainCamera.x, 0, mainCamera.z, ball.x, 0, ball.z) < zoneRadius/2.0f)){
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
  
  glBegin(GL_LINES);
  //glVertex3f(ball.x, 0, ball.z);
  //  glVertex3f(ball.x + vetorX*size/magnitude, arrowAngle, ball.z + vetorZ*size/magnitude);
  glEnd();
  glPopMatrix();
}

void drawField(){
  glEnable(GL_COLOR_MATERIAL);
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

  ball.draw();
  drawArrow();
  drawField();
  
  glutSwapBuffers();

}



void keyboard(unsigned char key, int x, int y){
  GLfloat distanceToBall = distance(mainCamera.x, mainCamera.y, mainCamera.z, ball.x, ball.y, ball.z);
  if(key == 'r'){
    GLfloat _x = random(-7.62, 7.62);
    GLfloat _z = random(-7.62, 7.62);
    changePosition(_x,_z);
    return;
  }
  if(key == 'a' && distanceToBall <= zoneRadius){
     GLfloat radianAngle = (PI * 1.0f) / 180.0f;
     GLfloat deltaX = (ball.x - mainCamera.x);
     GLfloat deltaZ = (ball.z - mainCamera.z);
     GLfloat finalX= mainCamera.x + (deltaX * cos(radianAngle) + deltaZ * sin(radianAngle));
     GLfloat finalZ = mainCamera.z + (-deltaX * sin(radianAngle) + deltaZ * cos(radianAngle));
     ball.move(finalX - ball.x,  -0.15, finalZ - ball.z);
  }
  else if(key == 'd' && distanceToBall <= zoneRadius){
    GLfloat radianAngle = (PI * -1.0f) / 180.0f;
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
