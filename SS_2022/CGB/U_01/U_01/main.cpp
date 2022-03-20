#include "GL/freeglut.h"
#include "stdio.h"
#include <iostream>

// For Convenience my functions are with underscore, GLUT functions with Camel Case
using namespace std;

// Has to be global due to event handlers on window id
int windowid;

GLfloat angleCube = 0.0f;


GLfloat scale = 1.5f;

const GLfloat step = 0.5f;

// Keine Absoluten Positionen relative 
// relative position z +1;

int navXIdx = 53;
int navZIdx = 53;

// Variable für Jump
int navYIdx = 1; // initiale Position über dem Boden

// Y ist Blickwinkel - hier bleibt absolut - granular
GLfloat centerXOffset = 0.0f;
GLfloat centerYOffset = 0.0f;

const int lab_row = 20;
const int lab_col = 20;

int lab_area[lab_row][lab_col] =
{
  1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1,
  1, 0, 1, 0, 1, 0, 3, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1,
  1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 0, 1, 0, 1, 1, 1,
  1, 1, 1, 1, 1, 0, 1, 2, 0, 0, 1, 0, 1, 0, 0, 1, 0, 3, 0, 1, 
  1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 1, 0, 1, 1, 1, 0, 1,
  1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1,
  1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 1,
  1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1,
  1, 0, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 0, 1, 1, 1, 0, 1, 1, 1, 1,
  1, 1, 1, 1, 0, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 3, 1,
  1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1,
  1, 1, 0, 1, 1, 1, 1, 2, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
  1, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 2, 0, 0, 3, 0, 1, 
  1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1,
  1, 0, 1, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 0, 0, 1, 
  1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1
};

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

// Fenster Size
void reshape_func(int x_width, int y_height) {
  if( y_height == 0 || x_width == 0) return;

  glMatrixMode(GL_PROJECTION); // Set a new projection matrix
  glLoadIdentity();
  gluPerspective(40.0f, (GLdouble)x_width / (GLdouble)y_height, 0.1f, 100.0f);
  glViewport(0, 0, x_width, y_height);

}

void draw_cube(GLfloat x, GLfloat y, GLfloat z) {
  glPushMatrix(); // Zugriff auf Globale Matrix der Simulation
    glTranslatef(x, (y + (scale /2)), z); // Verschiebung
    //glScalef(1.f, 1.f, 1.f); // Reihenfolge beim Rendern
    glColor3f(0.6f,0.6f,0.6f);
    glutSolidCube(scale);
    glColor3f(0.5f, 0.5f, 0.6f);
    glutWireCube(scale);
  glPopMatrix();
}

void draw_sphere(GLfloat x, GLfloat y, GLfloat z) {
  glPushMatrix(); // Zugriff auf Globale Matrix der Simulation
  glTranslatef(x, (y + (scale / 4)), z); // Verschiebung
  //glScalef(1.f, 1.f, 1.f); // Reihenfolge beim Rendern
  glColor3f(0.6f, 0.2f, 0.3f);
  glutSolidSphere((scale /3), 8,8);
  glPopMatrix();
}

void draw_pyramid(GLfloat x, GLfloat y, GLfloat z) {
  glPushMatrix(); // Zugriff auf Globale Matrix der Simulation
  glTranslatef(x, (y + (scale / 4)), z); // Verschiebung
  //glScalef(1.f, 1.f, 1.f); // Reihenfolge beim Rendern
  glColor3f(1.0f, 0.0f, 0.0f); glVertex3f(x + 0.0f, y + 1.f, z + 0.0f);
  glColor3f(0.0f, 1.0f, 0.0f); glVertex3f(x + -1.0f,y -1.0f, z + 1.0f);
  glColor3f(0.0f, 0.0f, 1.0f); glVertex3f(x + 1.0f,y -1.0f,z + 1.0f);

  glPopMatrix();
}

// Define Start Function to render our initial scene
void render_scene(void) {
  glClear(GL_COLOR_BUFFER_BIT); // Background
  glClearColor(1.f, 1.0f, 1.0f, .5f);

  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity(); // 0, 0, 0 Matrix

  GLfloat navX = navXIdx * step;
  GLfloat navY = navYIdx * step;
  GLfloat navZ = navZIdx * step;

  //GLfloat centerX = navX + centerXOffset;
  //GLfloat centerY = navY + centerYOffset;
  //GLfloat centerZ = navZ - 1.0f;

  GLfloat centerX = navX + centerXOffset;
  GLfloat centerY = navY + centerYOffset;
  GLfloat centerZ = navZ - 1.0f;

  gluLookAt(
    navX, navY, navZ, // Kamera
    centerX, centerY, centerZ, //centerX, centerY, centerZ, // Center - Eye - Mouse verschiebt Center - glut mouse passiv motion
    0.0f, 1.0f, 0.0f // up vector -> Oben ist Y
  );

  cout << "X: " << navX << " | " << "Center X: " << centerX << " | ";
  cout << "Y: " << navY << " | " << "Center Y: " << centerY << " | ";
  cout << "Z: " << navZ <<  "| " << "Center Z: " << centerZ << endl;

  GLfloat x = 0;
  GLfloat z = 0;

  for (int i = 0; i < lab_row; i++) {
    for (int j = 0; j < lab_col; j++) {
      //if (lab_area[i][j] == 1) {
      //  draw_cube(x, 0, z);
      //}
      //else if (lab_area[i][j] == 2) {
      //  draw_sphere(x, 0, z);
      //  //cout << i << j << endl;
      //}
      switch (lab_area[i][j]) {
      case 1:
        draw_cube(x, 0, z);
        break;
      case 2:
        draw_sphere(x, 0, z);
        break;
      case 3:
        draw_pyramid(x, 0, z);
        break;
      }
      x += scale;
    }
    x = 0.0f;
    z += scale;
  }
  //glutPostRedisplay();
  glutSwapBuffers(); // necessary for drawing 
}

// Kollision - wie groß ist ein schritt

// register Keyboard Handler similar too what has been done in the course
// Mouse geht auf Center
void keyboard(unsigned char key, int xcoor, int ycoor) {
  switch (key) {
  case 'a':
    navXIdx = navXIdx - 1;
    break;
  case 'd':
    navXIdx = navXIdx + 1;
    break;
  case 'w':
    navZIdx = navZIdx - 1;
    break;
  case 's':
    navZIdx = navZIdx + 1;
    break;
  case 'q': // Sonst bei Sprung relevant
    navYIdx = navYIdx - 1;
    break;
  case 'e':
    navYIdx = navYIdx + 1;
    break;
  case 27: // escape key
    glutDestroyWindow(windowid);
    exit(0);
    break;
  }
  glutPostRedisplay(); // explicitly trigger the display callback
}

void passive_mouse(int x, int y) {
  // center x bewegen links rechts
  // center y oben unten
  // z not necessary

}

// register Event handlers
void register_event_handlers(void) {
  /*glutDisplayFunc(renderPrimitives);*/
  glutDisplayFunc(render_scene);
  glutKeyboardFunc(keyboard);
  glutReshapeFunc(reshape_func);
  glutPassiveMotionFunc(passive_mouse);
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