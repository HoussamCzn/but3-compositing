#include "lib.hxx"

#include <catch2/catch_test_macros.hpp>

TEST_CASE("Name is compositing", "[library]")
{
    auto const lib = library{};
    REQUIRE(lib.name == "compositing");
}