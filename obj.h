#include <nan.h>
#include <iostream>
#include <cctype>

class obj : public Nan::ObjectWrap {
private:
    std::string ucletters;
    std::string lcletters;

public:
    static Nan::Persistent<v8::FunctionTemplate> constructor;

    static NAN_MODULE_INIT(Init);
    static NAN_METHOD(New);
    static NAN_METHOD(hasUpper);
    static NAN_METHOD(findUpper);
    static NAN_METHOD(findLower);
    static NAN_GETTER(GettersforAccessor);
    static NAN_SETTER(SettersforAccessor);
};
