#pragma once

#include <bdn/Checkbox.h>
#include <bdn/CheckboxCore.h>
#include <bdn/ClickEvent.h>

#import <bdn/ios/IosCheckbox.hh>
#import <bdn/ios/ViewCore.hh>

@interface BdnIosCheckboxComposite : UIControl <UIViewWithFrameNotification>
@property(nonatomic, assign) bdn::ios::ViewCore *viewCore;
@property(strong) BdnIosCheckbox *checkbox;
@property(strong) UILabel *uiLabel;
@end

@class BdnIosCheckboxClickManager;

namespace bdn::ios
{
    class CheckboxCore : public ViewCore, virtual public bdn::CheckboxCore
    {
      private:
        static BdnIosCheckboxComposite *_createCheckboxComposite();

      public:
        CheckboxCore(std::shared_ptr<Checkbox> outerCheckbox);
        virtual ~CheckboxCore();

        void setState(const TriState &state) override;

        void setLabel(const String &label) override;

        void _clicked();

      private:
        BdnIosCheckboxComposite *_composite;
        BdnIosCheckboxClickManager *_clickManager;
    };
}
