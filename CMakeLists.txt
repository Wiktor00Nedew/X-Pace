cmake_minimum_required(VERSION 3.20)
project(X_Pace)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)

if(WIN32)
    set(CMAKE_PREFIX_PATH libraries/win32/lib/cmake)
endif(WIN32)

find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        Network
        REQUIRED)

add_executable(X_Pace src/main.cpp src/windows/MainWindow.cpp src/windows/MainWindow.h src/utilities/StylesLoader.cpp src/utilities/StylesLoader.h src/utilities/Singleton.h src/components/PasswordBox.cpp src/components/PasswordBox.h src/structures/TitleBar.cpp src/structures/TitleBar.h src/pages/LoginPage.cpp src/pages/LoginPage.h src/api/Api.cpp src/api/ApiMessage.h src/api/Api.h src/utilities/QNetworkAccessManagerWithDelete.h src/utilities/QNetworkAccessManagerWithPatch.h src/utilities/json.hpp src/utilities/common.cpp src/utilities/common.h src/structures/LoginForm.cpp src/structures/LoginForm.h src/components/ErrorLabel.h src/components/ErrorLabel.cpp src/components/LoadingIndicator.cpp src/components/LoadingIndicator.h src/utilities/StringManager.h src/pages/RegisterPage.cpp src/pages/RegisterPage.h src/structures/RegisterForm.cpp src/structures/RegisterForm.h src/components/ClickableLabel.cpp src/components/ClickableLabel.h src/components/Title.cpp src/components/Title.h src/pages/ApplicationPage.cpp src/pages/ApplicationPage.h src/components/DropdownButton.cpp src/components/DropdownButton.h src/structures/TopBar.cpp src/structures/TopBar.h src/components/MessageBoxManager.cpp src/components/MessageBoxManager.h src/components/Button.cpp src/components/Button.h src/pages/MyTeamsPage.cpp src/pages/MyTeamsPage.h src/pages/AddTeamPage.cpp src/pages/AddTeamPage.h src/structures/TeamListItem.cpp src/structures/TeamListItem.h src/components/TeamListItemButtons.cpp src/components/TeamListItemButtons.h src/components/TreeWidgetButtons.cpp src/components/TreeWidgetButtons.h src/structures/ItemsList.cpp src/structures/ItemsList.h src/components/ItemWidget.cpp src/components/ItemWidget.h src/components/Permission.cpp src/components/Permission.h src/pages/PageReaderPage.cpp src/pages/PageReaderPage.h src/pages/EditPage.cpp src/pages/EditPage.h src/pages/ViewPage.cpp src/pages/ViewPage.h src/pages/ManageTeamPage.cpp src/pages/ManageTeamPage.h src/pages/JoinTeamPage.cpp src/pages/JoinTeamPage.h)

target_compile_options(X_Pace PRIVATE -Wall)

target_link_libraries(X_Pace
        Qt::Core
        Qt::Gui
        Qt::Widgets
        Qt::Network
        )