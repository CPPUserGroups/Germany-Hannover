#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

SCENARIO("Exploratory testing std::string", "[tag]") {
    GIVEN("A default-constructed string") {
        std::string s;
        THEN("The size is zero") {
            REQUIRE(s.size() == 0);
        }
        AND_THEN("The string is empty") {
            REQUIRE(s.empty());
        }
    }

    GIVEN("Two strings a and b") {
        std::string a("a");
        std::string b("b");
        std::string c("c");
        WHEN("The strings are added") {
            THEN("the result is ab") {
                REQUIRE("ab" == a + b);
            }

            AND_THEN("the string starts with a") {
                CHECK_THAT(a + c, Catch::Matchers::StartsWith("a"));
            }
        }
    }
}
