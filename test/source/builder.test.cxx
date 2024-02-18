#include <catch2/catch_test_macros.hpp>
#include <utils/builder.hxx>

using std::operator""s;
using std::operator""sv;

#ifdef _MSC_VER
static auto samples_path = "../../../../samples/"s;
#else  // ^^^ _MSC_VER / !_MSC_VER vvv
static auto samples_path = "../../../samples/"s;
#endif // _MSC_VER

TEST_CASE("Compose several images", "[compositing]")
{
    using namespace compositing;

    auto const img1 = ppm::read(samples_path + "spheres/left.ppm");
    auto const img2 = ppm::read(samples_path + "spheres/middle.ppm");
    auto const img3 = ppm::read(samples_path + "spheres/right.ppm");
    std::vector<float> weights = {0.5F, 1.F, 1.F};

    if (img1.has_value() && img2.has_value() && img3.has_value())
    {
        builder b;
        auto const result_img =
            b.images({*img1, *img2, *img3}).weights(weights).output_path(samples_path + "spheres/composed.ppm").composite();

        auto const result = ppm::write(result_img, samples_path + "spheres/composed.ppm", ppm::format::ascii, true);
        REQUIRE(result);
    }
    else { FAIL("Could not read images"); }
}
