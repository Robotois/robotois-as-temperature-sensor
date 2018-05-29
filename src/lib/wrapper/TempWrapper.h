#ifndef TEMPWRAPPER_H
#define TEMPWRAPPER_H

#include <node.h>
#include <node_object_wrap.h>
#include "../TemperatureSensor/TemperatureSensor.h"

class TempWrapper : public node::ObjectWrap {
public:
  static void Init();
  static void NewInstance(const v8::FunctionCallbackInfo<v8::Value>& args);

private:
  explicit TempWrapper(uint8_t _addr = 0x00);
  ~TempWrapper();

  static void New(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void getInfo(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void reading(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void tempCompensation(const v8::FunctionCallbackInfo<v8::Value>& args);
  static void calibrate(const v8::FunctionCallbackInfo<v8::Value>& args);

  static v8::Persistent<v8::Function> constructor;

  TemperatureSensor *sensor;
};

#endif
