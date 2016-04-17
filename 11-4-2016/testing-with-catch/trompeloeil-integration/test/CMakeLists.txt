include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Catch/single_include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/trompeloeil)

add_executable(demonstrate-integration-with-trompeloeil
    DemonstrateIntegrationWithTrompeloeil.cpp
)

set_target_properties(demonstrate-integration-with-trompeloeil PROPERTIES COMPILE_OPTIONS -std=c++14)
