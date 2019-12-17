
#include <nan.h>
#include "obj.h"

NAN_MODULE_INIT(InitModule) {
    obj::Init(target);
}

NODE_MODULE(addon, InitModule);
