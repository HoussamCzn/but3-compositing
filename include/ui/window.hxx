#pragma once

#include "menu.hxx"

#include <QMainWindow>
#include <memory>

namespace compositing::ui
{
    class window : public QMainWindow
    {
        Q_OBJECT

    public:

        window(QWidget* parent = nullptr);

    public slots:

        void on_open_action_triggered();

        void on_quit_action_triggered();

        void on_about_action_triggered();

    private:

        std::unique_ptr<menu> m_menu;
    };
} // namespace compositing::ui