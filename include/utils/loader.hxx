#pragma once

#include "image/ppm.hxx" // ppm::image

#include <functional> // std::function
#include <optional>   // std::optional

namespace compositing
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
         * @return A vector of images.
         * @note The images are loaded in the order they are found in the directory.
         */
        [[nodiscard]] auto load() -> std::vector<ppm::image>;

    private:

        std::function<bool(std::filesystem::path const&)> m_skip_predicate; //< The predicate to skip images.
        std::filesystem::path m_input_path;                                 //< The path from which images should be loaded.
        std::size_t m_max_count = std::numeric_limits<std::size_t>::max();  //< The maximum number of images to be loaded.
    };
} // namespace compositing