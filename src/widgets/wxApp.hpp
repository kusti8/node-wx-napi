#ifndef WXAPP_H
#define WXAPP_H
#include <wx/wx.h>
#include <wx/evtloop.h>
#include <wx/window.h>
#include <napi.h>
#include "../utils/unwrapper.hpp"

class WxApp;
class WxWrapApp : public wxApp
{
public:
    WxApp *jsApp;
    virtual bool OnInit();
};

class WxApp : public Napi::ObjectWrap<WxApp>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    WxApp(const Napi::CallbackInfo &info);

    Napi::FunctionReference OnInitCallback_;

    WxWrapApp *elem;

private:
    static Napi::FunctionReference constructor;
    Napi::Value OnInit(const Napi::CallbackInfo &info);
    Napi::Value loop(const Napi::CallbackInfo &info);
};

#endif