#include <catch2/catch_test_macros.hpp>
#include <image/ppm.hxx>

using std::operator""s;
using std::operator""sv;

#ifdef _MSC_VER
static auto samples_path = "../../../../samples/"s;
#else  // ^^^ _MSC_VER / !_MSC_VER vvv
static auto samples_path = "../../../samples/"s;
#endif // _MSC_VER

TEST_CASE("Load an ascii PPM file", "[compositing]")
{
    namespace ppm = compositing::ppm;

    auto const img = ppm::read(samples_path + "spheres.ppm");

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

    auto const img = ppm::read(samples_path + "lena.ppm");

    if (img.has_value())
    {
        REQUIRE(img->width == 512);
        REQUIRE(img->height == 512);
        REQUIRE(img->pixels.size() == static_cast<std::size_t>(img->width * img->height));
    }
    else { FAIL("Failed to load image"); }
}

TEST_CASE("Save an ascii PPM file", "[compositing]")
{
    namespace ppm = compositing::ppm;

    auto const img = ppm::read(samples_path + "lena.ppm");

    if (img.has_value()) { REQUIRE(ppm::write(*img, samples_path + "lena_v2.ppm", ppm::format::ascii, true)); }
    else { FAIL("Failed to load image"); }
}

TEST_CASE("Save a binary PPM file", "[compositing]")
{
    namespace ppm = compositing::ppm;

    auto const img = ppm::read(samples_path + "spheres.ppm");

    if (img.has_value()) { REQUIRE(ppm::write(*img, samples_path + "spheres_v2.ppm", ppm::format::binary, true)); }
    else { FAIL("Failed to load image"); }
}
