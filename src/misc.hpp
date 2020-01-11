#ifndef MISC_H
#define MISC_H
#include <napi.h>
#include <wx/wx.h>
#include <wx/display.h>
#include <wx/gdicmn.h>

void MiscInit(Napi::Env env, Napi::Object exports);

Napi::Object desktopSize(const Napi::CallbackInfo &info);

#endif