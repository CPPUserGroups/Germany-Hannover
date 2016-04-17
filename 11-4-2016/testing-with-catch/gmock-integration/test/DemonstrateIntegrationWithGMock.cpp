#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include <gmock/gmock.h>

#include <memory>
#include <string>

static std::unique_ptr<Catch::Session> catchSession;

class MinimalistPrinter : public ::testing::EmptyTestEventListener {
    // Called before a test starts.
    virtual void OnTestStart(const ::testing::TestInfo& test_info) {
    }

    // Called after a failed assertion or a SUCCEED() invocation.
    virtual void OnTestPartResult(
            const ::testing::TestPartResult& test_part_result) {
        std::ostringstream os;
        if (test_part_result.line_number()) {
            os << test_part_result.file_name() << ':'
               << test_part_result.line_number() << '\n';
        }
        os << test_part_result.summary();
        if (test_part_result.failed()) {
            FAIL(os.str());
        } else {
            if (catchSession->configData().showSuccessfulTests) {
                SUCCEED(os.str());
            } else {
                CHECK(os.str() == "");
            }
        }
    }

    // Called after a test ends.
    virtual void OnTestEnd(const ::testing::TestInfo& test_info) {
    }
};

int main(int argc, char* argv[]) {
    ::testing::TestEventListeners& listeners =
            ::testing::UnitTest::GetInstance()->listeners();
    // drop the default printer to prevent duplicate output
    delete listeners.Release(listeners.default_result_printer());
    // Adds a listener to the end.  Google Test takes the ownership.
    listeners.Append(new MinimalistPrinter);

    catchSession = std::make_unique<Catch::Session>();
    return catchSession->run(argc, argv);
}

class Foo {
  public:
    virtual ~Foo() {
    }
    virtual int GetSize() const = 0;
    virtual std::string Describe(const char* name) = 0;
    virtual std::string Describe(int type) = 0;
    //  virtual bool Process(Bar elem, int count) = 0;
};

class MockFoo : public Foo {
  public:
    MOCK_CONST_METHOD0(GetSize, int());
    MOCK_METHOD1(Describe, std::string(const char* name));
    MOCK_METHOD1(Describe, std::string(int type));
    //  MOCK_METHOD2(Process, bool(Bar elem, int count));
};

std::string MyProductionFunction(Foo* f) {
    for (int i = 0; i < 3; ++i) {
        f->Describe(5);
    }
    return "good";
}

using ::testing::Return;

TEST_CASE("GoogleMock", "[mock]") {
    MockFoo foo;                                    // #2
    //testing::StrictMock<MockFoo> foo;             // The type is a subclass of MockFoo.

    ON_CALL(foo, GetSize())                         // #3
            .WillByDefault(Return(1));
    // ... other default actions ...

    EXPECT_CALL(foo, Describe(5))                   // #4
            .Times(3)
            .WillRepeatedly(Return("Category 5"));
    // ... other expectations ...

    EXPECT_EQ("good", MyProductionFunction(&foo));  // #5
}

TEST_CASE("A usual Catch test") {
    REQUIRE(std::string("Hello World").length() == 11);
}
