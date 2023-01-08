//
// Created by Wiktor on 01.01.2023.
//

#include "JoinTeamPage.h"
#include "../api/Api.h"
#include "../utilities/common.h"
#include "../components/MessageBoxManager.h"

JoinTeamPage::JoinTeamPage(QWidget *parent) {
    createComponents();
    setStyling();
    connectSignals();

    setLayout(mainLayout_);
}

JoinTeamPage::~JoinTeamPage() {

}

void JoinTeamPage::createComponents() {
    mainLayout_ = new QVBoxLayout();
    title_ = new Title();
    tokenLabel_ = new QLabel();
    tokenBox_ = new QLineEdit();
    joinTeamButton_ = new QPushButton();
    loadingIndicator_ = new LoadingIndicator();
    errorLabel_ = new ErrorLabel();
    addTeamRedirect_ = new ClickableLabel();

    mainLayout_->addWidget(title_);
    mainLayout_->addWidget(tokenLabel_);
    mainLayout_->addWidget(tokenBox_);
    mainLayout_->addWidget(joinTeamButton_);
    mainLayout_->addWidget(addTeamRedirect_);
    mainLayout_->addWidget(loadingIndicator_);
    mainLayout_->addWidget(errorLabel_);
    mainLayout_->addStretch();
}

void JoinTeamPage::setStyling() {
    tokenLabel_->setText("Kod dołączenia");
    joinTeamButton_->setText("Dołącz do zespołu");
    title_->setText("Dołącz do zespołu");

    addTeamRedirect_->setText("Lub stwórz nowy zespół");
    addTeamRedirect_->setAlignment(Qt::AlignHCenter);
}

void JoinTeamPage::connectSignals() {
    connect(joinTeamButton_, &QPushButton::clicked, this, &JoinTeamPage::joinTeam);
    connect(addTeamRedirect_, &ClickableLabel::clicked, this, [=](){
        emit changingToAddTeam();
    });
}

void JoinTeamPage::joinTeam() {
    loadingIndicator_->show();

    if (tokenBox_->text() == ""){
        loadingIndicator_->hide();
        errorLabel_->setError("NO_TOKEN");
        return;
    }

    auto apiResponse = Api::get().apiJoinTeam(tokenBox_->text().toStdString());

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

    emit joinedTeam();

    tokenBox_->clear();
    loadingIndicator_->hide();
}
