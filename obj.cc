#include "obj.h"

Nan::Persistent<v8::FunctionTemplate> obj::constructor;

NAN_MODULE_INIT(obj::Init) {
    v8::Local<v8::FunctionTemplate> construct = Nan::New<v8::FunctionTemplate>(obj::New);
    constructor.Reset(construct);
    construct->InstanceTemplate()->SetInternalFieldCount(1);
    construct->SetClassName(Nan::New("obj").ToLocalChecked());

  Nan::SetAccessor(construct->InstanceTemplate(), Nan::New("ucletters").ToLocalChecked(), obj::GettersforAccessor, obj::SettersforAccessor);
  Nan::SetAccessor(construct->InstanceTemplate(), Nan::New("lcletters").ToLocalChecked(), obj::GettersforAccessor, obj::SettersforAccessor);

    Nan::SetPrototypeMethod(construct, "hasUpper", hasUpper);
    Nan::SetPrototypeMethod(construct, "findUpper", findUpper);
    Nan::SetPrototypeMethod(construct, "findLower", findLower);

    target->Set(Nan::New("obj").ToLocalChecked(), construct->GetFunction());
}

NAN_METHOD(obj::New) {


    obj* item = new obj();
    item->Wrap(info.Holder());
    if(info[0]->IsString())
        item->ucletters = std::string(*Nan::Utf8String(info[0]));
    if(info[1]->IsString())
        item->lcletters = std::string(*Nan::Utf8String(info[1]));

    info.GetReturnValue().Set(info.Holder());
}

NAN_METHOD(obj::hasUpper) {
    obj* init = Nan::ObjectWrap::Unwrap<obj>(info.This());

    if(!info[0]->IsString())
        return Nan::ThrowError(Nan::New("type error").ToLocalChecked());
    std::string str = std::string(*Nan::Utf8String(info[0]));
    std::string store1 = "";
    std::string store2 = "";
    if(!info[1]->IsString()) {
        bool flag = false;
        for(unsigned int i = 0, len = str.length(); i < len; ++i) {
            if(isupper(str[i])) {
                flag = true;
                store1 += str[i];
            } else {
                store2 += str[i];
            }
        }
        if(!init->ucletters.length()) {
        init->ucletters = store1;
        }
        if(!init->lcletters.length()) {
            init->lcletters = store2;
        }
        if(flag) {
            info.GetReturnValue().Set(1);
            return;
        }
    } else {
       std::string substring = std::string(*Nan::Utf8String(info[1]));
        char val = toupper(substring[0]);
        for(unsigned int i = 0, len = str.length(); i < len; ++i) {
            if(isupper(str[i])) {
                store1 += str[i];
            } else {
                store2 += str[i];
            }
        }
        if(!init->ucletters.length()) {
            init->ucletters = store1;
        }
        if(!init->lcletters.length()) {
            init->lcletters = store2;
        }
        for(int i = 0, len = str.length(); i < len; ++i) {
            if(str[i] == val) {
                info.GetReturnValue().Set(1);
                return;
            }
        }
    }
    info.GetReturnValue().Set(0);
}

NAN_METHOD(obj::findUpper) {
    obj* init = Nan::ObjectWrap::Unwrap<obj>(info.This());

    if(!info[0]->IsString() || !info[1]->IsString())
        return Nan::ThrowError(Nan::New("Type Error").ToLocalChecked());

    std::string str = std::string(*Nan::Utf8String(info[0]));
    std::string upper = std::string(*Nan::Utf8String(info[1]));

    std::string store1 = "";
    std::string store2 = "";
    if(upper != "") {
        for(unsigned int i = 0,len=str.length(); i < len; ++i) {
            for(unsigned int j = 0,ulen= upper.length(); j<ulen; ++j) {
                if(str[i] == upper[j])
                {
                    store1 += upper[j];
                } else
                {
                    store2 += upper[j];
                }
            }
        }
        if(!init->ucletters.length())
        {
            init->ucletters = store1;
        }
        if(!init->lcletters.length())
        {
            init->lcletters = store2;
        }
    }
    info.GetReturnValue().Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), store1.c_str()));
}

NAN_METHOD(obj::findLower) {
    obj* init = Nan::ObjectWrap::Unwrap<obj>(info.This());
    if(!info[0]->IsFunction()) return Nan::ThrowError(Nan::New("Type Error").ToLocalChecked());

    //https://github.com/nodejs/nan/blob/master/doc/callback.md
    //https://nodejs.org/api/addons.html#addons_callbacks
    v8::Local<v8::Function> cfunc = v8::Local<v8::Function>::Cast(info[0]);
    Nan::Callback cb(cfunc);

    if(!info[1]->IsString() || !info[2]->IsString())
        return Nan::ThrowError(Nan::New("Type Error").ToLocalChecked());

    std::string str = std::string(*Nan::Utf8String(info[1]));
    std::string lower = std::string(*Nan::Utf8String(info[2]));

    std::string store1 = "";
    std::string store2 = "";
    const int argc = 2;
    v8::Local<v8::Value> args[argc];
    args[0] = info[1];

    if(lower != "") {
        for(unsigned int i = 0, len = lower.length(); i < len; ++i) {
            args[1] = Nan::New(lower[i]);
            v8::Local<v8::Value> result = cb.Call(argc, args);
            bool flag = result->BooleanValue();
            if(flag) {
              store1 += lower[i];
            }
        }
        if(!init->ucletters.length()) {
            init->ucletters = store2;
        }
        if(!init->lcletters.length()) {
            init->lcletters = store1;
        }
    }

    info.GetReturnValue().Set(v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), store1.c_str()));
}

NAN_GETTER(obj::GettersforAccessor) {
    obj* init = Nan::ObjectWrap::Unwrap<obj>(info.This());

    std::string argument = std::string(*Nan::Utf8String(property));
    if(argument == "ucletters") {
        v8::Local<v8::String> result= v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), init->ucletters.c_str());
        info.GetReturnValue().Set(result);
    } else if(argument == "lcletters") {
        v8::Local<v8::String> result = v8::String::NewFromUtf8(v8::Isolate::GetCurrent(), init->lcletters.c_str());
        info.GetReturnValue().Set(result);
    }
}

NAN_SETTER(obj::SettersforAccessor) {
    obj* init = Nan::ObjectWrap::Unwrap<obj>(info.This());
    if(!value->IsString()) return Nan::ThrowError(Nan::New("type error").ToLocalChecked());

    std::string argument = std::string(*Nan::Utf8String(property));
    if(argument == "ucletters") {
        init->ucletters = std::string(*Nan::Utf8String(value));
    }
    else if(argument == "lcletters") {
        init->lcletters = std::string(*Nan::Utf8String(value));
    }
}
