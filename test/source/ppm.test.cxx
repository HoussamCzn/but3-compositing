#include <catch2/catch_test_macros.hpp>
#include <image/ppm.hxx>

TEST_CASE("Load an ascii PPM file", "[compositing]")
{
    namespace ppm = compositing::ppm;

    auto const img = ppm::read("../../../samples/spheres.ppm");

    if (img.has_value())
    {
        REQUIRE(img->width == 400);
        REQUIRE(img->height == 225);
        REQUIRE(img->pixels.size() == static_cast<std::size_t>(img->width * img->height));
    }
    else { FAIL("Failed to load image"); }
}

TEST_CASE("Load a binary PPM file", "[compositing]")
{
    namespace ppm = compositing::ppm;

    auto const img = ppm::read("../../../samples/lena.ppm");

    if (img.has_value())
    {
        REQUIRE(img->width == 512);
        REQUIRE(img->height == 512);
        REQUIRE(img->pixels.size() == static_cast<std::size_t>(img->width * img->height));
    }
    else { FAIL("Failed to load image"); }
}