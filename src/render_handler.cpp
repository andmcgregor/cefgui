#include <fstream>
#include "../include/render_handler.h"

RenderHandler::RenderHandler()
{
  initialized = false;
}

void RenderHandler::init(void)
{
  GLuint vertexShader = compileShader(GL_VERTEX_SHADER, "shaders/gui.vert");
  GLuint fragmentShader = compileShader(GL_FRAGMENT_SHADER, "shaders/gui.frag");

  program = glCreateProgram();

  glAttachShader(program, vertexShader);
  glAttachShader(program, fragmentShader);
  glLinkProgram(program);
  glDetachShader(program, vertexShader);
  glDetachShader(program, fragmentShader);

  positionLoc = glGetAttribLocation(program, "position");

  float coords[] = {-1.0,-1.0,-1.0,1.0,1.0,-1.0,1.0,-1.0,-1.0,1.0,1.0,1.0};

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(coords), coords, GL_STATIC_DRAW);
  glEnableVertexAttribArray(positionLoc);
  glVertexAttribPointer(positionLoc, 2, GL_FLOAT, GL_FALSE, 0, 0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  initialized = true;
}

void RenderHandler::draw(void)
{
  glUseProgram(program);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
  glUseProgram(0);
}

void RenderHandler::reshape(int w_, int h_)
{
  w = w_;
  h = h_;
}

bool RenderHandler::GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect)
{
  rect = CefRect(0, 0, w, h);
  return true;
}

void RenderHandler::OnPaint(CefRefPtr<CefBrowser> browser,
                            PaintElementType type,
                            const RectList &dirtyRects,
                            const void* buffer,
                            int width,
                            int height)
{
  glBindTexture(GL_TEXTURE_2D, texture);
  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_BGRA_EXT, GL_UNSIGNED_BYTE, (unsigned char*) buffer);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glBindTexture(GL_TEXTURE_2D, 0);
}

GLuint RenderHandler::compileShader(GLenum shaderType, const char* path)
{
  GLuint shader = glCreateShader(shaderType);

  std::ifstream ifs(path);
  std::string shaderStr( (std::istreambuf_iterator<char>(ifs) ),
                         (std::istreambuf_iterator<char>()  ) );

  const char* shaderData = shaderStr.c_str();

  glShaderSource(shader, 1, &shaderData, NULL);
  glCompileShader(shader);

  GLint status;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &status);
  if (status == GL_FALSE)
    printf("SHADER COMPILE ERROR\n");

  return shader;
}
