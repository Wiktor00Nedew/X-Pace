//
// Created by Wiktor on 28.12.2022.
//

#include "ApplicationPage.h"
#include "../utilities/Singleton.h"
#include "../api/ApiMessage.h"
#include "../api/Api.h"
#include "../components/MessageBoxManager.h"
#include "../utilities/common.h"

ApplicationPage::ApplicationPage(QWidget *parent) {
    createComponents();
    connectSignals();
    setStyling();

    setLayout(mainLayout_);

    isAllSaved = true; // TODO add opening page on click on tree widget and change this var adequately
}

ApplicationPage::~ApplicationPage() {

}

void ApplicationPage::createComponents() {
    mainLayout_ = new QVBoxLayout();
    mainStack_ = new QStackedWidget();
    topBar_ = new TopBar();
    itemsList_ = new ItemsList();

    myTeamsPage_ = new MyTeamsPage();
    addTeamPage_ = new AddTeamPage();
    pageReaderPage_ = new PageReaderPage();
    defaultPage_ = new QWidget();
    manageTeamsPage_ = new ManageTeamPage();
    joinTeamPage_ = new JoinTeamPage();

    mainStack_->addWidget(myTeamsPage_);
    mainStack_->addWidget(addTeamPage_);
    mainStack_->addWidget(pageReaderPage_);
    mainStack_->addWidget(defaultPage_);
    mainStack_->addWidget(manageTeamsPage_);
    mainStack_->addWidget(joinTeamPage_);


    mainSplitter_ = new QSplitter(Qt::Horizontal);
    mainSplitter_->addWidget(itemsList_);
    mainSplitter_->addWidget(mainStack_);

    mainLayout_->addWidget(topBar_);
    mainLayout_->addWidget(mainSplitter_);
}

void ApplicationPage::setStyling() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(defaultPage_));
    mainLayout_->setSpacing(0);
    mainLayout_->setContentsMargins(0, 0, 0, 0);

    mainSplitter_->setHandleWidth(1);
    mainSplitter_->setSizes({(int)(0.3 * width()), (int)(0.7 * width())});
}

void ApplicationPage::connectSignals() {
    connect(topBar_, &TopBar::logedOut, this, &ApplicationPage::onLogout);
    connect(topBar_, &TopBar::myTeamsOpened, this, &ApplicationPage::onMyTeamsOpened);
    connect(this, &ApplicationPage::myTeamsOpened, myTeamsPage_, &MyTeamsPage::loadTeams);
    connect(myTeamsPage_, &MyTeamsPage::createTeamOpened, this, &ApplicationPage::onCreateTeamOpened);
    connect(addTeamPage_, &AddTeamPage::addedTeam, this, &ApplicationPage::onAddedTeam);
    connect(joinTeamPage_, &JoinTeamPage::joinedTeam, this, &ApplicationPage::onJoinedTeam);
    connect(myTeamsPage_, &MyTeamsPage::teamDeleted, this, &ApplicationPage::onTeamDeleted);
    connect(topBar_, &TopBar::teamChanged, this, &ApplicationPage::onTeamChanged);
    connect(pageReaderPage_, &PageReaderPage::settingDefaultPage, this, &ApplicationPage::onSettingDefaultPage);
    connect(itemsList_, &ItemsList::pageOpened, this, &ApplicationPage::onPageOpened);
    connect(pageReaderPage_, &PageReaderPage::unsavedChanges, this, &ApplicationPage::onUnsavedChanges);
    connect(pageReaderPage_, &PageReaderPage::changesSaved, this, &ApplicationPage::onChangesSaved);
    connect(manageTeamsPage_, &ManageTeamPage::setMyTeamsPage, this, &ApplicationPage::onMyTeamsOpened);
    connect(myTeamsPage_, &MyTeamsPage::manageTeamOpened, this, &ApplicationPage::onManageTeamsOpened);
    connect(manageTeamsPage_, &ManageTeamPage::teamNameChanged, this, &ApplicationPage::onTeamNameChanged);
    connect(addTeamPage_, &AddTeamPage::changingToJoinTeam, this, &ApplicationPage::onChangingToJoinTeam);
    connect(joinTeamPage_, &JoinTeamPage::changingToAddTeam, this, &ApplicationPage::onCreateTeamOpened);
}

void ApplicationPage::onLogout() {
    if (!isAllSaved)
        pageReaderPage_->onSaveRequest();
    if (isAllSaved){
        bool active = true;

        while(active){
            ApiMessage apiResponse = Api::get().apiRevokeToken();


            if(apiResponse.type == ApiMessage::Error){
                bool chosenOption = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]) + "\n"
                                                                                                                                            "Spróbować ponownie?");
                if(!chosenOption){
                    return;
                }
                continue;
            }
            active = false;
        }

        emit logedOut();
        mainStack_->setCurrentIndex(mainStack_->indexOf(defaultPage_));
    }

}

void ApplicationPage::onLogin() {
    bool active = true;
    ApiMessage apiResponse;

    while(active){
        apiResponse = Api::get().apiFetchUser();
        //qDebug() << QString::fromStdString(to_string(apiResponse.data));

        if(apiResponse.type == ApiMessage::Error){
            bool chosenOption = MessageBoxManager::get().question("Error", QString::fromStdString(APIErrors[apiResponse.data["key"]]) + "\n"
                                                                                                                                        "Spróbować ponownie?");
            if(!chosenOption){
                return;
            }
            continue;
        }
        active = false;
    }
    //qDebug() << QString::fromStdString(to_string(apiResponse.data));
    topBar_->loadTeams(Api::get().getUser()["teams"]);

    topBar_->setUsername(QString::fromStdString(Api::get().getUser()["username"]));
}

void ApplicationPage::onMyTeamsOpened() {
    if (!isAllSaved)
        pageReaderPage_->onSaveRequest();
    if (isAllSaved){
        mainStack_->setCurrentIndex(mainStack_->indexOf(myTeamsPage_));
        topBar_->loadTeams(Api::get().getUser()["teams"]);
        emit myTeamsOpened();
    }
}

void ApplicationPage::onCreateTeamOpened() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(addTeamPage_));
    emit createTeamOpened();
}

void ApplicationPage::onAddedTeam() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(myTeamsPage_));
    topBar_->loadTeams(Api::get().getUser()["teams"]);
    emit myTeamsOpened();
}

void ApplicationPage::onTeamDeleted() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(myTeamsPage_));
    topBar_->loadTeams(Api::get().getUser()["teams"]);
    emit myTeamsOpened();
}

void ApplicationPage::onTeamChanged(int currentIndex) {
    if (currentIndex >= 0){
        Api::get().setCurrentTeam(Api::get().getUser()["teams"][currentIndex]);
        std::string team = Api::get().getUser()["teams"][currentIndex];
        itemsList_->loadItems(team);
    }
}

void ApplicationPage::onSettingDefaultPage() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(defaultPage_));
}

void ApplicationPage::onPageOpened(const std::string &pageId) {
    if (!isAllSaved)
        pageReaderPage_->onSaveRequest();
    if (isAllSaved){
        mainStack_->setCurrentIndex(mainStack_->indexOf(pageReaderPage_));
        pageReaderPage_->loadPage(pageId);
    }
}

void ApplicationPage::onUnsavedChanges() {
    isAllSaved = false;
}

void ApplicationPage::onChangesSaved() {
    isAllSaved = true;
}

void ApplicationPage::onManageTeamsOpened(const std::string &teamId) {
    mainStack_->setCurrentIndex(mainStack_->indexOf(manageTeamsPage_));
    manageTeamsPage_->loadTeamInfo(teamId);
}

void ApplicationPage::onTeamNameChanged() {
    topBar_->loadTeams(Api::get().getUser()["teams"]);
}

void ApplicationPage::onJoinedTeam() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(myTeamsPage_));
    topBar_->loadTeams(Api::get().getUser()["teams"]);
    emit myTeamsOpened();
}

void ApplicationPage::onChangingToJoinTeam() {
    mainStack_->setCurrentIndex(mainStack_->indexOf(joinTeamPage_));
}

