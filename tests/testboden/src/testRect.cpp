
#include <bdn/test.h>

#include <bdn/Rect.h>

using namespace bdn;

TEST_CASE("Rect")
{
    SECTION("defaultConstruct")
    {
        Rect a;

        REQUIRE(a.x == 0);
        REQUIRE(a.y == 0);
        REQUIRE(a.width == 0);
        REQUIRE(a.height == 0);
    }

    SECTION("constructAll")
    {
        Rect a(1, 2, 3, 4);

        REQUIRE(a.x == 1);
        REQUIRE(a.y == 2);
        REQUIRE(a.width == 3);
        REQUIRE(a.height == 4);
    }

    SECTION("constructPointSize")
    {
        Rect a(Point(1, 2), Size(3, 4));

        REQUIRE(a.x == 1);
        REQUIRE(a.y == 2);
        REQUIRE(a.width == 3);
        REQUIRE(a.height == 4);
    }

    SECTION("getSizeAndPosition")
    {
        Rect a(1, 2, 3, 4);

        REQUIRE(a.getPosition() == Point(1, 2));
        REQUIRE(a.getSize() == Size(3, 4));
    }

    SECTION("equality")
    {
        Rect a(1, 2, 3, 4);

        checkEquality(Rect(), Rect(), true);
        checkEquality(a, Rect(), false);
        checkEquality(a, Rect(1, 2, 3, 4), true);
        checkEquality(a, Rect(10, 2, 3, 4), false);
        checkEquality(a, Rect(1, 20, 3, 4), false);
        checkEquality(a, Rect(1, 2, 30, 4), false);
        checkEquality(a, Rect(1, 2, 3, 40), false);
    }

    SECTION("+-Margin")
    {
        Rect a(10, 20, 30, 40);

        SECTION("+")
        {
            REQUIRE(a + Margin(1, 2, 3, 4) == Rect(6, 19, 36, 44));
            REQUIRE(a == Rect(10, 20, 30, 40));
        }

        SECTION("+=")
        {
            a += Margin(1, 2, 3, 4);
            REQUIRE(a == Rect(6, 19, 36, 44));
        }

        SECTION("-")
        {
            REQUIRE(a - Margin(1, 2, 3, 4) == Rect(14, 21, 24, 36));
            REQUIRE(a == Rect(10, 20, 30, 40));
        }

        SECTION("-=")
        {
            a -= Margin(1, 2, 3, 4);
            REQUIRE(a == Rect(14, 21, 24, 36));
        }

        SECTION("+neg")
        {
            REQUIRE(a + Margin(-1, -2, -3, -4) == Rect(14, 21, 24, 36));
            REQUIRE(a == Rect(10, 20, 30, 40));
        }

        SECTION("+=neg")
        {
            a += Margin(-1, -2, -3, -4);
            REQUIRE(a == Rect(14, 21, 24, 36));
        }

        SECTION("-neg")
        {
            REQUIRE(a - Margin(-1, -2, -3, -4) == Rect(6, 19, 36, 44));
            REQUIRE(a == Rect(10, 20, 30, 40));
        }

        SECTION("-=neg")
        {
            a -= Margin(-1, -2, -3, -4);
            REQUIRE(a == Rect(6, 19, 36, 44));
        }
    }

    SECTION("toString")
    {
        Rect r(1.125, -345.125, 2.775, 3.5);
        std::ostringstream str;
        str << r;

        REQUIRE(str.str() == "(1.125, -345.125 | 2.775 x 3.5)");
    }
}
