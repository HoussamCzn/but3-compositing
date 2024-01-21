#pragma once

#include "image.hxx" // compositing::ppm::image

#include <filesystem> // std::filesystem::path
#include <optional>   // std::optional

namespace compositing::ppm
{
    /*
     * PPM images can be stored in ASCII or binary format.
     */
    enum class format
    {
        ascii,
        binary
    };

    /*
     * @brief Read a PPM image from a file.
     * @param path The path to the file.
     * @return The image if the file exists and is valid, std::nullopt otherwise.
     */
    [[nodiscard]] auto read(std::filesystem::path const& path) noexcept -> std::optional<image>;

    /*
     * @brief Write a PPM image to a file.
     * @param image The image to write.
     * @param path The path to the file.
     * @param fmt The format to use. (ascii or binary)
     * @return True if the image was written successfully, false otherwise.
     */
    [[nodiscard]] auto write(image const& image, std::filesystem::path const& path, format fmt = format::ascii,
                             bool can_overwrite = false) noexcept -> bool;
} // namespace compositing::ppm