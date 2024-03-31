#ifndef TICKETMASTER_MULTISELECTCOMBOBOX_H
#define TICKETMASTER_MULTISELECTCOMBOBOX_H
#ifndef MULTISELECTCOMBOBOX_H
#define MULTISELECTCOMBOBOX_H

#include <QComboBox>
#include <QStandardItemModel>

class MultiSelectComboBox : public QComboBox
{
Q_OBJECT

public:
    explicit MultiSelectComboBox(QWidget *parent = nullptr);

    // Utility functions to manage selections
    QStringList selectedItems() const;
    void setSelectedItems(const QStringList &items);

private:
    QStandardItemModel *model;
};

#endif // MULTISELECTCOMBOBOX_H
#endif //TICKETMASTER_MULTISELECTCOMBOBOX_H
