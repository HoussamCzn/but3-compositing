#pragma once

#include <QListWidget> // QListWidget

class QListWidgetItem;

namespace compositing::ui
{
    class listing : public QListWidget
    {
        Q_OBJECT

    public:

        explicit listing(QWidget* parent = nullptr);

    public slots:

        void on_file_selected(QListWidgetItem* item);

    signals:

        void file_selected(std::string const& file_path);
    };
} // namespace compositing::ui
