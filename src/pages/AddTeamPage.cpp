//
// Created by Wiktor on 01.01.2023.
//

#include "AddTeamPage.h"
#include "../api/Api.h"
#include "../utilities/common.h"
#include "../components/MessageBoxManager.h"

AddTeamPage::AddTeamPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

AddTeamPage::~AddTeamPage() {

}

void AddTeamPage::createComponents() {
    mainLayout_ = new QVBoxLayout();
    title_ = new Title();
    nameLabel_ = new QLabel();
    nameBox_ = new QLineEdit();
    addTeamButton_ = new QPushButton();
    loadingIndicator_ = new LoadingIndicator();
    errorLabel_ = new ErrorLabel();
    joinRedirect_ = new ClickableLabel();
    backButton_ = new QPushButton();

    mainLayout_->addWidget(title_);
    mainLayout_->addWidget(nameLabel_);
    mainLayout_->addWidget(nameBox_);
    mainLayout_->addWidget(addTeamButton_);
    mainLayout_->addWidget(joinRedirect_);
    mainLayout_->addWidget(loadingIndicator_);
    mainLayout_->addWidget(errorLabel_);
    mainLayout_->addStretch();
    mainLayout_->addWidget(backButton_);
}

void AddTeamPage::setStyling() {
    nameLabel_->setText("Nazwa zespołu");
    addTeamButton_->setText("Stwórz nowy zespół");
    title_->setText("Stwórz nowy zespół");\
    joinRedirect_->setAlignment(Qt::AlignHCenter);
    joinRedirect_->setText("Lub dołącz do zespołu");
    backButton_->setText("Wróć");
}

void AddTeamPage::connectSignals() {
    connect(addTeamButton_, &QPushButton::clicked, this, &AddTeamPage::addTeam);
    connect(joinRedirect_, &ClickableLabel::clicked, this, [=](){
        emit changingToJoinTeam();
    });
    connect(backButton_, &QPushButton::clicked, this, [=](){
        nameBox_->clear();
        emit changingToMyTeams();
    });
}

void AddTeamPage::addTeam() {
    loadingIndicator_->show();

    if (nameBox_->text() == ""){
        loadingIndicator_->hide();
        errorLabel_->setError("NO_NAME");
        return;
    }

    auto apiResponse = Api::get().apiCreateTeam(nameBox_->text().toStdString());

    if (apiResponse.type == ApiMessage::Error){
        loadingIndicator_->hide();
        errorLabel_->setError(apiResponse.data["key"]);
        return;
    }

    bool active = true;
    ApiMessage apiResponse2;

    while(active){
        apiResponse2 = Api::get().apiFetchUser();
        //qDebug() << QString::fromStdString(to_string(apiResponse2.data));

        if(apiResponse2.type == ApiMessage::Error){
            bool chosenOption = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse2.data["key"]]) + "\n"
                                                                                                                                        "Spróbować ponownie?");
            if(!chosenOption){
                return;
            }
            continue;
        }
        active = false;
    }

    errorLabel_->setError("NO_ERROR");

    emit addedTeam();

    nameBox_->clear();
    loadingIndicator_->hide();
}
