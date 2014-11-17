#include "../cef/linux/include/cef_app.h"

#include "browser_client.h"
#include "render_handler.h"

#ifndef CEFGUI_H
#define CEFGUI_H

class Cefgui;

Cefgui* initCefgui(int argc, char** argv);

class Cefgui {
  public:
    Cefgui();

    void draw(void);

    void load(const char* url);

    void setWindowSize(int, int);

  private:
    CefRefPtr<CefBrowser> browser;
    CefRefPtr<BrowserClient> client;

    RenderHandler* renderHandler;

};

#endif
