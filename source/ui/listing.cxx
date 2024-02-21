#include "ui/listing.hxx"

#include <QListWidgetItem> // QListWidgetItem

namespace compositing::ui
{
    listing::listing(QWidget* parent) : QListWidget(parent)
    {
        connect(this, &QListWidget::itemClicked, this, [this](QListWidgetItem* item) { on_file_selected(item); });
    }

    void listing::on_file_selected(QListWidgetItem* item) { emit file_selected(item->text().toStdString()); }
} // namespace compositing::ui