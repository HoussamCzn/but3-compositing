#include <application.hxx>

auto main(int argc, char* argv[]) -> int
{
    using compositing::application;

    return application::run(argc, argv);
}