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

void Cefgui::load(const char* url)
{
  if (!renderHandler->initialized)
    renderHandler->init();

  browser->GetMainFrame()->LoadURL(url);
}

void Cefgui::draw(void)
{
  CefDoMessageLoopWork();
  renderHandler->draw();
}

void Cefgui::reshape(int w, int h)
{
  renderHandler->reshape(w, h);
  browser->GetHost()->WasResized();
}

void Cefgui::mouseMove(int x, int y)
{
  CefMouseEvent event;
  event.x = x;
  event.y = y;

  browser->GetHost()->SendMouseMoveEvent(event, false);
}

void Cefgui::mouseClick(int btn, int state, int x, int y)
{
  CefMouseEvent event;
  event.x = x;
  event.y = y;

  bool mouseUp = state == 1;
  CefBrowserHost::MouseButtonType btnType = MBT_LEFT;
  browser->GetHost()->SendMouseClickEvent(event, btnType, mouseUp, 1);
}

void Cefgui::keyPress(unsigned char key)
{
  CefKeyEvent event;
  event.native_key_code = (int) key;
  event.type = KEYEVENT_KEYDOWN;

  browser->GetHost()->SendKeyEvent(event);
}
