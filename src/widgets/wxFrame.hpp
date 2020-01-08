#ifndef WXFRAME_H
#define WXFRAME_H
#include <wx/wx.h>
#include <wx/frame.h>
#include <napi.h>

class WxFrame;
class WxWrapFrame : public wxFrame
{
public:
    WxWrapFrame();
    WxFrame *jsFrame;
};

class WxFrame : public Napi::ObjectWrap<WxFrame>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    WxFrame(const Napi::CallbackInfo &info);

private:
    static Napi::FunctionReference constructor;
    Napi::Value Show(const Napi::CallbackInfo &info);

    WxWrapFrame *frame;
};

#endif