#include <napi.h>
#include "widgets/wxApp.hpp"
#include "widgets/wxFrame.hpp"
#include <wx/wx.h>

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    WxApp::Init(env, exports);
    WxFrame::Init(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

DECLARE_APP(WxWrapApp)
IMPLEMENT_APP_NO_MAIN(WxWrapApp)

// static WxWrapApp *_app = NULL;
// wxApp *wxCreateApp() { return _app; }
// wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction)wxCreateApp);