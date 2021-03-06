#pragma once

#include <bdn/android/JView.h>
#include <bdn/java/JObject.h>

namespace bdn::android
{
    constexpr const char kNativeViewCoreClickListenerClassName[] = "io/boden/android/NativeViewCoreClickListener";

    using JNativeViewCoreClickListener = OnClickListenerBase<kNativeViewCoreClickListenerClassName>;
}