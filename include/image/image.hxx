#pragma once

#include <cstdint> // std::uint8_t
#include <ostream> // std::ostream
#include <vector>  // std::vector

namespace compositing::ppm
{
    /*
     * A pixel is a single point in an image.
     * It is the smallest element you can work with and is
     * composed of three components. (Red, Green and Blue)
     * Each color component is a number from 0 to 255.
     */
    struct pixel
    {
        std::uint8_t red{0};   //< The red component of the pixel.
        std::uint8_t green{0}; //< The green component of the pixel.
        std::uint8_t blue{0};  //< The blue component of the pixel.

        /*
         * @brief Compare two pixels.
         * @param lhs The left-hand side pixel.
         * @param rhs The right-hand side pixel.
         * @return True if the pixels are equal, false otherwise.
         */
        [[nodiscard]] friend auto operator==(pixel const& lhs, pixel const& rhs) noexcept -> bool
        {
            return lhs.red == rhs.red && lhs.green == rhs.green && lhs.blue == rhs.blue;
        }

        /*
         * @brief Compare two pixels.
         * @param lhs The left-hand side pixel.
         * @param rhs The right-hand side pixel.
         * @return True if the pixels are not equal, false otherwise.
         */
        [[nodiscard]] friend auto operator!=(pixel const& lhs, pixel const& rhs) noexcept -> bool { return !(lhs == rhs); }

        /*
         * @brief Write a pixel to an output stream.
         * @param os The output stream.
         * @param pixel The pixel to write.
         * @return The output stream.
         */
        [[nodiscard]] friend auto operator<<(std::ostream& os, pixel const& pixel) noexcept -> std::ostream&
        {
            return os << static_cast<int>(pixel.red) << " " << static_cast<int>(pixel.green) << " "
                      << static_cast<int>(pixel.blue);
        }
    };

    /*
     * An image is a two-dimensional representation of pixels.
     * It is composed of a width, a height and a list of pixels.
     * Each pixel is stored in a row-major order.
     */
    struct image
    {
        std::vector<pixel> pixels; //< The list of pixels.
        std::uint32_t width{0};    //< The width of the image.
        std::uint32_t height{0};   //< The height of the image.
    };
} // namespace compositing::ppm
