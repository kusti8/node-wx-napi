#include "wxButton.hpp"

WxWrapButton::WxWrapButton(wxWindow *parent) : wxButton(parent, wxID_ANY)
{
}

void WxWrapButton::OnPress(wxCommandEvent &event)
{

    if (jsButton->OnPressCallback_.IsEmpty())
        return;

    jsButton->OnPressCallback_.Call({});
}

BEGIN_EVENT_TABLE(WxWrapButton, wxButton)
EVT_BUTTON(wxID_ANY, WxWrapButton::OnPress)
END_EVENT_TABLE()

Napi::FunctionReference WxButton::constructor;

Napi::Object WxButton::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "WxButton", {
        InstanceMethod("SetLabel", &WxButton::SetLabel),
        InstanceMethod("OnPress", &WxButton::OnPress),
        WXWINDOW_JS_DEFINES(WxButton)
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("WxButton", func);
    return exports;
}

WxButton::WxButton(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WxButton>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        wxWindow *parent = unwrap(info[0]);
        elem = new WxWrapButton(parent);
    }
    else
    {
        elem = new WxWrapButton(NULL);
    }

    elem->jsButton = this;
}

Napi::Value WxButton::SetLabel(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->SetLabel(info[0].ToString().Utf8Value());

    return Napi::Value();
}

Napi::Value WxButton::OnPress(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    OnPressCallback_ = Napi::Persistent(info[0].As<Napi::Function>());

    return Napi::Value();
}

WXWINDOW_BASE_FUNCS(WxButton)