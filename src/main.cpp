#include "windows/MainWindow.h"
#include "utilities/StylesLoader.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow mainWindow;

    a.setStyleSheet(StylesLoader::get().readStyleFromFile("../styles/main.css"));

    mainWindow.show();

    return QApplication::exec();
}
