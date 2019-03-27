#ifndef ADDON_HH
#define ADDON_HH

#include <napi.h>
#include "lib.hh"
#include "AddWorker.hh"

Napi::Value addCallback(const Napi::CallbackInfo &info);

Napi::Value addAsyncCallback(const Napi::CallbackInfo &info);

#endif