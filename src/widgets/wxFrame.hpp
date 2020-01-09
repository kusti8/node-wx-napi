#ifndef WXFRAME_H
#define WXFRAME_H
#include <wx/wx.h>
#include <wx/frame.h>
#include <wx/gdicmn.h>
#include <napi.h>

class WxFrame;
class WxWrapFrame : public wxFrame
{
public:
    WxWrapFrame(int width, int height);
    WxFrame *jsFrame;

    bool closed = false;

private:
    void OnResize(wxSizeEvent &event);
    void OnClose(wxCloseEvent &event);

    DECLARE_EVENT_TABLE()
};

class WxFrame : public Napi::ObjectWrap<WxFrame>
{
public:
    static Napi::Object Init(Napi::Env env, Napi::Object exports);
    WxFrame(const Napi::CallbackInfo &info);

    Napi::FunctionReference OnResizeCallback_;
    Napi::FunctionReference OnCloseCallback_;

private:
    static Napi::FunctionReference constructor;
    Napi::Value Show(const Napi::CallbackInfo &info);
    Napi::Value SetSize(const Napi::CallbackInfo &info);
    Napi::Value GetSize(const Napi::CallbackInfo &info);
    Napi::Value SetLoc(const Napi::CallbackInfo &info);
    Napi::Value OnResize(const Napi::CallbackInfo &info);
    Napi::Value OnClose(const Napi::CallbackInfo &info);
    Napi::Value getClosed(const Napi::CallbackInfo &info);

    WxWrapFrame *frame;
};

#endif