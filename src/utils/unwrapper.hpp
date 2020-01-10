#ifndef UNWRAPPER_H
#define UNWRAPPER_H
#include <wx/wx.h>
#include <wx/window.h>
#include "napi.h"
#include <iostream>
#include "../widgets/wxFrame.hpp"
#include "../widgets/wxPanel.hpp"

wxWindow *unwrap(Napi::Value object);

#endif