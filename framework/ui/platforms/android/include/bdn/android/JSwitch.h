#pragma once

#include <bdn/android/JCompoundButton.h>
#include <bdn/java/JString.h>

namespace bdn::android
{

    constexpr const char kSwitchClassName[] = "android/widget/Switch";
    class JSwitch : public JBaseCompoundButton<kSwitchClassName>
    {
      public:
        using JBaseCompoundButton<kSwitchClassName>::JBaseCompoundButton;

      public:
        java::Method<void(bool)> setChecked{this, "setChecked"};
    };
}
