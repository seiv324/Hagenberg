#include "GL/freeglut.h"
#include "stdio.h"
#include <iostream>

using namespace std;

// Has to be global due to event handlers on window id
int windowid;

GLfloat angleCube = 0.0f;

const int lab_row = 20;
const int lab_col = 20;

GLfloat navX = 0.0f;
GLfloat navZ = 1.0f;
GLfloat navY = 0.0f;

int lab_area[lab_row][lab_col] =
{
  1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
  1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 1 ,
  1 , 1 ,0,1,1,1,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
  1 , 1 ,1,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,
  1 , 0 ,1,0,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,
  1 , 0 ,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,1,1,
  1 , 0 ,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
  1 , 1 ,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
  1 , 1 ,1,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,
  1 , 0 ,1,0,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,
  1 , 0 ,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,1,1,
  1 , 0 ,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
  1 , 1 ,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,
  1 , 1 ,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
  1 , 0 ,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
  1 , 1 ,0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,
  1 , 1 ,0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
  1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1
 
};

// For Convenience my functions are with underscore, GLUT functions with Camel Case

// Init Glut Parameters
int init_glut(void) {
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glMatrixMode(GL_MODELVIEW);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE); // Changing Render Mode
  glutInitWindowPosition(900, 400);
  glutInitWindowSize(1000, 800);
  int windowid;
  return windowid = glutCreateWindow("Hopefully this works^^");
}


void draw_cube(GLfloat x, GLfloat y, GLfloat z) {
  glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.207f,0.952f,0.345f);
    glScalef(1.f, 1.f, 1.f);
    glutSolidCube(0.25f);
  glPopMatrix();
}

// Define Start Function to render our initial scene
void render_scene(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.f, 1.0f, 1.0f, .5f);
  glLoadIdentity();

  gluLookAt(
    navX, navY, navZ,
    navX, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  );

  glScalef(0.1f, 0.1f, 0.1f);
  glRotatef(250, 0.f, 0.f, 1.f);
  glRotatef(300, 0.f, 1.f, 0.f);

  cout << "X: " << navX << " | ";
  cout << "Y: " << navY << " | ";
  cout << "Z: " << navZ << endl;

  for (int i = 0; i < lab_row; i++) {
    for (int j = 0; j < lab_col; j++) {
      if (lab_area[i][j] == 1) {
      draw_cube(i * 0.25, j * 0.25, 0);
      }
    }
  }

  glutSwapBuffers(); // necessary for drawing 
}

// register Keyboard Handler similar too what has been done in the course
void keyboard(unsigned char key, int xcoor, int ycoor) {
  switch (key) {
  case 'a':
    navX = navX + 0.05;
    break;
  case 'd':
    navX = navX - 0.05;
    break;
  case 'w':
    navZ = navZ + 0.05;
    break;
  case 's':
    navZ = navZ - 0.05;
    break;
  case 'q':
    navY = navY + 0.05;
    break;
  case 'e':
    navY = navY - 0.05;
    break;
  case 27: // escape key
    glutDestroyWindow(windowid);
    exit(0);
    break;
  }
  glutPostRedisplay(); // explicitly trigger the display callback
}

// register Event handlers
void register_event_handlers(void) {
  /*glutDisplayFunc(renderPrimitives);*/
  glutDisplayFunc(render_scene);
  glutKeyboardFunc(keyboard);
}

int main(int argc, char** argv) {
  glutInit(&argc, argv);

  windowid = init_glut();
  // Register Event Handlers
  register_event_handlers();
  //glutDisplayFunc(renderPrimitives);
  // Start Main Loop - essential
  glutMainLoop();
  return 0;
}