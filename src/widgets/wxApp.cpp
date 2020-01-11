#include "wxApp.hpp"

int argc = 0;
char **argv = NULL;

bool WxWrapApp::OnInit()
{
    printf("Called oninit\n");
    if (!jsApp->OnInitCallback_.IsEmpty())
        jsApp->OnInitCallback_.Call({});
    printf("done oninit\n");
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

    //
    //wxInitialize();

    elem = new WxWrapApp();
    elem->jsApp = this;
    wxApp::SetInstance(elem);

    // printf("In app\n");

    wxEventLoop *loop = new wxEventLoop();
    wxEventLoop::SetActive(loop);

    // printf("Past loop\n");

    if (!wxEntryStart(argc, argv))
    {
        //cerr << "wx failed to start\n";
        printf("Failed to strart\n");
        wxExit();
    }

    // printf("Calling init\n");
    //wxTheApp->CallOnInit();
    // printf("Past init\n");
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