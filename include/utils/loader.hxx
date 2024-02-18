#pragma once

#include "image/image.hxx" // ppm::image

#include <filesystem>    // std::filesystem::path
#include <functional>    // std::function
#include <unordered_map> // std::unordered_map

namespace compositing::utils
{
    /*
     * @brief A loader for images.
     * The loader can be configured to load images from a specific path, to skip images based on a predicate and to limit the
     * number of images to be loaded.
     */
    class loader
    {
    public:

        /*
         * @brief Sets the path from which images should be loaded.
         * @param path The path from which images should be loaded.
         * @return A reference to the loader.
         * @note The path must be a directory.
         */
        auto input_path(std::filesystem::path const& path) -> loader&;

        /*
         * @brief Sets the maximum number of images to be loaded.
         * @param count The maximum number of images to be loaded.
         * @return A reference to the loader.
         */
        auto max_file_count(std::size_t count) -> loader&;

        /*
         * @brief Sets a predicate to skip images.
         * @param predicate The predicate to skip images.
         * @return A reference to the loader.
         * @note The predicate is called for each image and should return true if the image should be skipped and false otherwise.
         */
        auto skip_if(std::function<bool(std::filesystem::path const&)> const& predicate) -> loader&;

        /*
         * @brief Loads images from the configured path.
         * @return A map of images loaded from the configured path.
         * @note The key of the map is the path of the image and the value is the image itself.
         */
        [[nodiscard]] auto load() -> std::unordered_map<std::filesystem::path, ppm::image>;

    private:

        std::function<bool(std::filesystem::path const&)> m_skip_predicate; //< The predicate to skip images.
        std::filesystem::path m_input_path;                                 //< The path from which images should be loaded.
        std::size_t m_max_count = std::numeric_limits<std::size_t>::max();  //< The maximum number of images to be loaded.
    };
} // namespace compositing::utils