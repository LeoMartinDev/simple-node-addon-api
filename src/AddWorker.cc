#include "AddWorker.hh"

AddWorker::AddWorker(Napi::Function &callback, double a, double b)
    : Napi::AsyncWorker(callback), a(a), b(b) {}
AddWorker::~AddWorker(){};

// executé dans le worker-thread
void AddWorker::Execute()
{
    this->result = add(this->a, this->b);
}

// appelé lorsque Execute est terminé
void AddWorker::onOk()
{
    Napi::HandleScope scope(Env());
    Callback().Call({Env().Undefined(),
                     Napi::Number::New(Env(), this->result)});
}