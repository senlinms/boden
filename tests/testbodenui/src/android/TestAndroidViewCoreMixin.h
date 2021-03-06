#ifndef BDN_TEST_TestAndroidViewCore_H_
#define BDN_TEST_TestAndroidViewCore_H_

#include <bdn/View.h>
#include <bdn/android/UIProvider.h>
#include <bdn/android/ViewCore.h>

namespace bdn
{
    namespace test
    {

        /** A mixin class that adds implementations of android view specific
         functionality on top of the base class specified in the template
         parameter BaseClass.*/
        template <class BaseClass> class TestAndroidViewCoreMixin : public BaseClass
        {
          public:
            TestAndroidViewCoreMixin() : _jView(nullptr) {}

          protected:
            void initCore() override
            {
                BaseClass::initCore();

                _androidViewCore = std::dynamic_pointer_cast<bdn::android::ViewCore>(BaseClass::_view->viewCore());
                REQUIRE(_androidViewCore != nullptr);

                _jView = _androidViewCore->getJView();
                REQUIRE(!_jView.isNull_());
            }

            std::shared_ptr<UIProvider> uiProvider() override { return bdn::android::UIProvider::get(); }

            void verifyCoreVisibility() override
            {
                bool expectedVisible = BaseClass::_view->visible;

                if (expectedVisible)
                    REQUIRE(_jView.getVisibility() == bdn::android::JView::Visibility::visible);
                else
                    REQUIRE(_jView.getVisibility() == bdn::android::JView::Visibility::invisible);
            }

            Point getViewPosition()
            {
                double scaleFactor = _androidViewCore->getUIScaleFactor();

                return Point(_jView.getLeft() / scaleFactor, _jView.getTop() / scaleFactor);
            }

            Size getViewSize()
            {
                double scaleFactor = _androidViewCore->getUIScaleFactor();

                return Size(_jView.getWidth() / scaleFactor, _jView.getHeight() / scaleFactor);
            }

            void verifyInitialDummyCoreSize() override
            {
                Size size = getViewSize();

                REQUIRE(size == Size());
            }

            void verifyCorePosition() override
            {
                Point position = getViewPosition();
                Point expectedPosition = BaseClass::_view->position;

                REQUIRE_ALMOST_EQUAL(position.x, expectedPosition.x, 1);
                REQUIRE_ALMOST_EQUAL(position.y, expectedPosition.y, 1);
            }

            void verifyCoreSize() override
            {
                Size size = getViewSize();
                Size expectedSize = BaseClass::_view->size;

                REQUIRE_ALMOST_EQUAL(size.width, expectedSize.width, 1);
                REQUIRE_ALMOST_EQUAL(size.height, expectedSize.height, 1);
            }

            void verifyCorePadding() override
            {
                int top = _jView.getPaddingTop();
                int right = _jView.getPaddingRight();
                int bottom = _jView.getPaddingBottom();
                int left = _jView.getPaddingLeft();

                std::optional<UIMargin> pad = BaseClass::_view->padding;

                if (!pad) {
                    // the default padding is used. This is simply the padding
                    // that is pre-configured in the android UI control. We have
                    // no way to test if what we get here is really correct. So
                    // we cannot test this case.
                    return;
                }

                Margin expectedDipPadding = BaseClass::_view->uiMarginToDipMargin(*pad);

                double scaleFactor = _androidViewCore->getUIScaleFactor();

                REQUIRE_ALMOST_EQUAL(top / scaleFactor, expectedDipPadding.top, 1);
                REQUIRE_ALMOST_EQUAL(right / scaleFactor, expectedDipPadding.right, 1);
                REQUIRE_ALMOST_EQUAL(bottom / scaleFactor, expectedDipPadding.bottom, 1);
                REQUIRE_ALMOST_EQUAL(left / scaleFactor, expectedDipPadding.left, 1);
            }

            std::shared_ptr<bdn::android::ViewCore> _androidViewCore;
            bdn::android::JView _jView;
        };
    }
}

#endif
