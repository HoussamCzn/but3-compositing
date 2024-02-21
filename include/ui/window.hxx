#pragma once

#include "image/ppm.hxx"  // ppm::format, ppm::image
#include "ui/listing.hxx" // ui::listing
#include "ui/menu.hxx"    // ui::menu
#include "ui/viewer.hxx"  // ui::viewer

#include <QMainWindow>   // QMainWindow
#include <QPushButton>   // QPushButton
#include <filesystem>    // std::filesystem::path
#include <memory>        // std::unique_ptr
#include <unordered_map> // std::unordered_map

namespace compositing::ui
{
    class window : public QMainWindow
    {
        Q_OBJECT

    public:

        explicit window(QWidget* parent = nullptr);

    public slots:

        void on_directory_selected();

        void on_about_opened();

        void on_settings_opened();

        void on_settings_changed(bool can_overwrite, bool is_ascii_format);

        void on_settings_reset();

        void on_file_selected(std::string const& file_path);

        void on_weight_adjusted(std::string const& file_path, float weight);

        void on_composite_saved();

        void on_composite_reset();

    private:

        std::unordered_map<std::filesystem::path, ppm::image> m_images;
        std::unordered_map<std::filesystem::path, float> m_weights;
        std::unique_ptr<QWidget> m_central_widget = std::make_unique<QWidget>(this);
        std::unique_ptr<listing> m_listing = std::make_unique<listing>(this);
        std::unique_ptr<menu> m_menu = std::make_unique<menu>(this);
        std::unique_ptr<viewer> m_viewer = std::make_unique<viewer>(this);
        std::unique_ptr<QPushButton> m_save_button = std::make_unique<QPushButton>("Save", this);
        std::unique_ptr<QPushButton> m_reset_button = std::make_unique<QPushButton>("Reset", this);
        ppm::format m_format = ppm::format::ascii;
        bool m_can_overwrite = false;
    };
} // namespace compositing::ui