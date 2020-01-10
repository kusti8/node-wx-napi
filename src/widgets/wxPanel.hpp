#ifndef WXPANEL_H
#define WXPANEL_H
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/window.h>
#include <napi.h>
#include "../utils/unwrapper.hpp"

class WxPanel;
class WxWrapPanel : public wxPanel
{
public:
    WxWrapPanel(wxWindow *parent, int width, int height);
    WxPanel *jsPanel;

private:
    DECLARE_EVENT_TABLE()
};

class WxPanel : public Napi::ObjectWrap<WxPanel>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    WxPanel(const Napi::CallbackInfo &info);

    WxWrapPanel *elem;

private:
    static Napi::FunctionReference constructor;
    Napi::Value Show(const Napi::CallbackInfo &info);
    Napi::Value SetSize(const Napi::CallbackInfo &info);
    Napi::Value GetSize(const Napi::CallbackInfo &info);
    Napi::Value SetLoc(const Napi::CallbackInfo &info);
    Napi::Value SetBackgroundColour(const Napi::CallbackInfo &info);
    Napi::Value GetBestSize(const Napi::CallbackInfo &info);
};

#endif