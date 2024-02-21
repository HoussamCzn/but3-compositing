#include "ui/menu.hxx"

#include <QMainWindow> // QMainWindow
#include <QMenu>       // QMenu

namespace compositing::ui
{
    menu::menu(QWidget* parent) : QMenuBar(parent) {}

    auto menu::file_menu() -> QMenu& { return *m_file_menu; }

    auto menu::options_menu() -> QMenu& { return *m_options_menu; }

    auto menu::help_menu() -> QMenu& { return *m_help_menu; }

    void menu::add_item(QMenu& menu, QString const& text, QKeySequence const& shortcut, std::function<void()> slot,
                        QString const& tip)
    {
        auto& action = m_actions.emplace_back(new QAction(text, this));
        action->setShortcut(shortcut);
        action->setStatusTip(tip);
        connect(action.get(), &QAction::triggered, this, slot);
        menu.addAction(action.get());
    }

    void menu::add_item(QMenu& menu, QString const& text, QString const& shortcut, std::function<void()> slot, QString const& tip)
    {
        add_item(menu, text, QKeySequence(shortcut), slot, tip);
    }
} // namespace compositing::ui