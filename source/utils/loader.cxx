#include "utils/loader.hxx"

#include "image/ppm.hxx" // ppm::read

namespace compositing::utils
{
    auto loader::input_path(std::filesystem::path const& path) -> loader&
    {
        m_input_path = path;

        return *this;
    }

    auto loader::max_file_count(std::size_t count) -> loader&
    {
        m_max_count = count;

        return *this;
    }

    auto loader::skip_if(std::function<bool(std::filesystem::path const&)> const& predicate) -> loader&
    {
        m_skip_predicate = predicate;

        return *this;
    }

    auto loader::load() -> std::unordered_map<std::filesystem::path, ppm::image>
    {
        std::unordered_map<std::filesystem::path, ppm::image> images;

        for (auto const& entry : std::filesystem::recursive_directory_iterator(m_input_path))
        {
            auto const& path = entry.path();
            if (m_skip_predicate && m_skip_predicate(path)) continue;
            if (auto image = ppm::read(path); image.has_value()) { images[path] = std::move(*image); }
            if (images.size() == m_max_count) break;
        }

        return images;
    }
} // namespace compositing::utils