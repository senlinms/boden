
#include <bdn/test.h>

#include "TestAndroidViewCoreMixin.h"
#include <bdn/Window.h>
#include <bdn/android/UIProvider.h>
#include <bdn/android/WindowCore.h>
#include <bdn/test/TestWindowCore.h>

using namespace bdn;

class TestAndroidWindowCore : public bdn::test::TestAndroidViewCoreMixin<bdn::test::TestWindowCore>
{
  protected:
    void initCore() override { bdn::test::TestAndroidViewCoreMixin<bdn::test::TestWindowCore>::initCore(); }

    void verifyCoreTitle() override
    {
        // the title is ignored on android. So nothing to test here
    }

    bool canManuallyChangePosition() const override { return false; }

    bool canManuallyChangeSize() const override { return false; }

    /** Removes all references to the core object.*/
    void clearAllReferencesToCore() override
    {
        bdn::test::TestAndroidViewCoreMixin<bdn::test::TestWindowCore>::clearAllReferencesToCore();

        _androidViewCore = nullptr;
        //        _jView = bdn::android::JView();
    }

    struct DestructVerificationInfo : public Base
    {
        DestructVerificationInfo(bdn::android::JView jView) : jView(jView) {}

        bdn::android::JView jView;
    };

    std::shared_ptr<Base> createInfoToVerifyCoreUIElementDestruction() override
    {
        // sanity check
        REQUIRE(!_jView.isNull_());
        REQUIRE(!_jView.getParent().isNull_());

        return std::make_shared<DestructVerificationInfo>(_jView);
    }

    void verifyCoreUIElementDestruction(std::shared_ptr<Base> verificationInfo) override
    {
        bdn::android::JView jv = std::dynamic_pointer_cast<DestructVerificationInfo>(verificationInfo)->jView;

        // the view object should have been removed from its parent
        REQUIRE(jv.getParent().isNull_());
    }
};

TEST_CASE("android.WindowCore")
{
    std::shared_ptr<TestAndroidWindowCore> test = std::make_shared<TestAndroidWindowCore>();

    test->runTests();
}
