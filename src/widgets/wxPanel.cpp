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
        WXWINDOW_JS_DEFINES(WxPanel)
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

WXWINDOW_BASE_FUNCS(WxPanel)