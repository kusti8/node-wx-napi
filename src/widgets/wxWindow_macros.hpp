#ifndef WXWINDOW_MACROS_H
#define WXWINDOW_MACROS_H

///////////////////////////////////////
// Common WxWindow Functions
///////////////////////////////////////
#define WXWINDOW_DEFS                                                \
    Napi::Value Show(const Napi::CallbackInfo &info);                \
    Napi::Value SetSize(const Napi::CallbackInfo &info);             \
    Napi::Value GetSize(const Napi::CallbackInfo &info);             \
    Napi::Value SetLoc(const Napi::CallbackInfo &info);              \
    Napi::Value SetBackgroundColour(const Napi::CallbackInfo &info); \
    Napi::Value GetBestSize(const Napi::CallbackInfo &info);

///////////////////////////////////////
// Common WxWindow Functions Defines for JS
///////////////////////////////////////
#define WXWINDOW_JS_DEFINES(className)                                          \
    InstanceMethod("Show", &className::Show),                                   \
        InstanceMethod("SetSize", &className::SetSize),                         \
        InstanceMethod("GetSize", &className::GetSize),                         \
        InstanceMethod("SetLoc", &className::SetLoc),                           \
        InstanceMethod("SetBackgroundColour", &className::SetBackgroundColour), \
        InstanceMethod("GetBestSize", &className::GetBestSize),

///////////////////////////////////////
// Common WxWindow Function Implementations
///////////////////////////////////////
#define WXWINDOW_BASE_FUNCS(className)                                                                              \
                                                                                                                    \
    Napi::Value className::Show(const Napi::CallbackInfo &info)                                                     \
    {                                                                                                               \
        Napi::Env env = info.Env();                                                                                 \
        Napi::HandleScope scope(env);                                                                               \
                                                                                                                    \
        elem->Show(info[0].ToBoolean());                                                                            \
                                                                                                                    \
        return Napi::Value();                                                                                       \
    }                                                                                                               \
                                                                                                                    \
    Napi::Value className::SetSize(const Napi::CallbackInfo &info)                                                  \
    {                                                                                                               \
        Napi::Env env = info.Env();                                                                                 \
        Napi::HandleScope scope(env);                                                                               \
                                                                                                                    \
        elem->SetSize(info[0].ToNumber(), info[1].ToNumber());                                                      \
                                                                                                                    \
        return Napi::Value();                                                                                       \
    }                                                                                                               \
                                                                                                                    \
    Napi::Value className::GetSize(const Napi::CallbackInfo &info)                                                  \
    {                                                                                                               \
        Napi::Env env = info.Env();                                                                                 \
        Napi::HandleScope scope(env);                                                                               \
                                                                                                                    \
        wxSize size = elem->GetSize();                                                                              \
                                                                                                                    \
        Napi::Object out = Napi::Object::New(env);                                                                  \
        out.Set("w", size.GetWidth());                                                                              \
        out.Set("h", size.GetHeight());                                                                             \
                                                                                                                    \
        return out;                                                                                                 \
    }                                                                                                               \
                                                                                                                    \
    Napi::Value className::SetLoc(const Napi::CallbackInfo &info)                                                   \
    {                                                                                                               \
        Napi::Env env = info.Env();                                                                                 \
        Napi::HandleScope scope(env);                                                                               \
                                                                                                                    \
        elem->SetSize(info[0].ToNumber(), info[1].ToNumber(), wxDefaultCoord, wxDefaultCoord, wxSIZE_USE_EXISTING); \
                                                                                                                    \
        return Napi::Value();                                                                                       \
    }                                                                                                               \
                                                                                                                    \
    Napi::Value className::SetBackgroundColour(const Napi::CallbackInfo &info)                                      \
    {                                                                                                               \
        Napi::Env env = info.Env();                                                                                 \
        Napi::HandleScope scope(env);                                                                               \
                                                                                                                    \
        int r = info[0].ToNumber();                                                                                 \
        int g = info[1].ToNumber();                                                                                 \
        int b = info[2].ToNumber();                                                                                 \
                                                                                                                    \
        unsigned long color = ((b & 0xff) << 16) + ((g & 0xff) << 8) + (r & 0xff);                                  \
                                                                                                                    \
        elem->SetBackgroundColour(wxColour(color));                                                                 \
                                                                                                                    \
        return Napi::Value();                                                                                       \
    }                                                                                                               \
                                                                                                                    \
    Napi::Value className::GetBestSize(const Napi::CallbackInfo &info)                                              \
    {                                                                                                               \
        Napi::Env env = info.Env();                                                                                 \
        Napi::HandleScope scope(env);                                                                               \
                                                                                                                    \
        wxSize size = elem->GetBestSize();                                                                          \
                                                                                                                    \
        Napi::Object out = Napi::Object::New(env);                                                                  \
        out.Set("w", size.GetWidth());                                                                              \
        out.Set("h", size.GetHeight());                                                                             \
                                                                                                                    \
        return out;                                                                                                 \
    }

#endif