#pragma once

#include <QCheckBox>   // QCheckBox
#include <QComboBox>   // QComboBox
#include <QDialog>     // QDialog
#include <QLabel>      // QLabel
#include <QPushButton> // QPushButton
#include <QSpinBox>    // QSpinBox
#include <memory>      // std::unique_ptr

namespace compositing::ui
{
    class settings : public QDialog
    {
        Q_OBJECT

    public:

        explicit settings(QWidget* parent = nullptr);

    private slots:

        void on_settings_changed();

        void on_settings_reset();

    signals:

        void settings_changed(bool can_overwrite, bool is_ascii_format);

        void settings_reset();

    private:

        std::unique_ptr<QCheckBox> m_allow_overwrite_check_box = std::make_unique<QCheckBox>("Allow Overwrite", this);
        std::unique_ptr<QComboBox> m_format_combo_box = std::make_unique<QComboBox>(this);
        std::unique_ptr<QPushButton> m_apply_button = std::make_unique<QPushButton>("Apply", this);
        std::unique_ptr<QPushButton> m_reset_button = std::make_unique<QPushButton>("Reset", this);
    };
} // namespace compositing::ui