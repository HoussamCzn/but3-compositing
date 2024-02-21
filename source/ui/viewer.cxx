#include "ui/viewer.hxx"

#include "image/image.hxx" // ppm::image

#include <QGraphicsPixmapItem> // QGraphicsPixmapItem
#include <QGraphicsTextItem>   // QGraphicsTextItem
#include <QImage>              // QImage
#include <QPixmap>             // QPixmap
#include <algorithm>           // std::transform
#include <execution>           // std::execution::par

namespace compositing::ui
{
    viewer::viewer(QWidget* parent) : QWidget(parent)
    {
        m_layout->addWidget(m_graphics_view.get());
        m_layout->addWidget(m_weight_slider.get());
        m_graphics_view->setRenderHint(QPainter::SmoothPixmapTransform);
        m_graphics_view->setScene(m_scene.get());

        connect(m_weight_slider.get(), &QSlider::valueChanged, this, [this]() { on_weight_adjusted(m_weight_slider->value()); });

        setLayout(m_layout.get());
    }

    void viewer::on_empty_image_loaded()
    {
        m_scene->clear();
        m_file_path.clear();
        m_weight_slider->setValue(0);
    }

    void viewer::on_image_loaded(std::string const& file_path, ppm::image const& image)
    {
        auto const qimage = ppm_to_qimage(image);
        auto* pixmap_item = new QGraphicsPixmapItem(QPixmap::fromImage(qimage));
        m_file_path = file_path;
        m_scene->clear();
        m_scene->addItem(pixmap_item);
        m_weight_slider->setValue(100);

        emit image_loaded(file_path);
    }

    void viewer::on_weight_adjusted(int weight) { emit weight_adjusted(m_file_path, static_cast<float>(weight) / 100.0f); }

    auto viewer::ppm_to_qimage(ppm::image const& image) -> QImage
    {
        QImage qimage(image.width, image.height, QImage::Format_RGB32);

        for (auto y{0U}; y < image.height; ++y)
        {
            for (auto x{0U}; x < image.width; ++x)
            {
                auto const index = y * image.width + x;
                auto const pixel = image.pixels[static_cast<std::size_t>(index)];
                qimage.setPixel(x, y, qRgb(pixel.red, pixel.green, pixel.blue));
            }
        }

        return qimage;
    }
} // namespace compositing::ui