#ifndef WXButton_H
#define WXButton_H
#include <wx/wx.h>
#include <wx/button.h>
#include <wx/window.h>
#include <napi.h>
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
    Napi::Value Show(const Napi::CallbackInfo &info);
    Napi::Value SetSize(const Napi::CallbackInfo &info);
    Napi::Value GetSize(const Napi::CallbackInfo &info);
    Napi::Value SetLoc(const Napi::CallbackInfo &info);
    Napi::Value SetBackgroundColour(const Napi::CallbackInfo &info);
    Napi::Value SetLabel(const Napi::CallbackInfo &info);
    Napi::Value OnPress(const Napi::CallbackInfo &info);
    Napi::Value GetBestSize(const Napi::CallbackInfo &info);
};

#endif