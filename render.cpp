#include "render.hpp"
#include "main.hpp"

Render::Render(){}

Render::~Render(){}

void Render::print(char *string, GLfloat x, GLfloat y){
  glRasterPos2f(x,y); 
  while (*string)
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *string++); 

}

void Render::drawField(){  
  glPushMatrix();
  glDisable(GL_TEXTURE_2D);
  glColor4f(1.0,1.0,1.0,1);
  glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
  glEnable(GL_COLOR_MATERIAL);
  glBindTexture(GL_TEXTURE_2D, 0); 
  GLfloat num_pol = 200.0f;
  glNormal3f(0.0, 1.0, 0.0);
  for(GLfloat line = 0.0f; line< num_pol; line++){
    for(GLfloat col = 0.0f; col < num_pol; col++){
      glBegin(GL_QUADS);
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

  drawRoad();
}


void Render::drawSkybox(){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skyboxtex[1]);
  glPushMatrix();
  glColor3f(1.0,1.0,1.0);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(1.0f,0.0f);  glVertex3f(-100, -100, -100); 
  glTexCoord2f(0.0f,0.0f);  glVertex3f(-100, -100, 100); 
  glTexCoord2f(0.0f,1.0f);  glVertex3f(-100, 100, 100); 
  glTexCoord2f(1.0f,1.0f);  glVertex3f(-100, 100, -100); 
  glEnd();
  
  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D,skyboxtex[2]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0,0.0);glVertex3f(100, 100, -100);
  glTexCoord2f(1.0,0.0);glVertex3f(100, 100, 100);
  glTexCoord2f(1.0,1.0);glVertex3f(-100, 100, 100);
  glTexCoord2f(0.0,1.0);glVertex3f(-100, 100, -100);
  glEnd();

  glDisable(GL_TEXTURE_2D);
  glEnable(GL_TEXTURE_2D);  
  glBindTexture(GL_TEXTURE_2D,skyboxtex[4]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0f,0.0f);  glVertex3f(100, -100, -100);
  glTexCoord2f(1.0f,0.0f);  glVertex3f(100, -100, 100);
  glTexCoord2f(1.0f,1.0f);  glVertex3f(100, 100, 100);
  glTexCoord2f(0.0f,1.0f);  glVertex3f(100, 100, -100);
  glEnd();
  glDisable(GL_TEXTURE_2D);
  
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skyboxtex[3]);
  glBegin(GL_POLYGON);
  glTexCoord2f(1.0f,0.0f);glVertex3f(100, -100, -100);
  glTexCoord2f(1.0f,1.0f);glVertex3f(100, 100, -100);
  glTexCoord2f(0.0f,1.0f);glVertex3f(-100, 100, -100);
  glTexCoord2f(0.0f,0.0f);glVertex3f(-100, -100, -100);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,skyboxtex[0]);
  
  glBegin(GL_POLYGON);
  glTexCoord2f(0.0f,0.0f);glVertex3f(100, -100, 100);
  glTexCoord2f(0.0f,1.0f);glVertex3f(100, 100, 100);
  glTexCoord2f(1.0f,1.0f);glVertex3f(-100, 100, 100);
  glTexCoord2f(1.0f,0.0f);glVertex3f(-100, -100, 100);
  glEnd();
  glDisable(GL_TEXTURE_2D);

  
  
  glPopMatrix();
}

void Render::drawPaisagem(){
  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[4]);
  glPushMatrix();
  glTranslatef(11.5,0,0);
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f, 1.0f, 1.0f);
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
  glColor3f(1.0,1.0,1.0);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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

void Render::drawRoad(){
  /*PASSEIO*/
  glNormal3f(0,1,0);
  glEnable(GL_LIGHTING);
  glEnable(GL_TEXTURE_2D);
  glColor3f(1,1,1);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(19.5, 0, 0);
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor4f(1,1,1,1.0);
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

  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[2]);
  glPushMatrix();
  glTranslatef(0, 0, -29);
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-45.5, 0, -4);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-45.5, 0, 4);
  glTexCoord2f(20.0f,10.0f);glVertex3f(50.5, 0, 4);
  glTexCoord2f(0.0f,10.0f);glVertex3f(50.5 , 0, -4);
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

  glEnable(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D,textures[3]);
  glPushMatrix();
  glTranslatef(0, 0, -34);
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
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
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(0, 0, -85);
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13, 0, -10);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13, 0, 50);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 50);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -10);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(44, 0, -14);
  glColor3f(1.0f,1.0f,1.0f);
  glBegin(GL_QUADS);
  glTexCoord2f(0.0f,0.0f); glVertex3f(-13.5, 0, -9);
  glTexCoord2f(20.0f,0.0f);glVertex3f(-13.5, 0, 34);
  glTexCoord2f(20.0f,10.0f);glVertex3f(18.5, 0, 34);
  glTexCoord2f(0.0f,10.0f);glVertex3f(18.5 , 0, -9);
  glEnd();
  glPopMatrix();

  glPushMatrix();
  glTranslatef(-43, 0, -14);
  glColor3f(1.0f,1.0f,1.0f);
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



void Render::drawFieldLines(){
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


void Render::loadTextures(){
  
  glGenTextures(1, &skyboxtex[0]); 
  glBindTexture(GL_TEXTURE_2D, skyboxtex[0]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("skyrender0001.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[1]); 
  glBindTexture(GL_TEXTURE_2D, skyboxtex[1]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("skyrender0002.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[2]); 
  glBindTexture(GL_TEXTURE_2D, skyboxtex[2]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("skyrender0003.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[3]); 
  glBindTexture(GL_TEXTURE_2D, skyboxtex[3]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("skyrender0004.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &skyboxtex[4]); 
  glBindTexture(GL_TEXTURE_2D, skyboxtex[4]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("skyrender0005.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
  
  glGenTextures(1, &textures[0]); 
  glBindTexture(GL_TEXTURE_2D, textures[0]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("grass.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[1]); 
  glBindTexture(GL_TEXTURE_2D, textures[1]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("sand.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[2]); 
  glBindTexture(GL_TEXTURE_2D, textures[2]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("cim.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());

  glGenTextures(1, &textures[3]); 
  glBindTexture(GL_TEXTURE_2D, textures[3]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("calcada.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
  
  glGenTextures(1, &textures[4]); 
  glBindTexture(GL_TEXTURE_2D, textures[4]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("pista.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
  
  glGenTextures(1, &textures[0]); 
  glBindTexture(GL_TEXTURE_2D, textures[0]); 
  glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
  imag.LoadBmpFile("grass.bmp"); 
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, (int)imag.GetNumCols(), (int)imag.GetNumRows(), 0, GL_RGB, GL_UNSIGNED_BYTE, imag.ImageData());
}

void Render::drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius, int rot){
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


void Render::drawSits(int side){

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

void Render::drawBullding(int x, int y, int z, int xi, int zi){

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
