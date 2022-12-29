//
// Created by wiktor on 9/21/22.
//

#pragma once

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>
#include "../components/PasswordBox.h"
#include "../structures/TitleBar.h"
#include "../pages/LoginPage.h"
#include "../pages/RegisterPage.h"
#include "../pages/ApplicationPage.h"
#include <QStackedWidget>

class MainWindow : public QWidget{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    // main app stack
    QStackedWidget *mainStack_;

    // layouts
    QGridLayout *mainLayout_;

    // methods
    void createComponents();
    void createPages();
    void connectSignals();
    void setStyling();

    // events
    void resizeEvent(QResizeEvent *event);

    // components
    TitleBar *titleBar_;
    QPushButton *testButton_;
    QLineEdit *testLineEdit_;
    PasswordBox *testPasswordBox_;
    QLabel *testLabel_;

    // pages
    LoginPage *loginPage_;
    RegisterPage *registerPage_;
    ApplicationPage *applicationPage_;

public slots:
    void changedToRegister();
    void changedToLogin();
    void changedToApplication();
};

