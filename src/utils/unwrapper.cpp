#include "unwrapper.hpp"

wxWindow *unwrap(Napi::Value object)
{
    std::string constructor_name = object.ToObject().Get("constructor").ToObject().Get("name").ToString().Utf8Value();

    if (constructor_name == "WxFrame")
        return Napi::ObjectWrap<WxFrame>::Unwrap(object.ToObject())->elem;
    if (constructor_name == "WxPanel")
        return Napi::ObjectWrap<WxPanel>::Unwrap(object.ToObject())->elem;
    return NULL;
}