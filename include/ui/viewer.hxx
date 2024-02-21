#pragma once

#include <QGraphicsScene> // QGraphicsScene
#include <QGraphicsView>  // QGraphicsView
#include <QImage>         // QImage
#include <QSlider>        // QSlider
#include <QVBoxLayout>    // QBoxLayout
#include <memory>         // std::unique_ptr
#include <string>         // std::string

namespace compositing::ppm
{
    struct image;
} // namespace compositing::ppm

namespace compositing::ui
{
    class viewer : public QWidget
    {
        Q_OBJECT

    public:

        explicit viewer(QWidget* parent = nullptr);

    public slots:

        void on_empty_image_loaded();

        void on_image_loaded(std::string const& file_path, ppm::image const& image);

        void on_weight_adjusted(int weight);

    signals:

        void image_loaded(std::string const& file_path);

        void weight_adjusted(std::string const& file_path, float weight);

    private:

        [[nodiscard]] static auto ppm_to_qimage(ppm::image const& image) -> QImage;

    private:

        std::string m_file_path;
        std::unique_ptr<QVBoxLayout> m_layout = std::make_unique<QVBoxLayout>(this);
        std::unique_ptr<QGraphicsScene> m_scene = std::make_unique<QGraphicsScene>(this);
        std::unique_ptr<QGraphicsView> m_graphics_view = std::make_unique<QGraphicsView>(this);
        std::unique_ptr<QSlider> m_weight_slider = std::make_unique<QSlider>(Qt::Orientation::Horizontal, this);
    };
} // namespace compositing::ui