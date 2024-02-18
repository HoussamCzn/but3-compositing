#pragma once

namespace compositing
{
    class application
    {
    public:

        static auto run(int argc, char* argv[]) -> int;

    private:

        application() = default;

        ~application() = default;

        application(application const&) = delete;

        application(application&&) = delete;

        auto operator=(application const&) -> application& = delete;

        auto operator=(application&&) -> application& = delete;
    };
} // namespace compositing
