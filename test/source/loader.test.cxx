#include <catch2/catch_test_macros.hpp>
#include <utils/loader.hxx>

using std::operator""s;
using std::operator""sv;

#ifdef _MSC_VER
static auto samples_path = "../../../../samples/"s;
#else  // ^^^ _MSC_VER / !_MSC_VER vvv
static auto samples_path = "../../../samples/"s;
#endif // _MSC_VER

TEST_CASE("Load all samples", "[compositing]")
{
    using namespace compositing;

    loader l;
    auto const images = l.input_path(samples_path + "spheres/").load();

    REQUIRE(images.size() == 4);
}

TEST_CASE("Load all samples with a filter", "[compositing]")
{
    using namespace compositing;

    loader l;
    auto const images = l.input_path(samples_path + "spheres/")
                            .skip_if([](auto const& p) { return p.filename().string().find("composed") != std::string::npos; })
                            .load();

    REQUIRE(images.size() == 3);
}

TEST_CASE("Load all samples until reaching the file limit", "[compositing]")
{
    using namespace compositing;

    loader l;
    auto const images = l.input_path(samples_path + "spheres/").max_file_count(2).load();

    REQUIRE(images.size() == 2);
}