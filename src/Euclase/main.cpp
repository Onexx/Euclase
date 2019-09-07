#include <QApplication>
#include <QStackedWidget>
#include <QString>
#include "Menu.h"
#include "Statistics/logs.h"
#include "data.cpp"

int main(int argc, char* argv[]) {
    loadLocale();                // Loading locales
    QApplication a(argc, argv);  // starting application
    QSplashScreen* splash = new QSplashScreen;
    splash->setPixmap(QPixmap("Materials/Splash.png"));
    splash->show();  // Showing splash screen
    Menu m;          // Creating menu widget
    m.setWindowTitle(QString("Euclase V." + QString::number(Data::version) +
                             "." + QString::number(Data::build)));
    QTimer::singleShot(2500, splash, SLOT(close()));  // Closing spash screen
    QTimer::singleShot(2500, &m, SLOT(showFullScreen()));  // Showing menu
    return a.exec();
}
