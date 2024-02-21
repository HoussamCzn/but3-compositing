#include "utils/builder.hxx"

#include "image/image.hxx" // ppm::image, ppm::pixel

#include <algorithm> // std::ranges::max_element, std::ranges::for_each
#include <execution> // std::execution::par_unseq
#include <numeric>   // std::accumulate

namespace compositing::utils
{
    auto builder::images(std::vector<ppm::image> const& images) -> builder&
    {
        m_images = images;

        if (!m_images.empty()) [[likely]]
        {
            auto const max_width = std::ranges::max_element(m_images, {}, [](ppm::image const& image) { return image.width; });
            auto const max_height = std::ranges::max_element(m_images, {}, [](ppm::image const& image) { return image.height; });

            return output_size(max_width->width, max_height->height);
        }

        return *this;
    }

    auto builder::weights(std::vector<float> const& weights) -> builder&
    {
        m_weights = weights;

        return *this;
    }

    auto builder::output_size(std::uint32_t width, std::uint32_t height) -> builder&
    {
        m_final_image.width = width;
        m_final_image.height = height;
        m_final_image.pixels.resize(static_cast<std::size_t>(width * height));

        return *this;
    }

    auto builder::output_path(std::filesystem::path const& path) -> builder&
    {
        m_output_path = path;

        return *this;
    }

    auto builder::composite() -> ppm::image
    {
        auto const total_weight = std::accumulate(std::begin(m_weights), std::end(m_weights), 0.F);
        std::ranges::for_each(m_images, [this, total_weight](ppm::image const& image) {
            auto const weight = m_weights[static_cast<std::size_t>(std::ranges::distance(m_images.data(), &image))];
            std::transform(std::execution::par_unseq, std::begin(m_final_image.pixels), std::end(m_final_image.pixels),
                           std::begin(image.pixels), std::begin(m_final_image.pixels),
                           [weight, total_weight](ppm::pixel const final_pixel, ppm::pixel const pixel) -> ppm::pixel {
                               return final_pixel + pixel * (weight / total_weight);
                           });
        });

        return m_final_image;
    }
} // namespace compositing::utils