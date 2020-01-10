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
        InstanceMethod("Show", &WxButton::Show),
        InstanceMethod("SetSize", &WxButton::SetSize),
        InstanceMethod("GetSize", &WxButton::GetSize),
        InstanceMethod("SetLoc", &WxButton::SetLoc),
        InstanceMethod("SetBackgroundColour", &WxButton::SetBackgroundColour),
        InstanceMethod("SetLabel", &WxButton::SetLabel),
        InstanceMethod("OnPress", &WxButton::OnPress),
        InstanceMethod("GetBestSize", &WxButton::GetBestSize),
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

Napi::Value WxButton::Show(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->Show(info[0].ToBoolean());

    return Napi::Value();
}

Napi::Value WxButton::SetSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->SetSize(info[0].ToNumber(), info[1].ToNumber());

    return Napi::Value();
}

Napi::Value WxButton::GetSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    wxSize size = elem->GetSize();

    Napi::Object out = Napi::Object::New(env);
    out.Set("w", size.GetWidth());
    out.Set("h", size.GetHeight());

    return out;
}

Napi::Value WxButton::SetLoc(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->SetSize(info[0].ToNumber(), info[1].ToNumber(), wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING);

    return Napi::Value();
}

Napi::Value WxButton::SetBackgroundColour(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    int r = info[0].ToNumber();
    int g = info[1].ToNumber();
    int b = info[2].ToNumber();

    unsigned long color = ((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);

    elem->SetBackgroundColour(wxColour(color));

    return Napi::Value();
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

Napi::Value WxButton::GetBestSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    wxSize size = elem->GetBestSize();

    Napi::Object out = Napi::Object::New(env);
    out.Set("w", size.GetWidth());
    out.Set("h", size.GetHeight());

    return out;
}