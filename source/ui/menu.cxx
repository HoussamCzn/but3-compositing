#include "ui/menu.hxx"

#include <QMainWindow> // QMainWindow
#include <QMenu>       // QMenu

namespace compositing::ui
{
    menu::menu(QWidget* parent)
        : QMenuBar(parent), m_file_menu(addMenu("File")), m_options_menu(addMenu("Options")), m_help_menu(addMenu("Help"))
    {}

    auto menu::file_menu() -> QMenu* const { return m_file_menu; }

    auto menu::options_menu() -> QMenu* const { return m_options_menu; }

    auto menu::help_menu() -> QMenu* const { return m_help_menu; }

    void menu::add_action(QMenu* const p_menu, QString const& text, QKeySequence const& shortcut, std::function<void()> slot,
                          QString const& tip)
    {
        auto* action = new QAction(text, this);
        action->setShortcut(shortcut);
        action->setStatusTip(tip);
        connect(action, &QAction::triggered, this, slot);
        p_menu->addAction(action);
    }
} // namespace compositing::ui