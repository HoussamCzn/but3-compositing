#pragma once

#include "image/ppm.hxx" // ppm::image

namespace compositing
{
    class builder
    {
    public:

        auto images(std::vector<ppm::image> const& images) -> builder&;

        auto weights(std::vector<float> const& weights) -> builder&;

        auto output_size(std::uint32_t width, std::uint32_t height) -> builder&;

        auto output_path(std::filesystem::path const& path) -> builder&;

        [[nodiscard]] auto composite() -> ppm::image;

    private:

        std::vector<ppm::image> m_images;
        std::vector<float> m_weights;
        std::filesystem::path m_output_path;
        ppm::image m_final_image;
    };
} // namespace compositing