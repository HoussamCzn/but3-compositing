#include "utils/builder.hxx"

#include <algorithm>
#include <execution>
#include <numeric>

namespace compositing
{
    auto builder::images(std::vector<ppm::image> const& images) -> builder&
    {
        m_images = images;

        if (!m_images.empty())
        {
            auto const [min_width, max_width] =
                std::ranges::minmax_element(m_images, {}, [](auto const& image) { return image.width; });
            auto const [min_height, max_height] =
                std::ranges::minmax_element(m_images, {}, [](auto const& image) { return image.height; });

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
        auto const total_weight = std::accumulate(m_weights.begin(), m_weights.end(), 0.0F);
        std::ranges::for_each(m_images, [this, total_weight](auto const& image) {
            auto const weight = m_weights[static_cast<std::size_t>(std::ranges::distance(m_images.data(), &image))];
            std::transform(std::execution::par_unseq, m_final_image.pixels.begin(), m_final_image.pixels.end(),
                           image.pixels.begin(), m_final_image.pixels.begin(),
                           [weight, total_weight](auto const& final_pixel, auto const& pixel) -> ppm::pixel {
                               return final_pixel + pixel * (weight / total_weight);
                           });
        });

        return m_final_image;
    }
} // namespace compositing