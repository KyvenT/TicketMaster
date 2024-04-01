#include "MultiSelectComboBox.h"
#include <QListView>

MultiSelectComboBox::MultiSelectComboBox(QWidget *parent) : QComboBox(parent)
{
    model = new QStandardItemModel(this);
    setModel(model);
    view()->installEventFilter(this); // Install event filter to intercept click events on the dropdown
    setView(new QListView(this));
}

void MultiSelectComboBox::showPopup()
{
    // Custom behavior before showing the popup if needed
    QComboBox::showPopup(); // Call base class implementation to show the popup
}

void MultiSelectComboBox::hidePopup()
{
    // Override hidePopup to prevent the popup from closing automatically
}

bool MultiSelectComboBox::eventFilter(QObject *watched, QEvent *event)
{
    if (event->type() == QEvent::MouseButtonRelease && watched == view()->viewport()) {
        QMouseEvent *mouseEvent = static_cast<QMouseEvent *>(event);
        QModelIndex index = view()->indexAt(mouseEvent->pos());
        if (index.isValid()) {
            QStandardItem *item = model->itemFromIndex(index);
            if (item->checkState() == Qt::Checked)
                item->setCheckState(Qt::Unchecked);
            else
                item->setCheckState(Qt::Checked);

            return true; // Indicate that the event has been handled
        }
    }
    return QComboBox::eventFilter(watched, event); // Call base class eventFilter for other events
}
