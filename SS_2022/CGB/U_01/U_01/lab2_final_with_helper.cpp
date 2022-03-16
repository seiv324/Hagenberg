/*---------------------------------------------------------------------------
 * Title: Computer Graphics Lab 2 - Meshes and Transformations
 * Author: Christoph Anthes
 * Version: 1.0 (SS22)
 * Time to complete: 90 minutes
 * Additional material: slides, course notes
 *------------------------------------------------------------------------- */
#include "GL/freeglut.h"
#include "math.h"

int windowid; // the identifier of the GLUT window

GLfloat matrot[][4] = {          // a rotation matrix
  { 0.707f, 0.707f, 0.0f, 0.0f}, // it performs a rotation around z
  {-0.707f, 0.707f, 0.0f, 0.0f}, // in 45 degrees
  { 0.0f,   0.0f,   1.0f, 0.0f},
  { 0.0f,   0.0f,   0.0f, 1.0f}
};

GLfloat mattrans[][4] = {        // a translation matrix
  { 1.0f, 0.0f,  0.0f, 0.0f},    // it performs a translation along the
  { 0.0f, 1.0f,  0.0f, 0.0f},    // x-axis of 0.5 units and along
  { 0.0f, 0.0f,  1.0f, 0.0f},    // the z-axis of -1.5 units
  { 0.5f, 0.0f, -1.5f, 1.0f}
};

// Navigation variables - required for TASK 5
GLfloat navX = 0.0f;
GLfloat navZ = 5.0f;

// Angle for cube rotation - required for TASK 6
GLfloat angleCube = 0.0f;        //angle for cube1

// Camera motion variables - required for HOMEOWRK HELPER
GLdouble angle = 0.0f;          // angle of rotation for the camera direction
GLdouble lx = 0.0f, lz = -1.0f; // actual vector representing the camera's
                                // direction
GLdouble x = 0.0f, z = 5.0f;    // XZ position of the camera

/*
*/
//Taken from http://www.lighthouse3d.com/tutorials/glut-tutorial/keyboard-example-moving-around-the-world/
void processSpecialKeys(int key, int xcoor, int ycoor) {
  float fraction = 0.1f;

  switch (key) {
    case GLUT_KEY_LEFT:
      angle -= 0.01f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
    case GLUT_KEY_RIGHT:
      angle += 0.01f;
      lx = sin(angle);
      lz = -cos(angle);
      break;
    case GLUT_KEY_UP:
      x += lx * fraction;
      z += lz * fraction;
      break;
    case GLUT_KEY_DOWN:
      x -= lx * fraction;
      z -= lz * fraction;
      break;
  }
}
/* Here we have an example to draw a bit nicer with our limited OpenGL
   knowledge. First filled objects are drawn in black, at a smaller size.
   Then the same object outlines are drawn in full size full size. Both
   will be compared in the depth buffer and the front outlines will 
   remain. */
void drawObjectAlt(void) {
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  glPushMatrix(); //set where to start the current object transformations  
    glRotatef(angleCube, 0.0, 1.0, 0.0);
    glColor3f(0.0, 0.0, 0.0); //change cube1 to black
    glScalef(0.99, 0.99, 0.99);
    glutSolidCube(0.5);
    glTranslatef(0, 0.5, 0); //move cube1 to the right
    glScalef(0.99, 0.99, 0.99);
    glutSolidSphere(0.25f, 20, 20);
  glPopMatrix();

  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glPushMatrix(); //set where to start the current object transformations  
    glRotatef(angleCube, 0.0, 1.0, 0.0);
    glColor3f(0.0, 1.0, 0.0); //change cube1 to Green
    glutSolidCube(0.5);
    glTranslatef(0, 0.5, 0); //move cube1 to the right
    glutSolidSphere(0.25f, 20, 20);
  glPopMatrix();
}

/* This is the keyboard function which is used to react on keyboard input.
   It has to be registered as a callback in glutKeyboardFunc. Once a key is
   pressed it will be invoked and the keycode as well as the current mouse
   coordinates relative to the window origin are passed.
   It acts on our FPS controls 'WASD' and the escape key. A simple output
   to the keypress is printed in the console in case of 'WASD'. In case of
   ESC the window is destroyed and the application is terminated. */
void keyboard(unsigned char key, int xcoor, int ycoor) {
  switch (key) {
    case 'a':
      navX -= 0.1f; // TASK 5
      break;
    case 'd':
      navX += 0.1f; // TASK 5
      break;
    case 'w':
      navZ -= 0.1f; // TASK 5
      break;
    case 's':
      navZ += 0.1f; // TASK 5
      break;
    case 27: // escape key
      glutDestroyWindow(windowid);
      exit(0);
      break;
  }
  glutPostRedisplay();
}

/* This function should be called when the window is resized. It has to be
   registered as a callback in glutReshapeFunc. The function sets up the
   correct perspective projection. Don't worry about it we will not go into
   detail but we need it for correct perspective 3D rendering. */
void reshapeFunc(int xwidth, int yheight) {
  if (yheight == 0 || xwidth == 0) return;  // Nothing is visible, return

  glMatrixMode(GL_PROJECTION); // Set a new projection matrix
  glLoadIdentity();
  // Angle of view: 40 degrees
  // Near clipping plane distance: 0.5
  // Far clipping plane distance: 20.0
  gluPerspective(40.0f, (GLdouble)xwidth / (GLdouble)yheight, 0.5f, 20.0f);
  glViewport(0, 0, xwidth, yheight);  // Use the whole window for rendering
}

/* This is our first display function it will be used for drawing a 2D
   triangle. The background is set to black and cleared, the current drawing
   colour is set and the vertices of the triangle are defined. At the end the
   buffers are flipped. */
void renderPrimitives(void) {
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // set background colour to black 
  glClear(GL_COLOR_BUFFER_BIT);         // clear the colour buffer

  glColor3f(0.1f, 0.2f, 0.3f);        // set the colour to grey
  glBegin(GL_TRIANGLES);              // drawing using triangles
    glVertex3f(0.0f, 1.0f, 0.0f);      // top
    glVertex3f(-1.0f, -1.0f, 0.0f);    // bottom left
    glVertex3f(1.0f, -1.0f, 0.0f);    // bottom right
  glEnd();                            // finished drawing the triangle

  /* Example 1 - Slide 5 */
  glColor3f(1.0f, 0.0f, 0.0f);        // red
  glBegin(GL_QUADS);                  // drawing using quads
    glVertex2f(-0.5f, -0.5f);          // bottom left
    glVertex2f(0.5f, -0.5f);          // bottom right
    glVertex2f(0.5f, 0.5f);            // top right
    glVertex2f(-0.5f, 0.5f);          // top left
  glEnd();

  /* Example 2 - Slide 5 */
  glBegin(GL_QUADS);                  // drawing using quads
    glColor3f(1.0f, 0.0f, 0.0f);      // red
    glVertex2f(-0.5f, -0.5f);          // bottom left
    glColor3f(0.0f, 1.0f, 0.0f);      // green
    glVertex2f(0.5f, -0.5f);          // bottom right
    glColor3f(0.0f, 0.0f, 1.0f);      // blue
    glVertex2f(0.5f, 0.5f);            // top right
    glColor3f(1.0f, 1.0f, 0.0f);      // yellow
    glVertex2f(-0.5f, 0.5f);          // top left
  glEnd();

  // TASK 1:
  glColor3f(1.0f, 1.0f, 0.0f);  // yellow
  glBegin(GL_POLYGON);          // these vertices form a closed polygon
    glVertex2f(0.4f, 0.2f);
    glVertex2f(0.6f, 0.2f);
    glVertex2f(0.7f, 0.4f);
    glVertex2f(0.6f, 0.6f);
    glVertex2f(0.4f, 0.6f);
    glVertex2f(0.3f, 0.4f);
  glEnd();
  glutSwapBuffers();
}

/* This function will be used for composited objects and will be called from a
   display function. */
void drawObject(void) { // TASK 4:
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  glPushMatrix(); //set where to start the current object transformations  
    glRotatef(angleCube, 0.0f, 1.0f, 0.0f);
    glColor3f(0.0f, 1.0f, 0.0f);    // change cube1 to green
    glutSolidCube(0.5f);            // cube
    glTranslatef(0.0f, 0.5f, 0.0f); // move cube1 to the top
    glutSolidSphere(0.25f, 20, 20); // sphere
  glPopMatrix();
}

/* This function will replace the previous display function and will be used 
   for scene setup. */
void render3DScene(void) {
  glMatrixMode(GL_MODELVIEW);    // set the ModelView Matrix for scene setup
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  glColor3f(0.0f, 1.0f, 0.0f);  // green
  glTranslatef(0.0f, 0.0f, -1.5f);
  glRotatef(45, 1.0f, 0.0f, 0.0f);
  glutSolidCube(0.5f);

  // TASK 2:
  glutSolidSphere(0.1f, 20, 20);
  glutSolidTorus(0.6f, 1.4f, 20, 20);

  glutSwapBuffers();
}

/* This function will replace the previous display function and will be used 
   for rendering a cube and playing with transformations. */
void renderCube(void) {
  glMatrixMode(GL_MODELVIEW);
  // glClear(GL_DEPTH_BUFFER_BIT); // Helper to be used with drawObjectAlt
  glClear(GL_COLOR_BUFFER_BIT);

  glLoadIdentity();
  //glLoadMatrixf(&mattrans[0][0]);  // slide 16
  //glLoadMatrixf(&matrot[0][0]);    // slide 17

  /* Example 1 - Slide 18 */
  //glMultMatrixf(&mattrans[0][0]);  // translate
  //glMultMatrixf(&matrot[0][0]);    // rotate

  /* Example 2 - Slide 18 */
  //glMultMatrixf(&matrot[0][0]);    // rotate
  //glMultMatrixf(&mattrans[0][0]);  // translate

  /* Example - Slide 19 */ // TASK: 3
  //glScalef(2.0f, 2.0f, 1.0f);          // s
  //glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  // r
  //glTranslatef(1.0f, 0.0f, 0.0f);      // t

  /* Example - Slide 20 */
  //glTranslatef(1.0f, 0.0f, 0.0f);      // t
  //glRotatef(45.0f, 0.0f, 0.0f, 1.0f);  // r
  //glScalef(2.0f, 2.0f, 1.0f);          // s

  //glTranslatef(0.0f, 0.0f, -1.5f);
  //glTranslatef(0.0f, 0.0f, -5.0f);  // we additionally move from camera

  // TASK 5:

  gluLookAt(navX, 0.0f, navZ,      // camera position
            navX, 0.0f, 0.0f,      // target position (at)
            0.0f, 1.0f, 0.0f);     // up vector

  /* HOMEWORK HELPER
  gluLookAt(x, 1.0f, z,            // camera position
    x + lx, 1.0f, z + lz,          // target position (at)
    0.0f, 1.0f, 0.0f);             // up vector
  */

  // TASK 4:
  glTranslatef(0.0f, 0.0f, -5.0f);
  glutSolidCube(0.5);
  glTranslatef(-1.0f, 0.0f, 0.0f);
  drawObject();
  // drawObjectAlt(); // Helper to be used with drawObjectAlt
  glTranslatef(-1.0f, 0.0f, 0.0f);
  drawObject();
  // drawObjectAlt(); // Helper to be used with drawObjectAltt
  glTranslatef(0.0f, 1.0f, 0.0f);
  drawObject();
  // drawObjectAlt(); // Helper to be used with drawObjectAlt

  glutSwapBuffers();
}

/* This function will registered as a callback with glutIdleFunc. Here it will
   be constantly called and perform updates to realise an animation. */
void idleFunc(void) {
  angleCube += 0.1f; // TASK 6:
  glutPostRedisplay();
}

/* This is our main method which will perform the setup of our first OpenGL
   window. The command line parameters will be passed but not used in the
   context of our application. Callbacks have been registered already and
   are prepared for future use during the lab. */
int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowPosition(500, 500); // initial position of the window
  glutInitWindowSize(800, 600);     // initial size of the window
  windowid = glutCreateWindow("Our Second OpenGL Window"); // create window
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  // glEnable(GL_DEPTH_TEST);       // Helper to be used with drawObjectAlt

  // register callbacks
  glutKeyboardFunc(keyboard);
  //glutDisplayFunc(renderPrimitives);// Part 1 - we simply render primitives
  //glutDisplayFunc(render3DScene);  // Part 2 - we start with 3D scene setup
  glutReshapeFunc(reshapeFunc);    // Part 2 - keep reshape for all 3D parts
  glutDisplayFunc(renderCube);     // Part 3 - we play with transformations 
  glutIdleFunc(idleFunc);           // Part 4 - we perform basic animation 
  glutSpecialFunc(processSpecialKeys); // HOMEWORK HELPER

  glutMainLoop(); // start the main loop of GLUT
  return 0;
}