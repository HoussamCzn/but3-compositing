#pragma once

#include "image/ppm.hxx" // ppm::image

#include <functional> // std::function
#include <optional>   // std::optional

namespace compositing
{
	class loader
	{
    public:

		auto input_path(std::filesystem::path const& path) -> loader&;

		auto max_file_count(std::size_t count) -> loader&;

		auto skip_if(std::function<bool(std::filesystem::path const&)> const& predicate) -> loader&;

		auto load() -> std::vector<ppm::image>;

	private:

        std::function<bool(std::filesystem::path const&)> m_skip_predicate;
        std::filesystem::path m_input_path;
		std::size_t m_max_count = std::numeric_limits<std::size_t>::max();
	};
} // namespace compositing