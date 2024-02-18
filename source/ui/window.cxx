#include "ui/window.hxx"

#include <QDebug>

namespace compositing::ui
{
    window::window(QWidget* parent) : QMainWindow(parent), m_menu(std::make_unique<menu>(this))
    {
        setWindowTitle("Compositing");
        setMinimumSize(800, 600);
        setMenuBar(m_menu.get());

        m_menu->add_action(m_menu->file_menu(), "Open", QKeySequence::Open, [this] { on_open_action_triggered(); });
        m_menu->add_action(m_menu->file_menu(), "Quit", QKeySequence::Close, [this] { on_quit_action_triggered(); });
        m_menu->add_action(m_menu->help_menu(), "About", QKeySequence::HelpContents, [this] { on_about_action_triggered(); });
    }

    void window::on_open_action_triggered()
	{
        qDebug() << "Open action triggered";
	}

    void window::on_quit_action_triggered()
	{
		close();
	}

    void window::on_about_action_triggered()
    {
        qDebug() << "About action triggered";
	}
} // namespace compositing::ui