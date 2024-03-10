#pragma once

#include <QScrollArea>
#include <QGridLayout>

class DepartmentTicketsGUI : public QWidget {
public:
    DepartmentTicketsGUI() = delete;
    DepartmentTicketsGUI(QWidget* parent);

private:

    std::unique_ptr<QSpacerItem> spacer;
    std::unique_ptr<QLabel> title;
    std::unique_ptr<QGridLayout> gridLayout;
    std::unique_ptr<QGridLayout> scrollGridLayout;
    std::unique_ptr<QScrollArea> scrollArea;
    std::unique_ptr<QWidget> contents;

};
