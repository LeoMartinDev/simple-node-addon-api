#ifndef ADD_WORKER_HH
#define ADD_WORKER_HH

#include <napi.h>
#include "addon.hh"

class AddWorker : public Napi::AsyncWorker
{
  public:
    AddWorker(Napi::Function &callback, double a, double b);
    ~AddWorker();

    // executé dans le worker-thread
    void Execute();
    // appelé lorsque Execute est terminé
    void onOk();

  private:
    double a;
    double b;
    double result;
};

#endif