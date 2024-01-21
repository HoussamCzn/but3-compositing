#include "image/ppm.hxx"

#include <bit>     // std::bit_cast
#include <cstddef> // std::size_t
#include <fstream> // std::ifstream

namespace compositing::ppm
{
    namespace
    {
        /*
         * @brief Read a PPM image from a file in ASCII format.
         * @param path The path to the file.
         * @return The image if the file exists and is valid, std::nullopt otherwise.
         */
        [[nodiscard]] auto read_ascii(std::ifstream& file, std::uint32_t width, std::uint32_t height) noexcept -> image
        {
            image img = {
                .pixels = std::vector<pixel>(static_cast<std::size_t>(width) * height),
                .width = width,
                .height = height,
            };

            for (auto& pixel : img.pixels)
            {
                std::uint32_t red{0};
                std::uint32_t green{0};
                std::uint32_t blue{0};

                file >> red;
                file >> green;
                file >> blue;

                pixel = {
                    .red = static_cast<std::uint8_t>(red),
                    .green = static_cast<std::uint8_t>(green),
                    .blue = static_cast<std::uint8_t>(blue),
                };
            }

            return img;
        }

        /*
         * @brief Read a PPM image from a file in binary format.
         * @param path The path to the file.
         * @return The image if the file exists and is valid, std::nullopt otherwise.
         */
        [[nodiscard]] auto read_binary(std::ifstream& file, std::uint32_t width, std::uint32_t height) noexcept -> image
        {
            image img = {
                .pixels = std::vector<pixel>(static_cast<std::size_t>(width) * height),
                .width = width,
                .height = height,
            };
            auto* const bytes = std::bit_cast<char*>(img.pixels.data());
            auto const size = static_cast<std::streamsize>(img.pixels.size() * sizeof(pixel));

            file.read(bytes, size);

            return img;
        }
    } // namespace

    /*
     * @brief Read a PPM image from a file.
     * @param path The path to the file.
     * @return The image if the file exists and is valid, std::nullopt otherwise.
     */
    [[nodiscard]] auto read(std::filesystem::path const& path) noexcept -> std::optional<image>
    {
        if (!std::filesystem::exists(path)) [[unlikely]] { return std::nullopt; }

        std::ifstream file{path};
        if (!file.is_open()) [[unlikely]] { return std::nullopt; }

        std::string magic_number;
        std::getline(file, magic_number);

        std::uint32_t width{0};
        std::uint32_t height{0};
        std::uint32_t max_color{0};
        file >> width;
        file >> height;
        file >> max_color;

        file.ignore();

        if (magic_number == "P3") { return read_ascii(file, width, height); }
        if (magic_number == "P6") { return read_binary(file, width, height); }

        return std::nullopt;
    }
} // namespace compositing::ppm