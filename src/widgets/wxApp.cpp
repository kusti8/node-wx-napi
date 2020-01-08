#include "wxApp.hpp"

int argc = 0;
char **argv = NULL;

bool WxWrapApp::OnInit()
{
    printf("Called oninit\n");
    jsApp->OnInitCallback_.Call({});
    return true;
}

Napi::FunctionReference WxApp::constructor;

Napi::Object WxApp::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "WxApp", {
        InstanceMethod("loop", &WxApp::loop),
        InstanceMethod("OnInit", &WxApp::OnInit),
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("WxApp", func);
    return exports;
}

WxApp::WxApp(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WxApp>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    app = new WxWrapApp();
    app->jsApp = this;

    wxEventLoop *loop = new wxEventLoop();
    wxEventLoop::SetActive(loop);

    wxEntryStart(argc, argv);
}

Napi::Value WxApp::OnInit(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    OnInitCallback_ = Napi::Persistent(info[0].As<Napi::Function>());

    return Napi::Value();
}

Napi::Value WxApp::loop(const Napi::CallbackInfo &info)
{
    wxEventLoopBase *evtLoop = wxEventLoop::GetActive();
    if (evtLoop)
    {
        while (evtLoop->DispatchTimeout(1) != -1)
        {
        }
    }
    return Napi::Value();
}