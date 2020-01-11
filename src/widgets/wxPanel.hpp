#ifndef WXPANEL_H
#define WXPANEL_H
#include <wx/wx.h>
#include <wx/panel.h>
#include <wx/window.h>
#include <napi.h>
#include "wxWindow_macros.hpp"
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

    // WxWindow Funcs
    WXWINDOW_DEFS
};

#endif