#include "ui/settings.hxx"

#include <QVBoxLayout> // QVBoxLayout

namespace compositing::ui
{
    settings::settings(QWidget* parent) : QDialog(parent)
    {
        QVBoxLayout* layout = new QVBoxLayout(this);
        layout->addWidget(m_format_combo_box.get());
        layout->addWidget(m_allow_overwrite_check_box.get());
        layout->addWidget(m_apply_button.get());
        layout->addWidget(m_reset_button.get());

        m_format_combo_box->addItem("ASCII");
        m_format_combo_box->addItem("Binary");

        connect(m_apply_button.get(), &QPushButton::clicked, this, [this]() { on_settings_changed(); });
        connect(m_reset_button.get(), &QPushButton::clicked, this, [this]() { on_settings_reset(); });

        setLayout(layout);
        setWindowTitle("Settings");
        setFixedSize(200, 150);
    }

    void settings::on_settings_changed()
    {
        emit settings_changed(m_allow_overwrite_check_box->isChecked(), m_format_combo_box->currentIndex() == 0);

        close();
    }

    void settings::on_settings_reset()
    {
        emit settings_reset();

        close();
    }
} // namespace compositing::ui