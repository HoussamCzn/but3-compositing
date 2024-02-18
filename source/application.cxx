#include "application.hxx"

#include "ui/window.hxx"

#include <QApplication>

namespace compositing
{
    auto application::run(int argc, char* argv[]) -> int
    {
        QApplication app(argc, argv);
        ui::window window;
        window.show();

        return app.exec();
    }
} // namespace compositing
