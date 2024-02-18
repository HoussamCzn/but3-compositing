#pragma once

#include <QMenuBar>   // QMenuBar
#include <functional> // std::function

class QMenu;

namespace compositing::ui
{
    class menu : public QMenuBar
    {
        Q_OBJECT

    public:

        explicit menu(QWidget* parent = nullptr);

        auto file_menu() -> QMenu* const;

        auto options_menu() -> QMenu* const;

        auto help_menu() -> QMenu* const;

        void add_action(QMenu* const p_menu, QString const& text, QKeySequence const& shortcut, std::function<void()> slot,
                        QString const& tip = "");

    private:

        QMenu* m_file_menu{nullptr};
        QMenu* m_options_menu{nullptr};
        QMenu* m_help_menu{nullptr};
    };
} // namespace compositing::ui