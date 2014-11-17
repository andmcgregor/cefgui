#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/freeglut.h>

#include "../cef/linux/include/cef_render_handler.h"

#ifndef RENDER_HANDLER_H
#define RENDER_HANDLER_H

class RenderHandler : public CefRenderHandler {
  public:
    RenderHandler();

    bool initialized;

    void init(void);

    void draw(void);

    void setWindowSize(int, int);

    bool GetViewRect(CefRefPtr<CefBrowser> browser, CefRect &rect);

    void OnPaint(CefRefPtr<CefBrowser> browser,
                 PaintElementType type,
                 const RectList &dirtyRects,
                 const void* buffer,
                 int width,
                 int height);

  private:
    int w, h;

    GLuint program, vao, vbo, texture;

    GLuint compileShader(GLenum, const char*);

    IMPLEMENT_REFCOUNTING(RenderHandler);

};

#endif
