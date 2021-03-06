
#include <bdn/test.h>

#include <bdn/Button.h>
#include <bdn/Window.h>
#include <bdn/test/TestButtonCore.h>

#import "TestIosViewCoreMixin.hh"

using namespace bdn;

class TestIosButtonCore : public bdn::test::TestIosViewCoreMixin<bdn::test::TestButtonCore>
{
  protected:
    void initCore() override
    {
        bdn::test::TestIosViewCoreMixin<bdn::test::TestButtonCore>::initCore();

        _uIButton = (UIButton *)_uiView;
        REQUIRE(_uIButton != nullptr);
    }

    void verifyCoreLabel() override
    {
        String expectedLabel = _button->label;

        String label = bdn::ios::nsStringToString(_uIButton.currentTitle);

        REQUIRE(label == expectedLabel);
    }

  protected:
    UIButton *_uIButton;
};

TEST_CASE("ios.ButtonCore")
{
    std::shared_ptr<TestIosButtonCore> test = std::make_shared<TestIosButtonCore>();

    test->runTests();
}
