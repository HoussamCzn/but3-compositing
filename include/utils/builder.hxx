#pragma once

#include "image/ppm.hxx" // ppm::image

namespace compositing::utils
{
    /*
     * @brief A builder class for compositing images
     * It allows to set the images to composite, their weights, the output size and the output path
     */
    class builder
    {
    public:

        /*
         * @brief Set the images to composite
         * @param images The images to composite
         * @return A reference to the current builder
         * @note The size used for the output image will be the largest
         * width and height of the images.
         */
        auto images(std::vector<ppm::image> const& images) -> builder&;

        /*
         * @brief Set the weights for the images
         * @param weights The weights for the images
         * @return A reference to the current builder
         */
        auto weights(std::vector<float> const& weights) -> builder&;

        /*
         * @brief Set the size of the output image
         * @param width The width of the output image
         * @param height The height of the output image
         * @return A reference to the current builder
         */
        auto output_size(std::uint32_t width, std::uint32_t height) -> builder&;

        /*
         * @brief Set the path of the output image
         * @param path The path of the output image
         * @return A reference to the current builder
         * @note The path does not need to include the file extension
         * as it will be added automatically
         */
        auto output_path(std::filesystem::path const& path) -> builder&;

        /*
         * @brief Composite the images
         * This function needs to be called after setting the images,
         * the weights, the output size and the output path
         * @return The composite image
         */
        [[nodiscard]] auto composite() -> ppm::image;

    private:

        std::vector<ppm::image> m_images;    //< The images to composite
        std::vector<float> m_weights;        //< The weights for the images
        std::filesystem::path m_output_path; //< The path of the output image
        ppm::image m_final_image;            //< The composite image
    };
} // namespace compositing::utils