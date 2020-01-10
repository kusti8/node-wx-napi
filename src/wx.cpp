#include <napi.h>
#include "widgets/wxApp.hpp"
#include "widgets/wxFrame.hpp"
#include "widgets/wxPanel.hpp"
#include "widgets/wxButton.hpp"
#include "misc.hpp"
#include <wx/wx.h>

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    WxApp::Init(env, exports);
    WxFrame::Init(env, exports);
    WxPanel::Init(env, exports);
    WxButton::Init(env, exports);
    MiscInit(env, exports);
    return exports;
}

NODE_API_MODULE(NODE_GYP_MODULE_NAME, Init)

// DECLARE_APP(WxWrapApp)
// IMPLEMENT_APP_NO_MAIN(WxWrapApp)

// static WxWrapApp *_app = NULL;
// wxAppConsole *wxCreateApp() { return _app; }
// wxAppInitializer wxTheAppInitializer((wxAppInitializerFunction)wxCreateApp);