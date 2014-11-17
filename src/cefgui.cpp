#include "../include/cefgui.h"

Cefgui* initCefgui(int argc, char** argv)
{
  CefMainArgs args(argc, argv);
  CefExecuteProcess(args, nullptr, NULL);

  CefSettings settings;

  // TODO make cross platform
  CefString(&settings.locales_dir_path) = "cef/linux/lib/locales";

  CefInitialize(args, settings, nullptr, NULL);

  return new Cefgui();
}

Cefgui::Cefgui()
{
  CefWindowInfo windowInfo;
  CefBrowserSettings settings;

  windowInfo.SetAsOffScreen(nullptr);
  windowInfo.SetTransparentPainting(true);

  renderHandler = new RenderHandler();

  client = new BrowserClient(renderHandler);
  browser = CefBrowserHost::CreateBrowserSync(windowInfo, client.get(), "", settings, nullptr);
}

void Cefgui::draw(void)
{
  CefDoMessageLoopWork();
  renderHandler->draw();
}

void Cefgui::load(const char* url)
{
  if (!renderHandler->initialized)
    renderHandler->init();

  browser->GetMainFrame()->LoadURL(url);
}

void Cefgui::setWindowSize(int w, int h)
{
  renderHandler->setWindowSize(w, h);
}
