#pragma once

#include <bdn/java/JObject.h>

namespace bdn::android
{
    constexpr const char kIBinderClassName[] = "android/os/IBinder";

    class JIBinder : public java::JTObject<kIBinderClassName>
    {
      public:
        using java::JTObject<kIBinderClassName>::JTObject;
    };
}
