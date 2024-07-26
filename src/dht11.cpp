#include <node.h>
#include "DHTxx.h"


namespace demo {

using v8::Exception;
using v8::Context;
using v8::FunctionCallbackInfo;
using v8::Isolate;
using v8::Local;
using v8::Object;
using v8::String;
using v8::Value;
using v8::Number;

void CreateObject(const FunctionCallbackInfo<Value>& args) {
  float humidity;
  float temperature;

  Isolate* isolate = args.GetIsolate();
  Local<Context> context = isolate->GetCurrentContext();

  Local<Object> obj = Object::New(isolate);

    obj->Set(context,
           String::NewFromUtf8(isolate,"error").ToLocalChecked(),
           String::NewFromUtf8(isolate, "").ToLocalChecked()
                               ).FromJust();

  if (args.Length() < 1) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Wrong number of arguments").ToLocalChecked()));
    return;
  }

  if (!args[0]->IsNumber()) {
    isolate->ThrowException(Exception::TypeError(
        String::NewFromUtf8(isolate,
                            "Wrong argument type for pin must be Number").ToLocalChecked()));
    return;
  }

  int pin= args[0].As<Number>()->Value();
  DHTxx dht11(pin, DHT11);

    if (dht11.init() == DHT_SUCCESS) {

      int result = dht11.read(&humidity, &temperature);
            switch (result) {
            case DHT_ERROR_TIMEOUT:

                obj->Set(context,
                           String::NewFromUtf8(isolate,"error").ToLocalChecked(),
                           String::NewFromUtf8(isolate, "DHT_ERROR_TIMEOUT").ToLocalChecked()
                                               ).FromJust();

              break;
            case DHT_ERROR_CHECKSUM:

              obj->Set(context,
                 String::NewFromUtf8(isolate,"error").ToLocalChecked(),
                 String::NewFromUtf8(isolate, "DHT_ERROR_CHECKSUM").ToLocalChecked()
                                     ).FromJust();
              break;
            case DHT_ERROR_ARGUMENT:
              obj->Set(context,
                 String::NewFromUtf8(isolate,"error").ToLocalChecked(),
                 String::NewFromUtf8(isolate, "DHT_ERROR_ARGUMENT").ToLocalChecked()
                                     ).FromJust();
              break;
            case DHT_ERROR_GPIO:
              obj->Set(context,
                 String::NewFromUtf8(isolate,"error").ToLocalChecked(),
                 String::NewFromUtf8(isolate, "DHT_ERROR_GPIO").ToLocalChecked()
                                     ).FromJust();
              break;
            case DHT_SUCCESS:

            obj->Set(context,
                       String::NewFromUtf8(isolate,
                                           "temperature").ToLocalChecked(),
                                           Number::New(isolate, temperature)
                                           ).FromJust();
            obj->Set(context,
                       String::NewFromUtf8(isolate,
                                           "humidity").ToLocalChecked(),
                                           Number::New(isolate, humidity)
                                           ).FromJust();
              break;
            default:
              break;
            }
    }
  args.GetReturnValue().Set(obj);
}

void Init(Local<Object> exports, Local<Object> module) {
  NODE_SET_METHOD(module, "exports", CreateObject);
}

NODE_MODULE(NODE_GYP_MODULE_NAME, Init)

}