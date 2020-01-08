#include "wxFrame.hpp"

WxWrapFrame::WxWrapFrame() : wxFrame(NULL, wxID_ANY, wxT("Testing"), wxDefaultPosition, wxSize(250, 150))
{
    //Centre();
}

Napi::FunctionReference WxFrame::constructor;

Napi::Object WxFrame::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "WxFrame", {
        InstanceMethod("Show", &WxFrame::Show),
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("WxFrame", func);
    return exports;
}

WxFrame::WxFrame(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WxFrame>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    frame = new WxWrapFrame();
    frame->jsFrame = this;
}

Napi::Value WxFrame::Show(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    frame->Show(info[0].As<Napi::Boolean>());

    return Napi::Value();
}