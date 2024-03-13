#ifndef ADMINWINDOW_H
#define ADMINWINDOW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QScrollArea>
#include <QApplication>

class AdminWindow : public QWidget {
    Q_OBJECT
public:
    explicit AdminWindow(QWidget *parent = nullptr);

private:
    QVBoxLayout *mainLayout;
    QHBoxLayout *usersLabelLayout;
    QLabel *usersLabel;
    QLineEdit *usersLineEdit;
    QPushButton *usersAddButton;
    QScrollArea *usersScrollArea;
    QHBoxLayout *departmentsLabelLayout;
    QLabel *departmentsLabel;
    QLineEdit *departmentsLineEdit;
    QPushButton *departmentsAddButton;
    QScrollArea *departmentsScrollArea;
};

#endif // ADMINWINDOW_H
