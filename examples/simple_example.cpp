#include <cstdio>

#include <GL/glew.h>
#include <GL/gl.h>
#include <GLFW/glfw3.h>

#include "../include/cefgui.h"

Cefgui* cefgui;

void display(GLFWwindow* window)
{
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  // draw browser to screen
  cefgui->draw();

  glfwSwapBuffers(window);
  glfwPollEvents();
}

void reshape(GLFWwindow* window, int w, int h)
{
  // set browser size
  cefgui->reshape(w, h);
  glViewport(0, 0, (GLsizei) w, (GLsizei) h);
}

void mouse(GLFWwindow* window, int btn, int state, int mods)
{
  // send mouse click to browser

  cefgui->mouseClick(btn, GLFW_PRESS);
  cefgui->mouseClick(btn, GLFW_RELEASE);
}

void motion(GLFWwindow* window, double x, double y)
{
  // send mouse movement to browser
  cefgui->mouseMove((int) x, (int) y);
}

void keyboard(GLFWwindow* window, int key, int scancode, int action, int mods)
{
  // send key press to browser
  cefgui->keyPress(key);
}

int main(int argc, char** argv)
{
  // initialize cefgui
  cefgui = initCefgui(argc, argv);

  if (!glfwInit())
    exit(EXIT_FAILURE);

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow* window = glfwCreateWindow(1000, 1000, "simple example", NULL, NULL);

  glfwMakeContextCurrent(window);

  glfwSetFramebufferSizeCallback(window, reshape);
  glfwSetCursorPosCallback(window, motion);
  glfwSetMouseButtonCallback(window, mouse);
  glfwSetKeyCallback(window, keyboard);

  glClearColor(0.0, 0.0, 0.0, 0.0);

  glewExperimental = true;
  glewInit();

  // set window size & url
  cefgui->reshape(1000, 1000);
  cefgui->load("http://www.google.com");

  while (!glfwWindowShouldClose(window)) {
    display(window);
  }

  return 0;
}
