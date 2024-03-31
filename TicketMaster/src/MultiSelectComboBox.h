#ifndef MULTISELECTCOMBOBOX_H
#define MULTISELECTCOMBOBOX_H

#include <QComboBox>
#include <QStandardItemModel>
#include <QEvent>
#include <QMouseEvent>

class MultiSelectComboBox : public QComboBox
{
Q_OBJECT

public:
    explicit MultiSelectComboBox(QWidget *parent = nullptr);

protected:
    virtual void showPopup() override;
    virtual void hidePopup() override;
    bool eventFilter(QObject *watched, QEvent *event) override;

private:
    QStandardItemModel *model;
};

#endif // MULTISELECTCOMBOBOX_H

