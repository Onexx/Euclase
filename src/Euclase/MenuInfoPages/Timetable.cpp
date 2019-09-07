#include "Timetable.h"

Timetable::Timetable(QWidget *parent) : QWidget(parent), ui(new Ui::Timetable) {
    ui->setupUi(this);
    this->showFullScreen();
    this->setWindowFlag(Qt::FramelessWindowHint);
    scene = new QGraphicsScene;
    ui->MainView->setScene(scene);
    scene->clear();
    QString str;
    str = QFileInfo("Euclase").absolutePath();
    str += "/Materials/Info/Timetable.jpg";
    QPixmap Map(str);
    QSize MapSize = ui->MainView->size();
    Map = Map.scaled(MapSize.width()-100, MapSize.height(), Qt::KeepAspectRatioByExpanding);
    scene->addPixmap(Map);
}

Timetable::~Timetable() {}
