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

GLfloat centerX = 0.0f;
GLfloat centerY = 0.0f;
GLfloat centerZ = 0.0f;

int lab_area[lab_row][lab_col] =
{
  1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 , 1 ,
  1 , 0 , 0 , 0 , 0 , 1 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 0 , 1 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 0 , 0 , 0 , 0 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 1 ,
  1 , 1 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 ,
  1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 1 , 0 , 1 , 0 , 0 , 0 , 0 , 1 ,
  1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 0 , 1 , 0 , 1 , 1 , 0 , 1 , 1 , 1 ,
  1 , 0 , 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
  1 , 1 , 0,0,0,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,
  1 , 1 , 1,0,1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,
  1 , 0 , 1,0,1,0,0,0,0,1,1,0,1,0,1,0,0,0,0,1,
  1 , 0 , 1,0,1,1,0,1,1,1,1,0,1,0,1,1,0,1,1,1,
  1 , 0 , 0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,1,
  1 , 1 , 0,1,1,1,0,1,1,1,1,1,0,1,1,1,0,1,1,1,
  1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
  1 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 1 , 1 , 0 , 1 , 1 , 1 , 0 , 1 , 1 , 1 ,
  1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 , 1 , 1 , 0 , 0 , 0 , 0 , 0 , 0 , 0 , 1 ,
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

// gluPerspective + reshape
// gluPerspective(40.0f, (GLdouble)xwidth / (GLdouble)yheight, 0.5f, 100.0f);

void reshape_func(int x_width, int y_height) {
  if( y_height == 0 || x_width == 0) return;

  glMatrixMode(GL_PROJECTION); // Set a new projection matrix
  glLoadIdentity();
  gluPerspective(60.0f, (GLdouble)x_width / (GLdouble)y_height, 0.5f, 200.0f);
  glViewport(0, 0, x_width, y_height);

}



void draw_cube(GLfloat x, GLfloat y, GLfloat z) {
  glPushMatrix();
    glTranslatef(x, y, z);
    glColor3f(0.2f,0.2f,0.2f);
    glScalef(1.f, 1.f, 1.f);
    glutSolidCube(0.25f);
    glColor3f(0.5f, 0.5f, 0.5f);
    glutWireCube(0.25f);
  glPopMatrix();
}

// Define Start Function to render our initial scene
void render_scene(void) {
  glClear(GL_COLOR_BUFFER_BIT);
  glClearColor(1.f, 1.0f, 1.0f, .5f);
  glLoadIdentity();

  gluLookAt(
    navX, navY, navZ, // Kamera
    centerX, centerY, centerZ, // Center 
    0.0f, 1.0f, 0.0f
  );

  glScalef(0.4f, 0.4f, 0.4f);
  //glRotatef(250, 0.f, 0.f, 1.f);
  //glRotatef(300, 0.f, 1.f, 0.f);

  cout << "X: " << navX << " | ";
  cout << "Y: " << navY << " | ";
  cout << "Z: " << navZ << endl;

  for (int i = 0; i < 10; i++) {
    for (int j = 0; j < 10; j++) {

    draw_cube((i * 0.25f)-1, 0, (j * 0.25f) - 1);
    }
  }
  //draw_cube(0, 0, 0);
  //for (int i = 0; i < lab_row; i++) {
  //  for (int j = 0; j < lab_col; j++) {
  //    if (lab_area[i][j] == 1) {
  //      draw_cube(i * 0.25, j * 0.25, 0);
  //      /*draw_cube(i * 0.25, 0, j * 0.25);*/
  //    }
  //  }
  //}
  //glutPostRedisplay();
  glutSwapBuffers(); // necessary for drawing 
}

// register Keyboard Handler similar too what has been done in the course
void keyboard(unsigned char key, int xcoor, int ycoor) {
  switch (key) {
  case 'a':
    navX = navX - 0.1f;
    break;
  case 'd':
    navX = navX + 0.1f;
    break;
  case 'w':
    navZ = navZ - 0.1f;
    break;
  case 's':
    navZ = navZ + 0.1f;
    break;
  case 'q':
    navY = navY - 0.1f;
    break;
  case 'e':
    navY = navY + 0.1f;
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
  glutReshapeFunc(reshape_func);
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