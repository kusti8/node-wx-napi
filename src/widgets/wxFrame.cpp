#include "wxFrame.hpp"

WxWrapFrame::WxWrapFrame(wxWindow *parent, int width, int height) : wxFrame(parent, wxID_ANY, wxT(""), wxDefaultPosition, wxSize(width, height))
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

    jsFrame->closed = true; // super slow setting own instance variables for some reason, so we have to set the JS wrapper
    // would love to understand why one day

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
        InstanceMethod("OnResize", &WxFrame::OnResize),
        InstanceMethod("OnClose", &WxFrame::OnClose),
        InstanceMethod("getClosed", &WxFrame::getClosed),
        InstanceMethod("Close", &WxFrame::Close),
        WXWINDOW_JS_DEFINES(WxFrame)
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

    if (info.Length() > 0)
    {
        wxWindow *parent = unwrap(info[0]);
        elem = new WxWrapFrame(parent, 250, 250);
    }
    else
    {
        elem = new WxWrapFrame(NULL, 250, 250);
    }

    elem->jsFrame = this;
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

    return Napi::Boolean::New(env, closed);
}

Napi::Value WxFrame::Close(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (!closed)
        elem->Close();

    return Napi::Value();
}

WXWINDOW_BASE_FUNCS(WxFrame)