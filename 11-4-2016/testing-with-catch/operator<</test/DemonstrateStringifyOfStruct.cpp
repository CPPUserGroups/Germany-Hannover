#define CATCH_CONFIG_MAIN
#include <catch.hpp>

#include <string>

struct OperatorDemo {
    std::string name;
    double weight;
    int age;
    int size;

    bool operator==(const OperatorDemo& other) {
        return name == other.name &&
               weight == other.weight &&
               age == other.age &&
               size == other.size;
    }
};

std::ostream& operator<<(std::ostream& os, const OperatorDemo& o) {
    return os << "{ "
              << o.name
              << ", age: " << o.age
              << ", weight: " << o.weight
              << ", size: " << o.size
              << " }";
}

TEST_CASE("Our C++ heroes are unique") {
    // just guessing ;)
    OperatorDemo scott = {"Scott Meyers", 68.9, 49, 189};
    OperatorDemo bjarne = {"Bjarne Stroustrup", 84.1, 64, 170};

    REQUIRE(scott == bjarne);
}
