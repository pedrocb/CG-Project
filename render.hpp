#ifdef __APPLE__
#include <OpenGL/OpenGL.h>
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include "RgbImage.h"

using namespace std;

class Render {
public:
  Render();
  ~Render();
  GLuint textures[8];
  GLuint skyboxtex[5];
  RgbImage imag;
  void loadTextures();
  void drawFieldLines();
  void drawPaisagem();
  void drawRoad();
  void draw();
  void drawSits(int side);
  void drawHollowCircle(GLfloat x, GLfloat y, GLfloat radius, int rot);
  void drawBullding(int x, int y, int z, int xi, int zi);
  void drawLights(int x, int y);
  void print(char *string, GLfloat x, GLfloat y);
  void drawField();
  void drawSkybox();
};
