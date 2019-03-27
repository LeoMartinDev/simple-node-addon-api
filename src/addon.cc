#include "addon.hh"

Napi::Value addCallback(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double a;
    double b;

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Arguments 'a' and 'b' must be of type 'Number'").ThrowAsJavaScriptException();
        return env.Null();
    }
    a = info[0].As<Napi::Number>().DoubleValue();
    b = info[1].As<Napi::Number>().DoubleValue();
    return Napi::Number::New(env, add(a, b));
}

Napi::Value addAsyncCallback(const Napi::CallbackInfo &info)
{
    Napi::Env env = info.Env();
    double a;
    double b;
    Napi::Function callback;
    AddWorker *worker;

    if (info.Length() < 2)
    {
        Napi::TypeError::New(env, "Invalid number of arguments").ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[0].IsNumber() || !info[1].IsNumber())
    {
        Napi::TypeError::New(env, "Arguments 'a' and 'b' must be of type 'Number'").ThrowAsJavaScriptException();
        return env.Null();
    }
    if (!info[2].IsFunction())
    {
        Napi::TypeError::New(env, "Arguments 'callback' must be of type 'Function'").ThrowAsJavaScriptException();
        return env.Null();
    }
    a = info[0].As<Napi::Number>().DoubleValue();
    b = info[1].As<Napi::Number>().DoubleValue();
    callback = info[1].As<Napi::Function>();
    worker = new AddWorker(callback, a, b);
    worker->Queue();
    return env.Null();
}

Napi::Object Init(Napi::Env env, Napi::Object exports)
{
    exports.Set(Napi::String::New(env, "add"),
                Napi::Function::New(env, addCallback));
    exports.Set(Napi::String::New(env, "addAsync"),
                Napi::Function::New(env, addAsyncCallback));
    return exports;
}

NODE_API_MODULE(addon, Init)