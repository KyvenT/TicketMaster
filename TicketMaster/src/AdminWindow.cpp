#include "AdminWindow.h"

AdminWindow::AdminWindow(QWidget *parent) : QWidget(parent) {
    setWindowTitle("Admin Page");
    resize(1500, 800);
    departmentNamesVector = UserManager::GetExistingDepartments();

    mainLayout = new QVBoxLayout(this);

    // users section
    usersLabelLayout = new QHBoxLayout;
    usersLabel = new QLabel("Users:");
    usersLabelLayout->addWidget(usersLabel);
    usersLabel->setAlignment(Qt::AlignLeft);
    mainLayout->addLayout(usersLabelLayout);

    // username input
    QHBoxLayout *usernameLayout = new QHBoxLayout;
    QLabel *usernameLabel = new QLabel("Username:");
    usernameLineEdit = new QLineEdit;
    usernameLayout->addWidget(usernameLabel);
    usernameLayout->addWidget(usernameLineEdit);
    mainLayout->addLayout(usernameLayout);

    // password input
    QHBoxLayout *passwordLayout = new QHBoxLayout;
    QLabel *passwordLabel = new QLabel("Password:");
    passwordLineEdit = new QLineEdit;
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLayout->addWidget(passwordLabel);
    passwordLayout->addWidget(passwordLineEdit);
    mainLayout->addLayout(passwordLayout);

    // department input
    QHBoxLayout *departmentLayout = new QHBoxLayout;
    QLabel *departmentLabel = new QLabel("Department:");
    departmentComboBox = new QComboBox;
    departmentComboBox->setFixedWidth(400);
    populateDepartmentsComboBox();
    departmentLayout->addWidget(departmentLabel);
    departmentLayout->addWidget(departmentComboBox);
    mainLayout->addLayout(departmentLayout);

    // add button for users
    usersAddButton = new QPushButton("Add");
    usersAddButton->setFixedWidth(100);
    QHBoxLayout *addButtonLayout = new QHBoxLayout;
    addButtonLayout->addStretch();
    addButtonLayout->addWidget(usersAddButton);
    mainLayout->addLayout(addButtonLayout);

    // user list area
    usersScrollArea = new QScrollArea;
    usersScrollArea->setWidgetResizable(true);
    usersScrollArea->setStyleSheet("background-color: #FFFFFF;");
    mainLayout->addWidget(usersScrollArea);

    // departments section
    departmentsLabelLayout = new QHBoxLayout;
    departmentsLabel = new QLabel("Departments:");
    departmentsLabelLayout->addWidget(departmentsLabel);
    departmentsLabelLayout->setAlignment(Qt::AlignRight);

    // line to enter department name
    departmentsLineEdit = new QLineEdit;
    departmentsLineEdit->setFixedWidth(400);
    departmentsLabelLayout->addWidget(departmentsLineEdit);

    // department add button
    departmentsAddButton = new QPushButton("Add");
    departmentsAddButton->setFixedWidth(100);
    departmentsLabelLayout->addWidget(departmentsAddButton);

    mainLayout->addLayout(departmentsLabelLayout);

    // department list area
    departmentsScrollArea = new QScrollArea;
    departmentsScrollArea->setWidgetResizable(true);
    departmentsScrollArea->setStyleSheet("background-color: #FFFFFF;");
    mainLayout->addWidget(departmentsScrollArea);

    departmentsListLayout = new QVBoxLayout;
    QWidget *departmentsListWidget = new QWidget;
    departmentsListWidget->setLayout(departmentsListLayout);
    departmentsScrollArea->setWidget(departmentsListWidget);

    usersListLayout = new QVBoxLayout;
    QWidget *usersListWidget = new QWidget;
    usersListWidget->setLayout(usersListLayout);
    usersScrollArea->setWidget(usersListWidget);
    
    departmentNames = QSet<QString>();
    populateUsersScrollArea(); // get existing users and add to list area
    connect(usersAddButton, &QPushButton::clicked, this, &AdminWindow::addUser); // connect user add button to function
    populateDepartmentsScrollArea(); // get existing departments and add to list area
    connect(departmentsAddButton, &QPushButton::clicked, this, &AdminWindow::addDepartment); // connect department add button to function

    this->show();
}

void AdminWindow::populateUsersScrollArea() {
    const std::vector<std::shared_ptr<User>>& users = UserManager::GetUsers();

    // add each user to the user list in the UI
    for (const auto& user : users) {
        addUserWidget(user);
    }
}

// creates the user widget in user list section
void AdminWindow::addUserWidget(const std::shared_ptr<User>& user) {
    auto departments = user->GetDepartments();
    std::string departmentName = "None";
    if(!departments.empty()){
        departmentName = departments.front();
    }

    QLabel *usernameLabel = new QLabel(QString::fromStdString(user->GetName()));
    QLabel *departmentLabel = new QLabel(departmentName.c_str());
    QPushButton *deleteButton = new QPushButton("Delete");
    deleteButton->setFixedSize(100, 20);

    QWidget *userWidget = new QWidget;
    QHBoxLayout *userLayout = new QHBoxLayout(userWidget);
    userLayout->addWidget(usernameLabel);
    userLayout->addWidget(departmentLabel);
    userLayout->addWidget(deleteButton);

    usersListLayout->addWidget(userWidget);

    connect(deleteButton, &QPushButton::clicked, this, [=]() {
        deleteUser(userWidget, QString::fromStdString(user->GetName()));
    });
}

// adds new user to list area and in UserManager
void AdminWindow::addUser() {
    QString username = usernameLineEdit->text();
    QString password = passwordLineEdit->text();
    QString department = departmentComboBox->currentText();

    if (!username.isEmpty() && !password.isEmpty()) {
        // check if the username already exists
        if (UserManager::GetUser(username.toStdString()) == nullptr) {
            // creating user
            std::shared_ptr<User> newUser = UserManager::CreateUser(username.toStdString(), password.toStdString());
            if (newUser) {
                // add the user to the selected department
                if(departmentComboBox->currentIndex() != 0){
                    UserManager::AddUserToDepartment(username.toStdString(), department.toStdString());
                }

                // add the user to the UI
                addUserWidget(newUser);
                // clear input fields
                usernameLineEdit->clear();
                passwordLineEdit->clear();
            } else {
                QMessageBox::warning(this, "Error", "Failed to create user.");
            }
        } else {
            QMessageBox::warning(this, "Duplicate User", "This username already exists.");
        }
    } else {
        QMessageBox::warning(this, "Missing Information", "Please fill in all fields.");
    }
}

// removes user 
void AdminWindow::deleteUser(QWidget *userWidget, const QString &username) {
    QLayout *layout = usersListLayout->layout();
    if (layout) {
        layout->removeWidget(userWidget);
        userWidget->deleteLater();

        // remove the user from UserManager
        UserManager::RemoveUser(username.toStdString());
    }
}

// fills department combobox with list of existing departments
void AdminWindow::populateDepartmentsComboBox() {
    // clear existing items in combo box
    departmentComboBox->clear();

    // populate combo box with existing departments from departmentNamesVector
    departmentComboBox->addItem("None");
    for (const std::string& department : departmentNamesVector) {
        departmentComboBox->addItem(QString::fromStdString(department));
    }

}

void AdminWindow::populateDepartmentsScrollArea() {
    // retrieve existing departments from UserManager
    std::vector<std::string> existingDepartments = departmentNamesVector;

    // populate scroll area with existing departments
    for (const std::string& department : existingDepartments) {
        addDepartmentWidget(QString::fromStdString(department));
    }
}

// creates department widget to add to department list area
void AdminWindow::addDepartmentWidget(const QString& departmentName) {
    if (!departmentNames.contains(departmentName)) {
        QPushButton *deleteButton = new QPushButton("Delete");
        deleteButton->setFixedSize(100, 20);
        QLabel *departmentLabel = new QLabel(departmentName);
        QWidget *departmentWidget = new QWidget;
        QHBoxLayout *departmentLayout = new QHBoxLayout(departmentWidget);
        departmentLayout->addWidget(departmentLabel);
        departmentLayout->addWidget(deleteButton);

        departmentsListLayout->addWidget(departmentWidget);

        connect(deleteButton, &QPushButton::clicked, this, [=]() {
            deleteDepartment(departmentWidget, departmentName);
        });

        departmentNames.insert(departmentName);
    }
}

// adds department to the list area and in UserManager
void AdminWindow::addDepartment() {
    QString departmentName = departmentsLineEdit->text();
    if (!departmentName.isEmpty()) {
        if (!departmentNames.contains(departmentName)) { 
            QPushButton *deleteButton = new QPushButton("Delete");
            deleteButton->setFixedSize(100, 20); 
            QLabel *departmentLabel = new QLabel(departmentName);
            QWidget *departmentWidget = new QWidget;
            QHBoxLayout *departmentLayout = new QHBoxLayout(departmentWidget);
            departmentLayout->addWidget(departmentLabel);
            departmentLayout->addWidget(deleteButton);

            departmentsListLayout->addWidget(departmentWidget);

            connect(deleteButton, &QPushButton::clicked, this, [=]() {
                deleteDepartment(departmentWidget, departmentName);
            });

            departmentsLineEdit->clear();
            
            departmentNames.insert(departmentName);
            departmentNamesVector.push_back(departmentName.toStdString());

            //update combo box
            departmentComboBox->addItem(departmentName);
            
        } else {
            QMessageBox::warning(this, "Duplicate Department", "This department already exists.");
        }
    }
}
 
// removes department
void AdminWindow::deleteDepartment(QWidget *departmentWidget, const QString &departmentName) {
    // check if there are users assigned to the department
    std::vector<std::shared_ptr<User>> usersInDepartment = UserManager::GetUsersInDepartment(departmentName.toStdString());
    if (!usersInDepartment.empty()) {
        // show a message box informing the user that there are users assigned to the department
        QMessageBox::warning(this, "Users in Department", "There are users assigned to this department. Please remove them before deleting the department.");
        return; // exit without deleting the department
    }

    // if there are no users assigned to the department, proceed with deletion
    QLayout *layout = departmentsListLayout->layout();
    if (layout) {
        layout->removeWidget(departmentWidget);
        departmentWidget->deleteLater();

        auto it = std::find(departmentNamesVector.begin(), departmentNamesVector.end(), departmentName.toStdString());
        if (it != departmentNamesVector.end()) {
            // remove the department from departmentNamesVector
            departmentNamesVector.erase(it);
        }

        // remove the department from the combo box
        int index = departmentComboBox->findText(departmentName);
        if (index != -1) {
            departmentComboBox->removeItem(index);
        }

        departmentNames.remove(departmentName);
    }
}
