//
// Created by Wiktor on 07.01.2023.
//

#pragma once


#include <QWidget>
#include <QVBoxLayout>
#include <QTextEdit>
#include <QPushButton>

class EditPage : public QWidget{
    Q_OBJECT
public:
    explicit EditPage(QWidget *parent = nullptr);
    ~EditPage();

private:
    std::string pageId_;

    void createComponents();
    void setStyling();
    void connectSignals();

    QGridLayout *mainLayout_;

    QTextEdit *markdownEdit_;
    QPushButton *saveButton_;
    QPushButton *cancelButton_;

public slots:
    void loadPage(const std::string& pageId);
    void onSaveButtonClicked();
    void onSaveRequest();

signals:
    void finishingEditing(const std::string& pageId);
    void settingDefaultPage();
    void changesSaved();
    void unsavedChanges();
};
