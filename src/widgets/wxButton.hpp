#ifndef WXButton_H
#define WXButton_H
#include <wx/wx.h>
#include <wx/button.h>
#include <wx/window.h>
#include <napi.h>
#include "wxWindow_macros.hpp"
#include "../utils/unwrapper.hpp"

class WxButton;
class WxWrapButton : public wxButton
{
public:
    WxWrapButton(wxWindow *parent);
    WxButton *jsButton;

private:
    void OnPress(wxCommandEvent &event);

    DECLARE_EVENT_TABLE()
};

class WxButton : public Napi::ObjectWrap<WxButton>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    WxButton(const Napi::CallbackInfo &info);

    Napi::FunctionReference OnPressCallback_;

    WxWrapButton *elem;

private:
    static Napi::FunctionReference constructor;
    Napi::Value SetLabel(const Napi::CallbackInfo &info);
    Napi::Value OnPress(const Napi::CallbackInfo &info);

    // WxWindow Funcs
    WXWINDOW_DEFS
};

#endif