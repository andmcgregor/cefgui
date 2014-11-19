#include <cstdio>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "../include/cefgui.h"

Cefgui* cefgui;

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw browser to screen
  cefgui->draw();

  glutSwapBuffers();
  glutPostRedisplay();
}

void reshape(int w, int h)
{
  // set browser size
  cefgui->reshape(w, h);
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void mouse(int btn, int state, int x, int y)
{
  // send mouse click to browser
  cefgui->mouseClick(btn, state, x, y);
}

void motion(int x, int y)
{
  // send mouse movement to browser
  cefgui->mouseMove(x, y);
}

void keyboard(unsigned char key, int x, int y)
{
  // send key press to browser
  cefgui->keyPress(key);
}

int main(int argc, char** argv)
{
  // initialize cefgui
  cefgui = initCefgui(argc, argv);

  glutInit(&argc, argv);

  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitContextVersion(3, 2);
  glutInitContextProfile(GLUT_CORE_PROFILE);

  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(200, 200);

  glutCreateWindow("simple example");

  glewExperimental = true;
  glewInit();

  glClearColor(0.0, 0.0, 0.0, 0.0);

  // set window size & url
  cefgui->reshape(1000, 1000);
  cefgui->load("http://www.google.com");

  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMouseFunc(mouse);
  glutPassiveMotionFunc(motion);
  glutKeyboardFunc(keyboard);

  glutMainLoop();

  return 0;
}
