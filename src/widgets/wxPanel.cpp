#include "wxPanel.hpp"

WxWrapPanel::WxWrapPanel(wxWindow *parent, int width, int height) : wxPanel(parent, wxID_ANY, wxDefaultPosition, wxSize(width, height))
{
    //Centre();
}

BEGIN_EVENT_TABLE(WxWrapPanel, wxPanel)
END_EVENT_TABLE()

Napi::FunctionReference WxPanel::constructor;

Napi::Object WxPanel::Init(Napi::Env env, Napi::Object exports)
{
    Napi::HandleScope scope(env);
    // clang-format off
    Napi::Function func = DefineClass(env, "WxPanel", {
        InstanceMethod("Show", &WxPanel::Show),
        InstanceMethod("SetSize", &WxPanel::SetSize),
        InstanceMethod("GetSize", &WxPanel::GetSize),
        InstanceMethod("SetLoc", &WxPanel::SetLoc),
        InstanceMethod("SetBackgroundColour", &WxPanel::SetBackgroundColour),
        InstanceMethod("GetBestSize", &WxPanel::GetBestSize),
    });
    // clang-format on

    constructor = Napi::Persistent(func);
    constructor.SuppressDestruct();

    exports.Set("WxPanel", func);
    return exports;
}

WxPanel::WxPanel(const Napi::CallbackInfo &info) : Napi::ObjectWrap<WxPanel>(info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    if (info.Length() > 0)
    {
        wxWindow *parent = unwrap(info[0]);
        elem = new WxWrapPanel(parent, 250, 250);
    }
    else
    {
        elem = new WxWrapPanel(NULL, 250, 250);
    }

    elem->jsPanel = this;
}

Napi::Value WxPanel::Show(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->Show(info[0].ToBoolean());

    return Napi::Value();
}

Napi::Value WxPanel::SetSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->SetSize(info[0].ToNumber(), info[1].ToNumber());

    return Napi::Value();
}

Napi::Value WxPanel::GetSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    wxSize size = elem->GetSize();

    Napi::Object out = Napi::Object::New(env);
    out.Set("w", size.GetWidth());
    out.Set("h", size.GetHeight());

    return out;
}

Napi::Value WxPanel::SetLoc(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    elem->SetSize(info[0].ToNumber(), info[1].ToNumber(), wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING);

    return Napi::Value();
}

Napi::Value WxPanel::SetBackgroundColour(const Napi::CallbackInfo &info)
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

Napi::Value WxPanel::GetBestSize(const Napi::CallbackInfo &info) {
    Napi::Env env = info.Env();
    Napi::HandleScope scope(env);

    wxSize size = elem->GetBestSize();

    Napi::Object out = Napi::Object::New(env);
    out.Set("w", size.GetWidth());
    out.Set("h", size.GetHeight());

    return out;
}