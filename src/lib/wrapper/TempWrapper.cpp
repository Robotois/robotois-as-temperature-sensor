#include <node.h>
#include "TempWrapper.h"

using namespace v8;

Persistent<Function> TempWrapper::constructor;

TempWrapper::TempWrapper(uint8_t _addr){
  sensor = new TemperatureSensor(_addr);
}

TempWrapper::~TempWrapper(){
  // delete tempSensor;
}

// void TempWrapper::release(const FunctionCallbackInfo<Value>& args){
//   Isolate* isolate = Isolate::GetCurrent();
//   HandleScope scope(isolate);
//
//   TempWrapper* temp_obj = ObjectWrap::Unwrap<TempWrapper>(args.Holder());
//   temp_obj->tempSensor->release();
//   delete temp_obj->tempSensor;
// }

void TempWrapper::Init(){
  Isolate* isolate = Isolate::GetCurrent();
  // Prepare consructor template
  Local<FunctionTemplate> tpl = FunctionTemplate::New(isolate,New);
  tpl->SetClassName(String::NewFromUtf8(isolate,"TempWrapper"));
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  NODE_SET_PROTOTYPE_METHOD(tpl,"getInfo",getInfo);
  NODE_SET_PROTOTYPE_METHOD(tpl,"reading", reading);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"getIntValue",getIntValue);
  // NODE_SET_PROTOTYPE_METHOD(tpl,"release",release);

  constructor.Reset(isolate,tpl->GetFunction());
}

void TempWrapper::New(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _addr = 0x00;
  // If there are two params: First Param => i2c address, second => Port number
  // - Only one Param, this means that the given param is the Port Number,
  // printf("Args Count: %d\n",args.Length());
  TempWrapper* obj;
  uint8_t _argc = args.Length();
  if(args.IsConstructCall()){
    // Invoked as constructor: `new MyObject(...)`
    switch(_argc){
      case 1:
        _addr = (uint8_t) args[0]->NumberValue();
        obj = new TempWrapper(_addr);
        obj->Wrap(args.This());
        args.GetReturnValue().Set(args.This());
        break;
      default:
        isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate, "[PhSensor] - Wrong arguments...")));
    }
  }else{
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    if(_argc > 1){
      isolate->ThrowException(Exception::TypeError(
      String::NewFromUtf8(isolate, "[phSensor] - Wrong arguments...")));
    }
    Local<Value>* argv = new Local<Value>[_argc];
    for(uint8_t i = 0; i < _argc; i++){
      argv[i] = args[i];
    }
    Local<Function> cons = Local<Function>::New(isolate, constructor);
    args.GetReturnValue().Set(cons->NewInstance(_argc, argv));
  }
}

void TempWrapper::NewInstance(const FunctionCallbackInfo<Value>& args) {
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  uint8_t _argc = args.Length();
  // printf("Args Count: %d\n",_argc);
  if(_argc > 1){
    isolate->ThrowException(Exception::TypeError(
    String::NewFromUtf8(isolate, "[phSensor] - Wrong arguments...")));
  }
  Handle<Value>* argv = new Handle<Value>[_argc];
  for(uint8_t i = 0; i < _argc; i++){
    argv[i] = args[i];
  }
  Local<Function> cons = Local<Function>::New(isolate, constructor);
  Local<Object> instance = cons->NewInstance(_argc, argv);

  args.GetReturnValue().Set(instance);
}

void TempWrapper::getInfo(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  TempWrapper* temp_obj = ObjectWrap::Unwrap<TempWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->sensor->deviceInfo()));
}

void TempWrapper::reading(const FunctionCallbackInfo<Value>& args){
  Isolate* isolate = Isolate::GetCurrent();
  HandleScope scope(isolate);

  TempWrapper* temp_obj = ObjectWrap::Unwrap<TempWrapper>(args.Holder());

  args.GetReturnValue().Set(Number::New(isolate,temp_obj->sensor->reading()));
}
