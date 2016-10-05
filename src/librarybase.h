#pragma once
#include <nan.h>
#include <dynload.h>
#include <memory>
#include "locker.h"
#include "instance.h"

namespace fastcall {
struct Loop;

struct LibraryBase : public Nan::ObjectWrap, Instance {
    static NAN_MODULE_INIT(Init);
    
    Lock AcquireLock();
    void EnsureAsyncSupport();
    Loop* GetLoop();

private:
    static Nan::Persistent<v8::Function> constructor;

    DLLib* pLib = nullptr;
    Locker locker;
    std::unique_ptr<Loop> loop;

    static NAN_METHOD(New);

    static NAN_METHOD(initialize);
    static NAN_METHOD(free);
    static NAN_METHOD(_synchronize);

    static DLLib* FindPLib(const v8::Local<v8::Object>& self);
};

inline Loop* LibraryBase::GetLoop()
{
    EnsureAsyncSupport();
    return loop.get();
}
}
