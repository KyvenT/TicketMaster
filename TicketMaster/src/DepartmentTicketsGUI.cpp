#include <QLabel>
#include "DepartmentTicketsGUI.h"
#include "TicketGUI.h"

DepartmentTicketsGUI::DepartmentTicketsGUI(QWidget *parent) : QWidget(parent) {

    QPalette pal = this->palette();
    pal.setColor(this->backgroundRole(), Qt::lightGray);
    this->setPalette(pal);

    this->setMinimumHeight(300);

    gridLayout = std::make_unique<QGridLayout>(this);
    title = std::make_unique<QLabel>("Department: ", this);
    gridLayout->addWidget(title.get(), 0, 0, 1, 1);

    QFont font = title->font();
    font.setPointSize(24);
    title->setFont(font);

    scrollArea = std::make_unique<QScrollArea>(this);
    scrollArea->setWidgetResizable(true);
    gridLayout->addWidget(scrollArea.get(), 1, 0, 1, 1);

    contents = std::make_unique<QWidget>();
    scrollArea->setWidget(contents.get());

    scrollGridLayout = std::make_unique<QGridLayout>(contents.get());


    // testing
    TicketGUI* t1 = new TicketGUI(contents.get());
    scrollGridLayout->addWidget(t1, 0, 0, 1, 1);

    /*TicketGUI* t2 = new TicketGUI(contents.get());
    scrollGridLayout->addWidget(t2, 1, 0, 1, 1);

    TicketGUI* t3 = new TicketGUI(contents.get());
    scrollGridLayout->addWidget(t3, 2, 0, 1, 1);

    TicketGUI* t4 = new TicketGUI(contents.get());
    scrollGridLayout->addWidget(t4, 3, 0, 1, 1);*/

    spacer = std::make_unique<QSpacerItem>(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
    scrollGridLayout->addItem(spacer.get(), 4, 0, 1, 1);
}
