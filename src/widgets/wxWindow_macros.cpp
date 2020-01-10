#ifndef WXWINDOW_MACROS_H
#define WXWINDOW_MACROS_H

///////////////////////////////////////
// Common WxWindow Functions
///////////////////////////////////////
#define WXWINDOW_DEFS \
    Napi::Value Show(const Napi::CallbackInfo &info); \
    Napi::Value SetSize(const Napi::CallbackInfo &info); \
    Napi::Value GetSize(const Napi::CallbackInfo &info); \
    Napi::Value SetLoc(const Napi::CallbackInfo &info); \
    Napi::Value SetBackgroundColour(const Napi::CallbackInfo &info); \
    Napi::Value GetBestSize(const Napi::CallbackInfo &info); \
    Napi::Value Close(const Napi::CallbackInfo &info);

///////////////////////////////////////
// Common WxWindow Functions Defines for JS
///////////////////////////////////////
#define QWIDGET_JS_DEFINES(className)                                     \
    InstanceMethod("Show", &className::Show),                         \
    InstanceMethod("SetSize", &className::SetSize),                         \
    InstanceMethod("GetSize", &className::GetSize),                       \
    InstanceMethod("SetLoc", &className::SetLoc),                         \
    InstanceMethod("SetBackgroundColour", &className::SetBackgroundColour),                       \
    InstanceMethod("GetBestSize", &className::GetBestSize),                     \
    InstanceMethod("Close", &className::Close),

///////////////////////////////////////
// Common QWidget Function Implementations
///////////////////////////////////////
#define QWIDGET_BASE_FUNCS(className)                                                 \