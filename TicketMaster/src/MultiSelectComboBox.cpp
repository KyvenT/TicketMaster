#include "MultiSelectComboBox.h"
#include <QStandardItem>
#include <QLineEdit>
#include <QListView>

MultiSelectComboBox::MultiSelectComboBox(QWidget *parent) : QComboBox(parent)
{
    model = new QStandardItemModel(this);
    setModel(model);
    setView(new QListView(this));

    // Ensure the combo box doesn't close on item selection
    view()->viewport()->installEventFilter(this);

    setEditable(true);
    lineEdit()->setReadOnly(true);
    lineEdit()->setCursor(Qt::ArrowCursor);
}

QStringList MultiSelectComboBox::selectedItems() const
{
    QStringList selections;
    for (int i = 0; i < model->rowCount(); ++i) {
        QStandardItem *item = model->item(i);
        if (item->checkState() == Qt::Checked) {
            selections.append(item->text());
        }
    }
    return selections;
}

void MultiSelectComboBox::setSelectedItems(const QStringList &items)
{
    for (int i = 0; i < model->rowCount(); ++i) {
        QStandardItem *item = model->item(i);
        item->setCheckState(items.contains(item->text()) ? Qt::Checked : Qt::Unchecked);
    }
}


