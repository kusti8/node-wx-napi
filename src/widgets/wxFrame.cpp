#include "wxFrame.hpp"

WxWrapFrame::WxWrapFrame(int width, int height) : wxFrame(NULL, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(width, height))
{
    //Centre();
}

void WxWrapFrame::OnResize(wxSizeEvent &event)
{
    wxSize size = event.GetSize();

    if (jsFrame->OnResizeCallback_.IsEmpty())
        return;

    jsFrame->OnResizeCallback_.Call({Napi::Number::New(jsFrame->Env(), size.GetWidth()),
                                     Napi::Number::New(jsFrame->Env(), size.GetHeight())});
}

void WxWrapFrame::OnClose(wxCloseEvent &event)
{
    if (!jsFrame->OnCloseCallback_.IsEmpty())
    {
        jsFrame->OnCloseCallback_.Call({});
    }

    closed = true;

    event.Skip();
}

BEGIN_EVENT_TABLE(WxWrapFrame, wxFrame)
EVT_SIZE(WxWrapFrame::OnResize)
EVT_CLOSE(WxWrapFrame::OnClose)
END_EVENT_TABLE()

Napi::FunctionReference WxFrame::constructor;

Napi::Object WxFrame::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "WxFrame", {
        InstanceMethod("Show", &WxFrame::Show),
        InstanceMethod("SetSize", &WxFrame::SetSize),
        InstanceMethod("GetSize", &WxFrame::GetSize),
        InstanceMethod("SetLoc", &WxFrame::SetLoc),
        InstanceMethod("OnResize", &WxFrame::OnResize),
        InstanceMethod("OnClose", &WxFrame::OnClose),
        InstanceMethod("getClosed", &WxFrame::getClosed),
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

    int width = 250;
    int height = 250;
    if (info.Length() >= 2)
    {
        width = info[0].ToNumber();
        height = info[1].ToNumber();
    }

    frame = new WxWrapFrame(width, height);
    frame->jsFrame = this;
}

Napi::Value WxFrame::Show(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    frame->Show(info[0].ToBoolean());

    return Napi::Value();
}

Napi::Value WxFrame::SetSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    frame->SetSize(info[0].ToNumber(), info[1].ToNumber());

    return Napi::Value();
}

Napi::Value WxFrame::GetSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    wxSize size = frame->GetSize();

    Napi::Object out = Napi::Object::New(env);
    out.Set("w", size.GetWidth());
    out.Set("h", size.GetHeight());

    return out;
}

Napi::Value WxFrame::SetLoc(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    frame->SetSize(info[0].ToNumber(), info[1].ToNumber(), wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING);

    return Napi::Value();
}

Napi::Value WxFrame::OnResize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    OnResizeCallback_ = Napi::Persistent(info[0].As<Napi::Function>());

    return Napi::Value();
}

Napi::Value WxFrame::OnClose(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    OnCloseCallback_ = Napi::Persistent(info[0].As<Napi::Function>());

    return Napi::Value();
}

Napi::Value WxFrame::getClosed(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    return Napi::Boolean::New(env, frame->closed);
}