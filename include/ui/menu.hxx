#pragma once

#include <QAction>    // QAction
#include <QMenuBar>   // QMenuBar
#include <functional> // std::function
#include <memory>     // std::unique_ptr

class QMenu;

namespace compositing::ui
{
    class menu : public QMenuBar
    {
        Q_OBJECT

    public:

        explicit menu(QWidget* parent = nullptr);

        auto file_menu() -> QMenu&;

        auto options_menu() -> QMenu&;

        auto help_menu() -> QMenu&;

        void add_item(QMenu& menu, QString const& text, QKeySequence const& shortcut, std::function<void()> slot,
                      QString const& tip = "");

        void add_item(QMenu& menu, QString const& text, QString const& shortcut, std::function<void()> slot,
                      QString const& tip = "");

    private:

        QMenu* m_file_menu = addMenu("File");
        QMenu* m_options_menu = addMenu("Options");
        QMenu* m_help_menu = addMenu("Help");
        std::vector<std::unique_ptr<QAction>> m_actions;
    };
} // namespace compositing::ui