#include "ui/window.hxx"

#include "image/ppm.hxx"     // ppm::image, ppm::write
#include "ui/settings.hxx"   // ui::settings
#include "utils/builder.hxx" // utils::builder
#include "utils/loader.hxx"  // utils::loader

#include <QFileDialog> // QFileDialog
#include <QMessageBox> // QMessageBox

namespace compositing::ui
{
    window::window(QWidget* parent) : QMainWindow(parent)
    {
        auto* const main_layout = new QHBoxLayout(m_central_widget.get());
        auto* const listing_layout = new QVBoxLayout();
        auto* const viewer_layout = new QVBoxLayout();
        auto* const buttons_layout = new QHBoxLayout();
        auto* const spacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        main_layout->addLayout(listing_layout);
        main_layout->addLayout(viewer_layout, 1);
        listing_layout->addWidget(m_listing.get());
        viewer_layout->addWidget(m_viewer.get());
        viewer_layout->addLayout(buttons_layout);
        buttons_layout->addItem(spacer);
        buttons_layout->addWidget(m_save_button.get());
        buttons_layout->addWidget(m_reset_button.get());
        m_central_widget->setLayout(main_layout);

        m_menu->add_item(m_menu->file_menu(), "Open...", QKeySequence::Open, [this]() { on_directory_selected(); });
        m_menu->add_item(m_menu->file_menu(), "Save", QKeySequence::Save, [this]() { on_composite_saved(); });
        m_menu->add_item(m_menu->file_menu(), "Reset", QKeySequence::Refresh, [this]() { on_composite_reset(); });
        m_menu->add_item(m_menu->file_menu(), "Quit", QKeySequence::Quit, [this]() { close(); });
        m_menu->add_item(m_menu->options_menu(), "Settings", QKeySequence::Preferences, [this]() { on_settings_opened(); });
        m_menu->add_item(m_menu->help_menu(), "About", QKeySequence::HelpContents, [this]() { on_about_opened(); });

        connect(m_listing.get(), &QListWidget::itemClicked, this,
                [this](QListWidgetItem* item) { on_file_selected(item->text().toStdString()); });
        connect(m_viewer.get(), &viewer::weight_adjusted, this,
                [this](std::string const& file_path, float weight) { on_weight_adjusted(file_path, weight); });
        connect(m_save_button.get(), &QPushButton::clicked, this, [this] { on_composite_saved(); });
        connect(m_reset_button.get(), &QPushButton::clicked, this, [this] { on_composite_reset(); });

        setWindowTitle("BUT3 Composite");
        setFixedSize(1080, 720);
        setCentralWidget(m_central_widget.get());
        setMenuBar(m_menu.get());
    }

    void window::on_directory_selected()
    {
        auto const selected_directory = QFileDialog::getExistingDirectory(
            this, "Open Directory", QDir::currentPath(), QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

        if (!selected_directory.isEmpty()) [[likely]]
        {
            utils::loader image_loader;
            m_images = image_loader.input_path(selected_directory.toStdString()).load();

            for (auto const& [path, _] : m_images)
            {
                auto const& path_as_string = path.string();
                m_weights[path_as_string] = 1.F;
                m_listing->addItem(QString::fromStdString(path_as_string));
            }
        }
    }

    void window::on_about_opened()
    {
        QMessageBox::information(this, "About",
                                 "Compositing application written as part of an assignment.\n\nDate: 19/02/2024\nVersion: 1.0.0");
    }

    void window::on_settings_opened()
    {
        settings settings_dialog(this);
        connect(&settings_dialog, &settings::settings_changed, this,
                [this](bool can_overwrite, bool is_ascii_format) { on_settings_changed(can_overwrite, is_ascii_format); });
        connect(&settings_dialog, &settings::settings_reset, this, [this]() { on_settings_reset(); });

        settings_dialog.exec();
    }

    void window::on_settings_changed(bool can_overwrite, bool is_ascii_format)
    {
        m_can_overwrite = can_overwrite;
        m_format = is_ascii_format ? ppm::format::ascii : ppm::format::binary;
    }

    void window::on_settings_reset()
    {
        m_can_overwrite = false;
        m_format = ppm::format::ascii;
    }

    void window::on_file_selected(std::string const& file_path)
    {
        auto const& image = m_images[file_path];
        m_viewer->on_image_loaded(file_path, image);
    }

    void window::on_weight_adjusted(std::string const& file_path, float weight) { m_weights[file_path] = weight; }

    void window::on_composite_saved()
    {
        auto const selected_file =
            QFileDialog::getSaveFileName(this, "Save File", QDir::currentPath(), "Portable Pixmap (*.ppm)");

        if (!selected_file.isEmpty()) [[likely]]
        {
            utils::builder image_builder;
            std::vector<ppm::image> images;
            std::vector<float> weights;
            images.reserve(m_images.size());
            weights.reserve(m_weights.size());

            for (auto const& [path, image] : m_images)
            {
                images.push_back(image);
                weights.push_back(m_weights[path.string()]);
            }

            auto const composed_image =
                image_builder.output_path(selected_file.toStdString()).images(images).weights(weights).composite();
            auto const is_successful_write = ppm::write(composed_image, selected_file.toStdString(), m_format, m_can_overwrite);

            if (!is_successful_write) [[unlikely]]
            {
                QMessageBox::critical(this, "Failed to save",
                                      std::format("Error when attempting to write the composite image to location \"{}\". If the "
                                                  "file already exists, allow overwriting it.",
                                                  selected_file.toStdString())
                                          .c_str());
            }
            else
            {
                QMessageBox::information(this, "Success", "Composite image saved successfully.");
            }
        }
    }

    void window::on_composite_reset()
    {
        auto const response =
            QMessageBox::question(this, "Reset composite", "Are you sure you want to reset the current composition?",
                                  QMessageBox::Yes | QMessageBox::No);

        if (response == QMessageBox::Yes) [[likely]]
        {
            m_images.clear();
            m_weights.clear();
            m_listing->clear();
            m_viewer->on_empty_image_loaded();
        }
    }
} // namespace compositing::ui
