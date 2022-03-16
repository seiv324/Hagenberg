/*---------------------------------------------------------------------------
 * Title: Computer Graphics Lab 1 - OpenGL Setup and Basic GLUT Functionality
 * Author: Christoph Anthes
 * Version: 1.0 (SS22)
 * Time to complete: 45 minutes
 * Additional material: slides, course notes
 *-------------------------------------------------------------------------*/
#include "GL/freeglut.h"
#include "stdio.h"

int windowid; // the identifier of the GLUT window

/* This is our very basic render function which will be called each time the
	 display is updated triggered by registration in glutDisplayFunc. It
	 fills the colour buffer and flips the back buffer to the front.
	 Additionally a clear colour is set. */
void renderScene(void) {
	glClear(GL_COLOR_BUFFER_BIT); // clear the colour buffer
	// TASK 1: yellow 	#FFFF00 	rgb(255,255,0)
	glClearColor(1.0f, 1.0f, 0.0f, 1.0f); // clear colour is yellow
	glutSwapBuffers(); // swap back to front buffer
}

/* This is the keyboard function which is used to react on keyboard input.
   It has to be registered as a callback in glutKeyboardFunc. Once a key is
   pressed it will be invoked and the keycode as well as the current mouse
   coordinates relative to the window origin are passed. */
void keyboard(unsigned char key, int xcoor, int ycoor) {
	switch (key) {
		case 'a':
			printf("You just pressed 'a'\n");
			break;
		case 27: // escape key
			glutDestroyWindow(windowid);
			exit(0);
			break;
		//TASK 2:
		case 'g': 
			glClearColor(0.0f, 1.0f, 0.0f, 1.0f); // clear colour is green
			break;
		case 32: // space bar
			glClearColor(0.0f, 1.0f, 1.0f, 1.0f); // clear colour is cyan
			break;
	}
	glutPostRedisplay(); // explicitly trigger the display callback
}

/* This function acts as callback for mouse click events. It has to be 
   registered as a callback in glutMouseFunc. The parameters passed are the
   buttonid, the current state of the button and the x,y coordinates relative
   to the window origin. The display callback is automatically triggered after
   the mouse callback was invoked. */
void onMouseClick(int buttonid, int buttonstate, int xcoor, int ycoor) {
	if (buttonid == GLUT_MIDDLE_BUTTON && buttonstate == GLUT_DOWN) {
		printf("Middle button clicked at position x: %i y: %i\n", xcoor, ycoor);
	}
	// TASK 2:
	if (buttonid == GLUT_RIGHT_BUTTON && buttonstate == GLUT_DOWN) {
		glClearColor(0.0f, 0.0f, 1.0f, 1.0f); //clear colour is blue
	}
}

/* This is our main method which will perform the setup of our first OpenGL 
   window. The command line parameters will be passed but not used in the 
   context of our application. */
int main(int argc, char **argv) {
	glutInit(&argc, argv); // generic GLUT initialisation
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE ); // setup display mode
	glutInitWindowPosition(500, 500); // initial position of the window
	glutInitWindowSize(800, 600); // initial size of the window
	windowid = glutCreateWindow("OpenGL First Window"); // create window

	// register callbacks
	glutDisplayFunc(renderScene); // the display callback
	glutKeyboardFunc(keyboard); // the keyboard callback
	glutMouseFunc(onMouseClick); // the mouse callback

	glutMainLoop(); // start the main loop of GLUT
	return 0;
}