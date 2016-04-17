#define CATCH_CONFIG_RUNNER
#include <catch.hpp>

#include <string>
#include <trompeloeil.hpp>

int main(int argc, char* argv[]) {
    trompeloeil::set_reporter([](::trompeloeil::severity s, char const* file,
                                 unsigned long line, const std::string& msg) {
        std::ostringstream os;
        if (line)
            os << file << ':' << line << '\n';
        os << msg;
        if (s == ::trompeloeil::severity::fatal) {
            FAIL(os.str());
        }
        CHECK(os.str() == "");
    });

    return Catch::Session().run(argc, argv);
}

class Interface {
  public:
    virtual bool foo(int, std::string& s) = 0;
    virtual bool bar(int) = 0;
    virtual bool bar(std::string) = 0;
};

void interface_func(Interface*);  // function to test

void interface_func(Interface* i) {
    std::string s;
    i->bar(3);
    i->bar("word");
    i->foo(3, s);
}

class Mock : public Interface {
  public:
    MAKE_MOCK2(foo, bool(int, std::string&));
    MAKE_MOCK1(bar, bool(int));
    MAKE_MOCK1(bar, bool(std::string));
};

TEST_CASE("exercise interface func", "[mock]") {
    using trompeloeil::_;   // wild card for matching any value
    using trompeloeil::gt;  // greater-than match

    Mock m;

    trompeloeil::sequence seq1, seq2;  // control order of matching calls

    int local_var = 0;

    REQUIRE_CALL(m, bar(ANY(int)))  // expect call to m.bar(int)
            .LR_SIDE_EFFECT(
                    local_var = _1)  // set captured variable to value of param
            .RETURN(_1 > 0)          // return value depending on param value
            .IN_SEQUENCE(seq1)       // must be first match for seq1
            .TIMES(AT_LEAST(1));     // can be called several times

    FORBID_CALL(m, bar(0));  // but m.bar(0) is not allowed

    REQUIRE_CALL(m, bar("word"))  // expect one call to m.bar(std::string)
            .RETURN(true)
            .IN_SEQUENCE(seq2);  // must be first match for seq2

    REQUIRE_CALL(m, foo(gt(2), _))    // expect call to foo(int,std::string&)
            .WITH(_2 == "")           // with int > 2 and empty string
            .IN_SEQUENCE(seq1, seq2)  // last for both seq1 and seq2
            .SIDE_EFFECT(_2 = "cat")  // and set param string to "cat"
            .RETURN(true);

    interface_func(&m);

    // all the above expectations must be fulfilled here
}

TEST_CASE("A usual Catch test") {
    REQUIRE(std::string("Hello World").length() == 11);
}
