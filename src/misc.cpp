#include "misc.hpp"

void MiscInit(Napi::Env env, Napi::Object exports)
{
    exports.Set("desktopSize", Napi::Function::New(env, desktopSize));
}

Napi::Object desktopSize(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();

    Napi::Object out = Napi::Object::New(env);

    out.Set("w", wxGetDisplaySize().GetWidth());
    out.Set("h", wxGetDisplaySize().GetHeight());

    return out;
}