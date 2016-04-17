include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Catch/single_include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/googletest/googlemock/include)

add_definitions(-DGTEST_DONT_DEFINE_FAIL)
add_definitions(-DGTEST_DONT_DEFINE_SUCCEED)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/googletest ${CMAKE_CURRENT_BINARY_DIR}/googletest)

add_executable(demonstrate-integration-with-gmock
    DemonstrateIntegrationWithGMock.cpp
)

set_target_properties(demonstrate-integration-with-gmock PROPERTIES COMPILE_OPTIONS "-std=c++14")

target_link_libraries(
    demonstrate-integration-with-gmock
    gmock
    gtest
)
